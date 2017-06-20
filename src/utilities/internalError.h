//
// Created by GentlyGuitar on 6/7/2017.
//

#ifndef LLPARSER_EXCEPTION_H
#define LLPARSER_EXCEPTION_H

#include <stdexcept>

#ifdef __linux__
#include <execinfo.h>
#endif
#include <signal.h>


class Errors {
public:
    static void init();
    static void install_sig_handlers();
    static void semantic_error_handler();
    static void sigsegv_handler(int sig, siginfo_t *siginfo, void *context);
    //static void sigsegv_handler(int sig);
    static void print_backtrace_symbols();
    static void die();
};


class UnexpectedTokenError: public std::runtime_error {
public:
    UnexpectedTokenError(std::string msg): runtime_error(msg) {}
    UnexpectedTokenError(): runtime_error("") {}
};

class TypeError: public std::runtime_error {
public:
    TypeError(std::string msg): runtime_error(msg) {}
    TypeError(): runtime_error("") {}
};


#endif //LLPARSER_EXCEPTION_H
