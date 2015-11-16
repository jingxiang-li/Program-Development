/**
 * Scanner: a class contains method to parse from CDAL language text file
 * to a list of Tokens
 *
 * Author: Jingxiang Li, Tanoja Sunkam
 *
 * Last modified: Sun 15 Nov 2015 10:12:56 PM CST
 */

#ifndef SCANNER_H
#define SCANNER_H

#include "./regex.h"
#include <string>

using namespace std;

/**
 * This enumerated type is used to keep track of
 * what kind of token was matched.
 */
enum tokenEnumType {

    printKwd,
    floatKwd,
    boolKwd,
    trueKwd,
    falseKwd,
    stringKwd,
    matrixKwd,
    letKwd,
    inKwd,
    endKwd,
    ifKwd,
    thenKwd,
    elseKwd,
    repeatKwd,
    whileKwd,
    intKwd,
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

/**
 * Below is a class Token used for storing information of a single
 * token parsed from the text. A Token instance contains the a lexeme
 * (matched string), a terminal (type of the matched string) and a
 * next pointer pointing to the next Token.
 */
class Token {
public:
    string lexeme;
    tokenType terminal;
    Token *next;

    // Constructor for Token, initialize lexeme, terminal and next pointer
    Token(string lexeme, tokenType terminal, Token *next);
};

/**
 * Below is the class Scanner used for scanning the text and parsing it to a
 * list of Tokens
 */
class Scanner {
public:
    /**
     * Constructor for Scanner, initialize head, tail and regex_array
     * by calling initializeRegex()
     */
    Scanner();

    /**
     * Destructor of Scanner, delete the token list and regex_array
     */
    // ~Scanner();

    /**
     * scan the input text and return a list of Tokens parsed from the text
     * @param  text input string
     * @return      On success, a pointer pointing to the head of the list of
     * Tokens; otherwise NULL
     */
    Token *scan(const char *text);

    /**
     * given the input text match the Token and return the length of
     * the matched characters
     * @param  text        input string
     * @param  mathedToken a reference to the pointer to the Token instance,
     * which will be modified by this function
     * @return             On success, return the nubmer of mached characters;
     * otherwise -1;
     */
    int matchToken(const char *text, Token *&matchedToken);

private:
    // head and tail pointer for the list of Tokens
    Token *head;
    Token *tail;

    /**
     * array of regular expressions for each tokenType,
     * with length "lexicalError", it will be initialized
     * in the constructor of Scanner by calling function
     * initializeRegex()
     */
    regex_t **regex_array;

    /**
     * given the input text and the token type, return the length of the
     * matched string
     * @param  text     input string
     * @param  terminal the type of token
     * @return          On success, length of the matched string; otherwise -1;
     */
    int matchTokenType(const char *text, tokenType terminal);

    /**
     * match white space and comments, modified from WordCount.cpp
     * @param  text input text
     * @return      the length of string that contains space or comments
     */
    int consumeWhiteSpaceAndComments(const char *text);

    /**
     * make a list of Tokens given the input text, head and tail will be
     * modified after calling this function
     * @param  text input string
     * @return      on success, return the pointer to the head of the list;
     * otherwise NULL
     */
    Token *makeTokenList(const char *text);

    /**
     * initialize the regex_array, this function will be called
     * in the constructor of Scanner
     */
    void initializeRegex();
};

#endif /* SCANNER_H */
