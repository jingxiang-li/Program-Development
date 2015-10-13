/* A small meaningless comment */
#ifndef SCANNER_H
#define SCANNER_H

#include <regex.h>
#include <string>

using namespace std;

/* This enumerated type is used to keep track of what kind of
   construct was matched.
 */

enum tokenEnumType {

    intKwd,
    floatKwd,
    stringKwd,
    matrixKwd,
    letKwd,
    inKwd,
    endKwd,
    ifKwd,
    thenKwd,
    elseKwd,
    repeatKwd,
    printKwd,
    toKwd,

    // Constants
    intConst,
    floatConst,
    stringConst,

    // Names
    variableName,

    // Punctuation
    leftParen,
    rightParen,
    leftCurly,
    rightCurly,
    leftSquare,
    rightSquare,

    semiColon,
    colon,

    // Operators
    assign,
    plusSign,
    star,
    dash,
    forwardSlash,
    lessThan,
    lessThanEqual,
    greaterThan,
    greaterThanEqual,
    equalsEquals,
    notEquals,
    andOp,
    orOp,
    notOp,

    // Special terminal types
    endOfFile,
    lexicalError
};
typedef enum tokenEnumType tokenType;

// Below you need to write your class definitions for Token and Scanner.

class Token {
public:
    Token(string lexeme, tokenType terminal, Token *next);
    ~Token();

private:
    string lexeme;
    tokenType terminal;
    Token *next;
};

class Scanner {
public:
    Scanner();
    ~Scanner();
    /**
     * scan the input text and return a list of Tokens parsed from the text
     * @param  text input string
     * @return      On success, a pointer pointing to the head of the list of
     * Tokens; otherwise NULL
     */
    Token *scan(char *text);

private:
    // head and tail pointer for the list of Tokens
    Token *head = NULL;
    Token *tail = NULL;
    /**
     * given the input text and the token type, return the length of the
     * matched string
     * @param  text     input string
     * @param  terminal the type of token
     * @return          On success, length of the matched string; otherwise -1;
     */
    int matchTokenType(char *text, tokenType terminal);
    /**
     * given the input text, return the matched Token
     * @param  text input string
     * @return      On success, create a Token instance and return a pointer
     * to this instance; otherwise NULL
     */
    Token *matchToken(char *text);
    /**
     * make a list of Tokens given the input text, head and tail will be
     * modified after calling this function
     * @param  text input string
     * @return      0 on success, -1 on faliure.
     */
    int makeTokenList(char *text);
};

#endif /* SCANNER_H */
