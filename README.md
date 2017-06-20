
## LinearC

LinearC is an intermediate language between LLVM IR and C. It has features from both languages. 

It's more more readable than LLVM IR because it still uses most of C's operators.

It's very easy to parse because it is three address code based and has a very strict grammar. 
One can write a predictive parser for it without a few hours without using `lex` and `yacc`. 
Without supporting for `typedef`, LinearC is LL(2) and very close to LL(1). 




## Overview


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

type : (storage)* primitive (\*)*  # more


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
         | type-desc


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