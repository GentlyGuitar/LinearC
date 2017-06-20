//
// Created by tlaber on 6/19/17.
//

#ifndef LINEARC_SYMBOLTABLE_H
#define LINEARC_SYMBOLTABLE_H


#include <utilities/macros.h>
#include <map>

class Symbol {
    string _name;
    bool _is_defined;
    string _linkage;
    string _type;
public:
    void set_name(string name)                               { _name = name; }
    string name()                                            { return _name; }
    void set_type(string type)                               { _type = type; }
    string type()                                            { return _type; }
};


class SymbolTable {
    typedef std::map<string, Symbol*>* table_t;

    std::vector<table_t> _table_list;
    int _scope;
public:
    SymbolTable();
    void enter_scope();
    void exit_scope();

    void add_symbol(Symbol* s);
    Symbol* get_symbol();
};

#endif //LINEARC_SYMBOLTABLE_H
