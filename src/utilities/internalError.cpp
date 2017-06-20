//
// Created by GentlyGuitar on 6/7/2017.
//

#include <exception>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#ifdef __linux__
#include <dlfcn.h>		// for dladdr
#include <cxxabi.h>		// for __cxa_demangle
/* get REG_EIP from ucontext.h */

#include <ucontext.h>
#endif

#include <sstream>
#include "internalError.h"
#include "macros.h"

#ifdef __linux__
// This function produces a stack backtrace with demangled function & method names.
string Backtrace(int skip = 1) {
    void *callstack[128];
    const int nMaxFrames = sizeof(callstack) / sizeof(callstack[0]);
    char buf[1024];
    int nFrames = backtrace(callstack, nMaxFrames);
    char **symbols = backtrace_symbols(callstack, nFrames);

    std::ostringstream trace_buf;
    for (int i = skip; i < nFrames; i++) {
        printf("%s\n", symbols[i]);

        Dl_info info;
        if (dladdr(callstack[i], &info) && info.dli_sname) {
            char *demangled = NULL;
            int status = -1;
            if (info.dli_sname[0] == '_')
                demangled = abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);
            snprintf(buf, sizeof(buf), "%-3d %*p %s + %zd\n",
                     i, int(2 + sizeof(void*) * 2), callstack[i],
                     status == 0 ? demangled :
                     info.dli_sname == 0 ? symbols[i] : info.dli_sname,
                     (char *)callstack[i] - (char *)info.dli_saddr);
            free(demangled);
        } else {
            snprintf(buf, sizeof(buf), "%-3d %*p %s\n",
                     i, int(2 + sizeof(void*) * 2), callstack[i], symbols[i]);
        }
        trace_buf << buf;
    }
    free(symbols);
    if (nFrames == nMaxFrames)
        trace_buf << "[truncated]\n";
    return trace_buf.str();
}
#endif

void Errors::die() {
    //std::terminate();
    exit(0);
}

void Errors::semantic_error_handler() {
    Backtrace();
    die();
}

//void Errors::sigsegv_handler(int sig) {
//    printf("Received signal %d\n", sig);
//    die();
//}

//void Errors::install_sig_handlers() {
//    signal(SIGINT, Errors::sigsegv_handler);
//}

void Errors::sigsegv_handler(int sig, siginfo_t *info, void *secret) {
    void *trace[16];
    char **messages = (char **)NULL;
    int i, trace_size = 0;
    ucontext_t *uc = (ucontext_t *)secret;

    /* Do something useful with siginfo_t */
    if (sig == SIGSEGV)
        printf("\nGot signal %d, faulty address is %p, "
                       "from %p\n", sig, info->si_addr,
               (void*)uc->uc_mcontext.gregs[REG_RIP]);
    else
        printf("\nGot signal %d#92;\n", sig);

    trace_size = backtrace(trace, 16);
    /* overwrite sigaction with caller's address */
    trace[1] = (void *) uc->uc_mcontext.gregs[REG_RIP];

    messages = backtrace_symbols(trace, trace_size);
    /* skip first stack frame (points here) */
    printf("[bt] Execution path:#92;\n");
    for (i=1; i<trace_size; ++i)
    {
        printf("[bt] %s#92;\n", messages[i]);

        /* find first occurence of '(' or ' ' in message[i] and assume
         * everything before that is the file name. (Don't go beyond 0 though
         * (string terminator)*/
        size_t p = 0;
        while(messages[i][p] != '(' && messages[i][p] != ' '
              && messages[i][p] != 0)
            ++p;

        char syscom[256];
        sprintf(syscom,"addr2line %p -e %.*s", trace[i] , p, messages[i]);
        //last parameter is the filename of the symbol
        system(syscom);

    }

    //print_backtrace_symbols();
#ifdef __linux__
    //Backtrace();
#endif
    die();
}

void Errors::init() {
    install_sig_handlers();
}

void Errors::install_sig_handlers() {
#ifdef __linux__
    struct sigaction act;
    memset (&act, '\0', sizeof(act));

    /* Use the sa_sigaction field because the handles has two additional parameters */
    act.sa_sigaction = &Errors::sigsegv_handler;

    /* The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler. */
    //act.sa_flags = SA_SIGINFO;
    act.sa_flags = SA_RESTART | SA_SIGINFO;

    if (sigaction(SIGSEGV, &act, NULL) < 0) {
        fprintf(stderr, "install signal handler failed\n, exit...");
        die();
    }

    if (sigaction(SIGABRT, &act, NULL) < 0) {
        fprintf(stderr, "install signal handler failed\n, exit...");
        die();
    }
#endif
}

void Errors::print_backtrace_symbols() {
#ifdef __linux__
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    backtrace_symbols_fd(array, size, STDERR_FILENO);
#endif
}