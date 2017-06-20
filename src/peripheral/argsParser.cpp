//
// Created by tlaber on 6/14/17.
//

#include <fstream>
#include <utilities/strings.h>
#include <cstring>
#include <utilities/flags.h>
#include "argsParser.h"
#include "sysArgs.h"

void ArgsParser::parse_config_files() {
    const char* home = std::getenv("HOME");
    guarantee(home != NULL, "$HOME is not set");

    string pass_ld_config = home;
    pass_ld_config += "/.sopt/config";
    std::ifstream ifs;
    ifs.open(pass_ld_config);
    if (ifs.good()) {
        string line;
        while (std::getline(ifs, line)) {
            if (line[0] == ';') {
                continue;
            }
            set_text(line);
            if (Strings::startswith(_text, "ld-pass-path")) {
                inc_intext_pos(strlen("ld-pass-path"));
                get_word('=');
                get_word(','); // todo: ',' is just a randomly chosen delimiter
                SysArgs::set_property("ld-pass-path", _word);
            }
        }
    }
}

void ArgsParser::parse_args(SoptInitArgs* init_args) {
    parse_config_files();

    //zpl("%p, %p", &PrintParsedLine, &UseParseTimePasses);
    for (int i = 1; i < init_args->argc; ++i) {
        string this_arg = init_args->argv[i];
        set_text(this_arg);
        if (Strings::startswith(_text, "-XX:")) {
            int xx_len = strlen("-XX:");
            if (_text[xx_len] == '+') {
                Flags::set_flag(_text.substr(xx_len+1), true);
            }
            else if (_text[xx_len] == '-') {
                Flags::set_flag(_text.substr(xx_len+1), false);
            }
            else {
                guarantee(0, "assignment not supported");
            }
        }
        else if (Strings::startswith(_text, "--")) {
            parse_long_option();
        }
        else if (Strings::startswith(_text, "-")) {
            parse_short_flag();
        }
        else {
            SysArgs::add_target_file(_text);
        }

    }
}

void ArgsParser::parse_short_flag() {
    get_word();
    if (_word == "-g") {
        SysArgs::set_flag("debug-info");
    }
}

void ArgsParser::parse_long_option() {
    get_word('=');
    if (_word == "--load") {
        get_word();
        _passes = Strings::split(_word, ',');
        if (_passes.size() == 0) {
            _passes = Strings::split(_word, '+');
        }
        guarantee(_passes.size() != 0, ".");
    } else if (_word == "--ld-pass-path") {
        get_word();
        SysArgs::set_property("ld-pass-path", _word);
    }
    else if (_word == "--o") {
        get_word();
        SysArgs::set_property("output", _word);
    }
}
