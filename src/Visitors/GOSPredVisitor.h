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
        _includes.push_back(filename);
    }

    antlrcpp::Any visitPredCall(BUPParser::PredCallContext *ctx) override { // TODO copied from GOSConstraintsVisitor. Maybe put in BUPBaseVisitor the common part?
        // Get call parameters
        std::vector<SymbolRef> paramsSymbols;
        PredSymbol::Signature signature;
        signature.name = ctx->name->getText();
        if (ctx->predCallParams()) {
            this->accessingNotLeafVariable = true; // TODO ask Mateu if this is correct
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
                else sym = res;
                paramsSymbols.emplace_back(sym);
                PredSymbol::Param param = {
                        "", // Not used to lookup the predicate in the symbol table
                        sym->getType()->getTypeIndex()
                };
                signature.params.emplace_back(param);
            }
            this->accessingNotLeafVariable = false;
        }

        // Check if a predicate with same signature is defined
        std::string predSignature = PredSymbol::signatureToSymbolTableName(signature);
        SymbolRef predSym = this->currentScope->resolve(predSignature);
        if (predSym == nullptr) {
            std::map<std::string, SymbolRef> symbols = this->currentScope->getScopeSymbols();
            const std::string predName = Utils::string_split(predSignature, '(')[0];
            std::vector<std::string> candidatesPredStr;
            for (auto entry : symbols) {
                if (Utils::string_split(entry.first, '(')[0] == predName) {
                    std::string candidateName = entry.second->getName();
                    candidatesPredStr.emplace_back(VisitorsUtils::parsePredicateString(candidateName));
                }
            }
            throw CSP2SATPredNotExistsException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    VisitorsUtils::parsePredicateString(predSignature),
                    candidatesPredStr
            );
        }

        return nullptr;
    }

    antlrcpp::Any visitPredDefBlock(BUPParser::PredDefBlockContext *ctx) override {
        try {
            // Store all defined predicates by its signature and pospose compilation
            BUPBaseVisitor::visitPredDefBlock(ctx);

            // Check predCalls inside predBodies (not compiling them, just checking correct predCalls). Otherwise, only
            // those predicates that happen to be called would be checked and compiled (due to the on-demand compilation)
            for (auto entry : st->gloabls->getScopeSymbols()) {
                SymbolRef sym = entry.second;
                if (Utils::is<PredSymbol>(sym)) {
                    PredSymbolRef predSym = Utils::as<PredSymbol>(sym);
                    for (auto constraintDef : predSym->getPredDefTree()->predDefBody()->constraintDefinition()) {
                        visit(constraintDef); // TODO visit only predcalls
                    }
                }
            }
        } catch (GOSException &e) {
            std::cerr << e.getErrorMessage() << std::endl;
        }
        return nullptr;
    }

    antlrcpp::Any visitVarDefinition(BUPParser::VarDefinitionContext *ctx) override {
        PredSymbol::ParamRef param(new PredSymbol::Param);
        param->name = ctx->name->getText();

        const bool isArray = ctx->arrayDefinition() && !ctx->arrayDefinition()->expr().empty();
        if (isArray)
            param->type = SymbolTable::tArray;
        param->type = SymbolTable::tVarBool;

        return param;
    }

    antlrcpp::Any visitParamDefinition(BUPParser::ParamDefinitionContext *ctx) override {
        PredSymbol::ParamRef param(new PredSymbol::Param);
        param->name = ctx->name->getText();

        const bool isArray = ctx->arrayDefinition() && !ctx->arrayDefinition()->expr().empty();
        if (isArray)
            param->type = SymbolTable::tArray;
        else
            param->type = Utils::as<Type>(currentScope->resolve(ctx->type->getText()))->getTypeIndex();

        return param;
    }

    antlrcpp::Any visitPredDef(BUPParser::PredDefContext *ctx) override {
        std::string name = ctx->name->getText();

        // Get whole predicate signature
        PredSymbol::Signature signature;
        signature.name = name;
        if(ctx->predDefParams()) {
            for (auto defCtx: ctx->predDefParams()->definition()) {
                PredSymbol::ParamRef param = visit(defCtx);
                signature.params.push_back(*param);
            }
        }

        // Check if a predicate with same signature is already declared
        if(this->currentScope->existsInScope(PredSymbol::signatureToSymbolTableName(signature))) {
            throw CSP2SATAlreadyExistException(
                ctx->name->getLine(),
                ctx->name->getCharPositionInLine(),
                name,
                _includes.back()
            );
        }

        PredSymbolRef pred = PredSymbol::Create(signature, ctx);
        currentScope->define(pred);
        //currentScope = pred;
        //SMTFormula* currentFormula = _f;
        //_f = new SMTFormula();
        //GOSConstraintsVisitor::visitConstraintDefinition(ctx->predDefBody()->constraintDefinition());
        //_f = currentFormula;
        //currentScope = currentScope->getEnclosingScope();

        return nullptr;
    }

    antlrcpp::Any visitPredDefParams(BUPParser::PredDefParamsContext *ctx) override {
        std::cout << "visitPredDefParams" << std::endl;
        return BUPBaseVisitor::visitPredDefParams(ctx);
    }

    antlrcpp::Any visitPredDefBody(BUPParser::PredDefBodyContext *ctx) override {
        return BUPBaseVisitor::visitPredDefBody(ctx);
    }

    antlrcpp::Any visitPredInclude(BUPParser::PredIncludeContext *ctx) override {
        const std::string name = ctx->TK_STRING()->getText();
        const std::filesystem::path filePath = name.substr(1, name.length()-2); // Trim double quotes
        _includes.push_back(filePath);

        // Compute the path of the included file
        std::filesystem::path wholePath;
        for (auto e : _includes) wholePath /= e.parent_path();
        wholePath /= filePath.filename();

        // Discard those files already included
        const bool isFileAlreadyIncluded = st->parsedFiles.find(wholePath) != st->parsedFiles.end();
        if (!isFileAlreadyIncluded) {
            try {
                // Parse file and visit its subtree
                BUPFileRef file = BUPFile::Create(wholePath);
                st->parsedFiles[wholePath] = file;
                visit(file->getParser()->predDefBlockBody());
            } catch (std::ifstream::failure e) {
                std::cerr << "Error reading file: " << filePath.filename() << std::endl; // TODO GOSException
            }
        }
        else {
            std::cerr << "Warning: file " << filePath.filename() << " already included, parsing omitted" << std::endl;
        }
        _includes.pop_back();

        return nullptr;
    }

private:
    std::vector<std::filesystem::path> _includes; // Included filenames stack, _includes.back() is the current include level
};

}

#endif //CSP2SAT_GOSPREDVISITOR_H
