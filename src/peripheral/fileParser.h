//
// Created by tlaber on 6/19/17.
//

#ifndef LINEARC_FILEPARSER_H
#define LINEARC_FILEPARSER_H

#include <fstream>
#include "stringParser.h"

class FileParser: public StringParser {
protected:
    string _file_name;
    int _line_number;
    bool _eof;
    std::ifstream _ifs;
public:
    int MAX_LINE_LEN;
    FileParser(const char*);
    FileParser();

    void parse(const char* filename);
    virtual void parse();
    void initialize();
    void set_line(string text);

    std::ifstream& getline_or_eof();
    std::ifstream& getline_nocomment(char comment=';');
    std::ifstream& get_real_line(char comment=';');
    std::ifstream& getline_nonempty();
    void remove_tail_comments(char comment=';');
};

#endif //LINEARC_FILEPARSER_H
