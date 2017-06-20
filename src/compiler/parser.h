//
// Created by tlaber on 6/19/17.
//

#ifndef LINEARC_PARSER_H
#define LINEARC_PARSER_H

#include "symbolTable.h"
#include <utilities/macros.h>
#include <peripheral/fileParser.h>
#include <map>

struct Token {
    string text;
    string category;
    string type; // for identifiers and constants
};



class CParser: public FileParser {
protected:
    Token _token;
    SymbolTable* _symbol_table;
public:
    CParser();
    void get_token(char delim=' ');
    void match_token(string cat, char delim=' ');
    void parse();
    void parse(const char*);

    void add_symbol(Symbol* value)                           { _symbol_table->add_symbol(value); }
//    Symbol* get_symbol(string key) {
//
//    }

    void do_globals();
    void do_global_variables();
    void do_function_declaration();
    void do_function_definition();
};




#endif //LINEARC_PARSER_H
