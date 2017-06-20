//
// Created by tlaber on 6/19/17.
//

#include <utilities/strings.h>
#include <regex>
#include <utilities/internalError.h>
#include "parser.h"

CParser::CParser() {
    _symbol_table = new SymbolTable();
}

void CParser::get_token(char delim) {
    get_word(delim);

    std::regex primitive("int|float");
    std::regex identifier("[a-zA-Z][a-zA-Z0-9_]*");
    std::regex const_int("[1-9][0-9]*");
    std::regex const_float("[0-9]+\\.[0-9]+");
    if (std::regex_match(_word, primitive)) {
        _token.category = "primitive type";
    }
    else if (std::regex_match(_word, identifier)) {
        _token.category = "identifier";
    }
    else if (std::regex_match(_word, const_int)) {
        _token.category = "constant";
        _token.type = "int";
    }
    else if (std::regex_match(_word, const_float)) {
        _token.category = "constant";
        _token.type = "float";
    }
    else {
        _token.category = _word;
    }

    _token.text = _word;
}

void CParser::match_token(string cat, char delim) {
    get_token(delim);
    if (cat != _token.category) {
        throw std::runtime_error("expect token category:" + cat + '\n');
    }
}

void CParser::parse() {
    _ifs.open(_file_name);
    if (!_ifs.good()) {
        fprintf(stderr, "open file %s failed, exit\n", _file_name.c_str());
    }
    _symbol_table->enter_scope();
    do_globals();
    _symbol_table->exit_scope();
}

void CParser::do_globals() {
    while (!_eof) {
        zpl("eof: %d", _eof);
        get_real_line();
        if (_eof) {
            break;
        }
        remove_tail_comments();
        get_token();
        if (_token.category == "primitive type") {
            do_global_variables();
        }
        else if (_token.category == "declare") {
            do_function_declaration();
        }
        else if (_token.category == "define") {
            do_function_definition();
        }
    }
}

void CParser::do_global_variables() {
    Token ty = _token;
    get_token();
    Token id = _token;
    guarantee(id.category == "identifier", "Bad identifier: %s", _text.c_str());
    Symbol* symbol = new Symbol();
    symbol->set_name(id.text);
    symbol->set_type(ty.text);
    add_symbol(symbol);
    if (!_eol) {
        match_token("=");
        match_token("constant");
        if (_token.type != symbol->type()) {
            throw TypeError();
        }
    }
    zpl("ty: %s, id: %s, end: %d", ty.text.c_str(), id.text.c_str(), _eol);
}

void CParser::do_function_declaration() {

}

void CParser::do_function_definition() {

}

void CParser::parse(const char * filename) {
    FileParser::parse(filename);
}