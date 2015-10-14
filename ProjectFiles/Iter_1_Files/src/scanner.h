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
    string lexeme;
    tokenType terminal;
    Token *next;

    Token(string lexeme, tokenType terminal, Token *next);
    ~Token();
};

class Scanner {
public:
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
     * given the input text match the Token and return the length of
     * the matched characters
     * @param  text        input string
     * @param  mathedToken a reference to the pointer to the Token instance,
     * which will be modified by this function
     * @return             On success, return the nubmer of mached characters;
     * otherwise -1;
     */
    int matchToken(char *text, Token *&matchedToken);

    /**
     * match white space and comments, modified from WordCount.cpp
     * @param  text input text
     * @return      the length of string that contains space or comments
     */
    int consumeWhiteSpaceAndComments(char *text);

    /**
     * make a list of Tokens given the input text, head and tail will be
     * modified after calling this function
     * @param  text input string
     * @return      on success, return the pointer to the head of the list;
     * otherwise NULL
     */
    Token *makeTokenList(char *text);
};

#endif /* SCANNER_H */
