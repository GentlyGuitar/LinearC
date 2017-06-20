//
// Created by tlaber on 6/14/17.
//

#include "stringParser.h"



StringParser::StringParser() {
    MAX_VALUE_LEN = 1024;
    _text = "";
    _intext_pos = 0;
    _char = 0;
    _eol = false;
}

void StringParser::set_text(const string & text) {
    _text = text;
    _intext_pos = 0;
    _char = _text[_intext_pos];
    _eol = false;
}

void StringParser::get_word(char delim, bool append_delim, bool skip_delim, bool skip_ws) {
    guarantee(_intext_pos < _text.size(), "inline pointer out of range");
    guarantee(_char == _text[_intext_pos], "_char: %c, _text[_intext_pos]: %c", _char, _text[_intext_pos]);

    if (skip_ws) {
        while (_text[_intext_pos] == ' ' || _text[_intext_pos] == '\t' || _text[_intext_pos] == '\n') {
            inc_intext_pos();
            if (_eol) {
                break;
            }
        }
    }

    if (_eol) {
        return;
    }

    int startp = _intext_pos;
    int len = 0;
    while (_text[_intext_pos] != delim) {
        inc_intext_pos();
        len++;
        if (_eol) {
            break;
        }
    }

    _word = _text.substr(startp, len);
    if (append_delim) {
        _word += delim;
        zpl("append %c", delim);
    }

    if (skip_delim) {
        if (!_eol) {
            inc_intext_pos();
        }
    }
}

void StringParser::get_char(bool skip_ws) {
    guarantee(_intext_pos < _text.size(), "inline pointer out of range");
    guarantee(_char == _text[_intext_pos], "_char: %c, _text[_intext_pos]: %c", _char, _text[_intext_pos]);

    if (skip_ws) {
        while (_text[_intext_pos] == ' ' || _text[_intext_pos] == '\t' || _text[_intext_pos] == '\n') {
            inc_intext_pos();
            if (_eol) {
                break;
            }
        }
    }

    if (_eol) {
        _char = '\0';
    }
    else {
        _char = _text[_intext_pos];
    }
}

void StringParser::inc_intext_pos(int steps) {
    guarantee(_intext_pos < _text.size(), "inline pointer out of range");
    guarantee(_char == _text[_intext_pos], "_char: %c, _text[_intext_pos]: %c", _char, _text[_intext_pos]);

    _intext_pos += steps;
    if (_intext_pos > _text.size()-1) {
        _eol = true;  // _intext_pos is no longer valid
    }
    else {
        _char = _text[_intext_pos];
    }
}