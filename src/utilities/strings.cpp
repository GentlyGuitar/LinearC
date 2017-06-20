//
// Created by GentlyGuitar on 6/6/2017.
//

#include <sstream>
#include "strings.h"

std::vector<std::string> Strings::split(char* s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> Strings::split(const std::string  &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

bool Strings::startswith(const std::string  &s, const char *substr, bool skip_nw) {
    std::string ss(substr);
    return Strings::startswith(s, ss, skip_nw);
}

bool Strings::startswith(const std::string  &s, std::string substr, bool skip_nw) {
    std::string newstr;
    if (skip_nw) {
        int real_start = s.find_first_not_of(" \t");
        if (real_start == s.npos) {
            return false;
        }
        else {
            newstr = s.substr(real_start);
        }
    }
    else {
        newstr = s;
    }

    if (newstr.find(substr) == 0) {
        return true;
    }
    else {
        return false;
    }
}

char Strings::first_nonws_char(const std::string  &s) {
    std::size_t found = s.find_first_not_of(" \t");
    if (found != std::string::npos) {
        return s[found];
    }
    else {
        return 0;
    }
}

bool Strings::endswith(const std::string  &s, const char *ending) {
    return Strings::endswith(s, std::string(ending));
}

bool Strings::endswith(const std::string  &s, std::string ending) {
    if (ending.size() > s.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), s.rbegin());
}

bool Strings::is_number(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool Strings::replace(std::string  &s, std::string &oldsub, std::string& newsub) {
    int pos = s.find(oldsub);
    if (pos == s.npos) {
        return false;
    }
    else {
        s.replace(pos, oldsub.size(), newsub);
        return true;
    }
}

bool Strings::replace(std::string  &s, const char *oldsub, std::string &newsub) {
    std::string o = oldsub;
    return replace(s, o, newsub);
}

bool Strings::replace(std::string  &s, std::string &oldsub, const char *newsub) {
    std::string n = newsub;
    return replace(s, oldsub, n);
}

bool Strings::replace(std::string  &s, const char *oldsub, const char *newsub) {
    std::string o = oldsub;
    std::string n = newsub;
    return replace(s, o, n);
}