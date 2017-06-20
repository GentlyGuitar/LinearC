//
// Created by tlaber on 6/19/17.
//

#include <utilities/flags.h>
#include <utilities/strings.h>
#include "fileParser.h"



FileParser::FileParser(const char* file) {
    _file_name = file;
    initialize();
}

FileParser::FileParser() {
    initialize();
}

void FileParser::initialize() {
    MAX_LINE_LEN = 4096;
    MAX_VALUE_LEN = 1024;
    _line_number = 0;
    _intext_pos = 0;
    _eof = false;
}

void FileParser::set_line(string text) {
    _text = text;
    _intext_pos = 0;
    _char = _text[_intext_pos];
    _eol = false;
}

std::ifstream& FileParser::getline_or_eof() {
    if (std::getline(_ifs, _text)) {
        _line_number++;
        _intext_pos = 0;
        _char = _text[_intext_pos];
        _eol = false;

#ifdef __CYGWIN__
        assert(_text[_text.size()-1] == '\r' && "Windows new line encoding should be \\r\\n");
        _text = _text.substr(0, _text.size()-1);
#endif
        if (PrintParsedLine) {
            printf("%d: %s\n", _line_number, _text.c_str());
        }

    }
    else {
        _eof = true;
    }
    return _ifs;
}

std::ifstream& FileParser::getline_nocomment(const char* head) {
    getline_or_eof();

    if (_eof) {
        return _ifs;
    }

    while (!_eof && Strings::startswith(_text, head)) {
        getline_or_eof();
    }

    return _ifs;
}

std::ifstream& FileParser::get_real_line(const char* head) {
    getline_or_eof();

    if (_eof) {
        return _ifs;
    }

    while (!_eof && (_text.empty() || Strings::startswith(_text, head))) {
        getline_or_eof();
    }

    return _ifs;
}

std::ifstream& FileParser::getline_nonempty() {
    getline_or_eof();

    if (_eof) {
        return _ifs;
    }

    while (_text.empty()) {
        getline_or_eof();
    }

    return _ifs;
}

void FileParser::remove_tail(const char* delim) {
    int pos = _text.find(delim);
    set_text(_text.substr(0, pos));
}

void FileParser::parse(const char *filename) {
    _file_name = filename;
    parse();
}

void FileParser::parse() {
    std::cout << "FileParser.parse() called. Do nothing.\n";
}