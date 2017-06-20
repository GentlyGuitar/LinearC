//
// Created by tlaber on 6/14/17.
//

#ifndef LLPARSER_STRINGPARSER_H
#define LLPARSER_STRINGPARSER_H

#include "utilities/macros.h"

class StringParser {
protected:
    string _text;
    int _intext_pos;
    string _word;
    char _char;
    int _eol;
public:
    int MAX_VALUE_LEN;

    StringParser();

    void set_text(const string& );

    void get_word(char delim=' ', bool append_delim=0, bool skip_delim=1, bool skip_ws=1); // return a string

    void get_char(bool skip_ws=1);
    void inc_intext_pos(int steps=1);
};

#endif //LLPARSER_STRINGPARSER_H
