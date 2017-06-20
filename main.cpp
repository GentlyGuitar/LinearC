#include <iostream>
#include <compiler/parser.h>

int main() {
    Errors::init();

    CParser p;
    p.parse("../../test/exchange.lc");
    return 0;
}