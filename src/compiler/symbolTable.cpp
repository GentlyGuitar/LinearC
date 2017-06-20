//
// Created by tlaber on 6/19/17.
//

#include "symbolTable.h"


SymbolTable::SymbolTable() {
    _scope = -1;
}

void SymbolTable::enter_scope() {
    ++_scope;
    table_t new_table = new std::map<string, Symbol*>();
    _table_list.push_back(new_table);
}

void SymbolTable::exit_scope() {
    guarantee(_scope >= 0, "scope must be non-negative: %d", _scope);
    auto cur = _table_list[_table_list.size()-1];
    _table_list.pop_back();

    zpl("size: %d", cur->size());
    auto it = cur->begin();
    for (; it != cur->end(); ++it) {
        delete it->second;
    }
    delete cur;
}

void SymbolTable::add_symbol(Symbol *s) {
    table_t cur = _table_list[_scope];
    (*cur)[s->name()] = s;
}