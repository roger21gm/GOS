//
// Created by David on 18/07/2022.
//

#ifndef GOS_PARSER_H
#define GOS_PARSER_H

#include <BUPLexer.h>
#include <BUPParser.h>
#include <memory>
#include <filesystem>
#include <string>
#include <iostream>
#include "GOSUtils.h"

namespace GOS {

// Class to keep alive a Parser object and all its dependencies (since they are loaded on-demand
//BUFFEREDTOKENSTREAM.H---> This implementation of {@link TokenStream} loads tokens from a
//   * {@link TokenSource} on-demand, and places the tokens in a buffer to provide
//   * access to any previous token by index.

class BUPFile;
typedef std::shared_ptr<BUPFile> BUPFileRef;
class BUPFile {
public:
    static BUPFileRef Create(const std::filesystem::path& filePath) {
        return BUPFileRef(new BUPFile(filePath));
    }

    BUPParser* getParser() {
        return _parser.get();
    };

    std::filesystem::path getPath() {
        return _path;
    }

private:
    typedef std::shared_ptr<antlr4::CommonTokenStream> TokenStreamRef;
    typedef std::shared_ptr<antlr4::ANTLRInputStream> InputStreamRef;
    typedef std::shared_ptr<BUPLexer> BUPLexerRef;
    typedef std::shared_ptr<BUPParser> BUPParserRef;

    BUPFile(const std::filesystem::path& filePath) : _path(filePath) {
        std::string fileContent;
        try {
            fileContent = Utils::readFile(absolute(filePath));
        } catch(std::ifstream::failure e) {
            std::cerr << "Error reading file: " << filePath.filename() << std::endl;
            abort();
        }
        _inputStream = std::make_shared<antlr4::ANTLRInputStream>(fileContent);
        _lexer = std::make_shared<BUPLexer>(_inputStream.get());
        _tokenStream = std::make_shared<antlr4::CommonTokenStream>(_lexer.get());
        _parser = std::make_shared<BUPParser>(_tokenStream.get());
    }

    std::filesystem::path _path;
    BUPParserRef _parser;
    BUPLexerRef _lexer;
    TokenStreamRef _tokenStream;
    InputStreamRef _inputStream;
};

}

#endif //GOS_PARSER_H
