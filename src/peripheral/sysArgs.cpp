//
// Created by tlaber on 6/14/17.
//

#include <utilities/flags.h>
#include <peripheral/timer.h>
#include "argsParser.h"
#include "sysArgs.h"
#include "utilities/strings.h"

std::vector<string> SysArgs::_filenames;
std::map<string, string> SysArgs::_properties;
std::set<string> SysArgs::_flags;


void SysArgs::add_target_file(string name) {
    _filenames.push_back(name);
}

string SysArgs::get_property(string key) {
    if (_properties.find(key) == _properties.end()) {
        return "";
    } else {
        return _properties[key];
    }
}