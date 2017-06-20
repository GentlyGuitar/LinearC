
## LinearC

LinearC is an intermediate language between LLVM IR and C. It has features from both languages. 

It's more more readable than LLVM IR because it still uses most of C's operators.

It's very easy to parse because it is three address code based and has a very modified C grammar. 
The grammar is modified so that it is closer to LL(1), though it is still LL(2), if not considering 
the "typedef-name: identifier" problem. 

One can write a predictive parser for it within a few hours. It's even faster than learning how to use `lex` and `yacc`, 
and also more rewarding.


## Overview

The grammar requires blank space to be used as delimiter for tokens so that the lexical work can be minimized.

The parser also follows a "lexical analysis -> syntactic analysis -> semantic analysis" flow, although the lexer 
is very tiny.

The lexer returns a token at a time, each token contains a terminal symbol and the type of the token. 

A terminal symbol can only either be reserved word, identifier or constant. Otherwise a lexical error is thrown.

If no derivation can be found, throw a syntactic error such as UnexpectedToken.

If referencing undefined symbol, or type mismatch found, throw a semantic error. 

A symbol carries a type information if it's of type identifier or constant. Type check is forced for every operator and assignment. 


- No "unsigned" or "signed" keyword. All types are signed.

- No "const" because "const" greatly increases the complexity of a parser.


## Grammar

This grammar is written with a combination of BNF and regular expression, but it should be straightforward to understand.

```
primitive : "int"
          | "float"

type : (storage)? primitive (\*)*  # more

storage : "static"
        | "extern"  

identifier : (?!reserved)[a-zA-Z]+

reserved : "if"
         | "else"
         | "while"
         | "break"
         | "continue"
         | "return"
         | "eval"
         | primitive
         | storage

global : type identifier ('=' constant)
       | "declare" type identifier '(' arguments ')'
       | "define" type identifier '(' arguments ')' '{'
             (statement)* 
         '}'

argument : type identifier (',' type identifier)*

statement : "eval" expression
          | identifier '=' expression
          | type identifier ('='' expression)?
          | "if" '(' expression ')' '{'
                (statement)*
            '}' 
          | "while" '(' expression ')' '{'
                (statement)*
            '}' 
          | "return"
          | "break"
          | "continue"

constant : [0-9]+
         | [0-9]+ '.' [0-9]+
         | '"' [a-zA-Z]+ '"'

expression : identifier '(' arguments ')'
           | identifier [+\-*/] identifier
           | constant

program ： (global)*
```