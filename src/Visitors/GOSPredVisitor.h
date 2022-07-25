#ifndef CSP2SAT_GOSPREDVISITOR_H
#define CSP2SAT_GOSPREDVISITOR_H

#include "GOSCustomBaseVisitor.h"
#include "../Symtab/Symbol/PredSymbol.h"
#include "../Symtab/SymbolTable.h"
#include "../BUPFile.h"
#include <BUPLexer.h>
#include <BUPParser.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <filesystem>

namespace GOS {

class GOSPredVisitor : public GOSCustomBaseVisitor {
public:
    explicit GOSPredVisitor(SymbolTable *symbolTable, SMTFormula *f, const std::string& filename) :
            GOSCustomBaseVisitor(symbolTable, f)
    {
        _includes.push(std::filesystem::canonical(filename));
    }

    antlrcpp::Any visitPredCall(BUPParser::PredCallContext *ctx) override { // TODO copied from GOSConstraintsVisitor. Maybe put in BUPBaseVisitor the common part?
        // Get call parameters
        std::vector<SymbolRef> paramsSymbols;
        PredSymbol::Signature signature;
        signature.name = ctx->name->getText();
        if (ctx->predCallParams()) {
            this->accessingNotLeafVariable = true; // TODO ask Mateu if this is correct
            // Evaluate all parameters from call
            for (auto predCallParamCtx: ctx->predCallParams()->predCallParam()) {
                SymbolRef sym;
                antlrcpp::Any res = visit(predCallParamCtx);
                if (res.is<ValueRef>()) { // Anonymous constant
                    ValueRef val = res.as<ValueRef>();
                    AssignableSymbolRef assignableSym;
                    if(val->isBoolean())
                        assignableSym = AssignableSymbol::Create("",SymbolTable::_boolean);
                    else assignableSym = AssignableSymbol::Create("",SymbolTable::_integer);
                    assignableSym->setValue(val);
                    sym = assignableSym;
                }
                else sym = res; // Defined symbol
                paramsSymbols.emplace_back(sym);

                // Construct signature to lookup the predicate in the symbol table
                const int type = sym->getType()->getTypeIndex();
                PredSymbol::ParamRef param;
                if (type == SymbolTable::tArray) {
                    ArraySymbolRef arraySym = Utils::as<ArraySymbol>(sym);
                    PredSymbol::ParamArrayRef paramArray(new PredSymbol::ParamArray);
                    paramArray->elemType = arraySym->getElementsType()->getTypeIndex();
                    paramArray->nDimensions = arraySym->getNDimensions();
                    param = paramArray;
                }
                else param.reset(new PredSymbol::Param);
                param->name = sym->getName();
                param->type = type;
                signature.params.emplace_back(param);
            }
            this->accessingNotLeafVariable = false;
        }

        // Check if a predicate with same signature is defined
        SymbolRef predSym = this->currentScope->resolve(signature.toStringSymTable());
        if (predSym == nullptr) {
            std::map<std::string, SymbolRef> symbols = st->gloabls->getScopeSymbols(); // pred definitions are global
            std::vector<std::pair<std::string, ExceptionLocation>> candidates;
            for (auto entry : symbols) {
                if (Utils::is<PredSymbol>(entry.second)) {
                    PredSymbolRef pred = Utils::as<PredSymbol>(entry.second);
                    const bool predHasSameName = Utils::string_split(entry.first, '(')[0] == signature.name;
                    if (predHasSameName) {
                        const std::string candName = pred->getSignature().toString();
                        ExceptionLocation candLoc = {
                                pred->getLocation().file,
                                pred->getLocation().line,
                                pred->getLocation().col
                        };
                        candidates.emplace_back(std::make_pair(candName, candLoc));
                    }
                }
            }
            throw CSP2SATPredNotExistsException(
                {
                    _includes.top(),
                    ctx->name->getLine(),
                    ctx->name->getCharPositionInLine()
                },
                signature.toString(),
                candidates
            );
        }

        return nullptr;
    }

    void checkPredCalls() {
        for (auto entry : st->gloabls->getScopeSymbols()) { // Assumes symbol table is ordered
            SymbolRef sym = entry.second;
            if (Utils::is<PredSymbol>(sym)) {
                PredSymbolRef predSym = Utils::as<PredSymbol>(sym);
                auto predCallsCtxs = VisitorsUtils::getRuleContextsRecursive<BUPParser::PredCallContext>(
                        predSym->getPredDefTree()->predDefBody());

                // Setup a mock environment to check if all predCalls are correct.
                // This is achieved declaring all parameters as dummy symbols in a new temporary local scope
                this->currentScope = LocalScope::Create(this->currentScope);
                for (PredSymbol::ParamRef p : predSym->getSignature().params) {
                    SymbolRef dummySym;
                    switch (p->type) {
                        case SymbolTable::tInt: {
                            auto assignableSym = AssignableSymbol::Create(p->name, Type::Create(SymbolTable::tInt, ""));
                            assignableSym->setValue(IntValue::Create(0));
                            dummySym = assignableSym;
                            break;
                        }
                        case SymbolTable::tBool: {
                            auto assignableSym = AssignableSymbol::Create(p->name, Type::Create(SymbolTable::tBool, ""));
                            assignableSym->setValue(BoolValue::Create());
                            dummySym = assignableSym;
                            break;
                        }
                        case SymbolTable::tVarBool:
                            dummySym = VariableSymbol::Create(p->name, literal());
                            break;
                        case SymbolTable::tArray: {
                            assert(Utils::is<PredSymbol::ParamArray>(p));
                            PredSymbol::ParamArrayRef pArray = Utils::as<PredSymbol::ParamArray>(p);
                            dummySym = ArraySymbol::Create(pArray->name, this->currentScope, Type::Create(pArray->elemType, ""));
                            break;
                        }
                        default:
                            throw std::invalid_argument("Type " + std::to_string(p->type) + " not supported");
                    }
                    Utils::as<BaseScope>(this->currentScope)->define(dummySym);
                }
                for (auto predCall : predCallsCtxs) {
                    try {
                        _includes.push(predSym->getLocation().file);
                        visit(predCall);
                        _includes.pop();
                    } catch (GOSException &e) {
                        std::cerr << e.getErrorMessage() << std::endl;
                    }
                }
                this->currentScope = this->currentScope->getEnclosingScope();
            }
        }
    }

    antlrcpp::Any visitPredDefBlock(BUPParser::PredDefBlockContext *ctx) override {
        try {
            // Store all defined predicates by its signature and pospose compilation
            BUPBaseVisitor::visitPredDefBlock(ctx);

            // Check predCalls inside predBodies (not compiling them, just checking correct predCalls). Otherwise, only
            // those predicates that happen to be called would be checked and compiled (due to the on-demand compilation)
            checkPredCalls();
        } catch (GOSException &e) {
            std::cerr << e.getErrorMessage() << std::endl;
        }
        return nullptr;
    }

    antlrcpp::Any visitPredDefBlockBody(BUPParser::PredDefBlockBodyContext *ctx) override {
        try {
            return BUPBaseVisitor::visitPredDefBlockBody(ctx);
        } catch (GOSException &e) {
            std::cerr << e.getErrorMessage() << std::endl;
        }
        return nullptr;
    }

    antlrcpp::Any visitVarDefinition(BUPParser::VarDefinitionContext *ctx) override {
        PredSymbol::ParamRef param;

        if (ctx->arrayDefinition() && !ctx->arrayDefinition()->children.empty()) {
            if(!ctx->arrayDefinition()->expr().empty()) {
                throw CSP2SATArrayBoundsException(
                        {
                                st->parsedFiles.front()->getPath(),
                                ctx->name->getLine(),
                                ctx->name->getCharPositionInLine()
                        }, false
                );
            }
            PredSymbol::ParamArrayRef paramArray(new PredSymbol::ParamArray);
            paramArray->type = SymbolTable::tArray;
            paramArray->elemType = SymbolTable::tVarBool;
            paramArray->nDimensions = ctx->arrayDefinition()->TK_LCLAUDATOR().size();
            param = paramArray;
        }
        else {
            param.reset(new PredSymbol::Param);
            param->type = SymbolTable::tVarBool;
        }
        param->name = ctx->name->getText();

        return param;
    }

    antlrcpp::Any visitParamDefinition(BUPParser::ParamDefinitionContext *ctx) override {
        PredSymbol::ParamRef param;

        const int type = Utils::as<Type>(currentScope->resolve(ctx->type->getText()))->getTypeIndex();
        if (ctx->arrayDefinition() && !ctx->arrayDefinition()->children.empty()) {
            if(!ctx->arrayDefinition()->expr().empty()) {
                throw CSP2SATArrayBoundsException(
                        {
                                st->parsedFiles.front()->getPath(),
                                ctx->name->getLine(),
                                ctx->name->getCharPositionInLine()
                        }, false
                );
            }
            PredSymbol::ParamArrayRef paramArray(new PredSymbol::ParamArray);
            paramArray->type = SymbolTable::tArray;
            paramArray->elemType = type;
            paramArray->nDimensions = ctx->arrayDefinition()->TK_LCLAUDATOR().size();
            param = paramArray;
        }
        else {
            param.reset(new PredSymbol::Param);
            param->type = type;
        }
        param->name = ctx->name->getText();

        return param;
    }

    antlrcpp::Any visitPredDef(BUPParser::PredDefContext *ctx) override {
        std::string name = ctx->name->getText();
        const size_t line = ctx->name->getLine();
        const size_t col = ctx->name->getCharPositionInLine();

        // Get whole predicate signature
        PredSymbol::Signature signature;
        signature.name = name;
        if(ctx->predDefParams()) {
            for (auto defCtx: ctx->predDefParams()->definition()) {
                try {
                    PredSymbol::ParamRef param = visit(defCtx);
                    signature.params.push_back(param);
                } catch (GOSException &e) {
                    std::cerr << e.getErrorMessage() << std::endl;
                }
            }
        }

        // Check if a predicate with same signature is already declared
        if(this->currentScope->existsInScope(signature.toStringSymTable())) {
            throw CSP2SATAlreadyExistException(
                {
                    _includes.top(),
                    line,
                    col
                },
                name
            );
        }

        // Define predicate symbol as global
        PredSymbol::Location loc = {_includes.top(), line, col};
        PredSymbolRef pred = PredSymbol::Create(signature, loc, ctx);
        st->gloabls->define(pred);

        return nullptr;
    }

    antlrcpp::Any visitPredInclude(BUPParser::PredIncludeContext *ctx) override {
        // Compute the path of the included file
        const std::string name = ctx->TK_STRING()->getText();
        std::filesystem::path filePath = name.substr(1, name.length()-2); // Trim double quotes
        if (filePath.is_relative())
            filePath = canonical(_includes.top().parent_path() / filePath);

        // Discard those files already included
        auto conditionFunc = [&] (const BUPFileRef& file) { return equivalent(file->getPath(),filePath); };
        const bool isFileAlreadyIncluded = std::find_if(st->parsedFiles.begin(), st->parsedFiles.end(), conditionFunc) != st->parsedFiles.end();
        if (!isFileAlreadyIncluded) {
            try {
                // Parse file and visit its subtree
                BUPFileRef file = BUPFile::Create(filePath);
                st->parsedFiles.emplace_back(file);
                _includes.push(filePath);
                visit(file->getParser()->predDefBlockBody());
                _includes.pop();
            } catch (std::ifstream::failure e) {
                std::cerr << "Error reading file: " << filePath.filename() << std::endl; // TODO GOSException
            }
        }
        else {
            std::cerr << "Warning: file " << filePath.filename() << " already included, parsing omitted" << std::endl;
        }

        return nullptr;
    }

private:
    std::stack<std::filesystem::path> _includes;
};

}

#endif //CSP2SAT_GOSPREDVISITOR_H
