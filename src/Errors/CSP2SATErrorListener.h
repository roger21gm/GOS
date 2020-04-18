//
// Created by Roger Generoso Masós on 13/04/2020.
//

#ifndef CSP2SAT_CSP2SATERRORLISTENER_H
#define CSP2SAT_CSP2SATERRORLISTENER_H

#include <CSP2SATLexer.h>

using namespace CSP2SAT;
using namespace antlr4;

class CSP2SATErrorListener : public ANTLRErrorListener {


public:
    ~CSP2SATErrorListener() override {

    }

    void syntaxError(Recognizer *recognizer, Token *offendingSymbol, size_t line, size_t charPositionInLine,
                     const std::string &msg, std::exception_ptr e) override {

    }

    void reportAmbiguity(Parser *recognizer, const dfa::DFA &dfa, size_t startIndex, size_t stopIndex, bool exact,
                         const antlrcpp::BitSet &ambigAlts, atn::ATNConfigSet *configs) override {

    }

    void reportAttemptingFullContext(Parser *recognizer, const dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
                                     const antlrcpp::BitSet &conflictingAlts, atn::ATNConfigSet *configs) override {

    }

    void reportContextSensitivity(Parser *recognizer, const dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
                                  size_t prediction, atn::ATNConfigSet *configs) override {

    }
};


#endif //CSP2SAT_CSP2SATERRORLISTENER_H
