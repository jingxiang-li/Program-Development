#include "scanner.h"
#include <iostream>
#include "regex.h"

using namespace std;

Token::Token(string lexeme, tokenType terminal, Token *next) {
    cout << "Token is created, lexeme is " << lexeme << endl;
    this->lexeme = lexeme;
    this->terminal = terminal;
    this->next = next;
}

int Scanner::matchTokenType(char *text, tokenType terminal) {
    regex_t *re = NULL;
    int numMatchedChars = 0;
    switch (terminal) {
        // keywords
        case intKwd:
            re = makeRegex("^int");
            break;
        case floatKwd:
            re = makeRegex("^float");
            break;
        case stringKwd:
            re = makeRegex("^string");
            break;
        case matrixKwd:
            re = makeRegex("^matrix");
            break;
        case letKwd:
            re = makeRegex("^let");
            break;
        case inKwd:
            re = makeRegex("^in");
            break;
        case endKwd:
            re = makeRegex("^end");
            break;
        case ifKwd:
            re = makeRegex("^if");
            break;
        case thenKwd:
            re = makeRegex("^then");
            break;
        case elseKwd:
            re = makeRegex("^else");
            break;
        case repeatKwd:
            re = makeRegex("^repeat");
            break;
        case printKwd:
            re = makeRegex("^print");
            break;
        case toKwd:
            re = makeRegex("^to");
            break;

        // constants
        case intConst:
            re = makeRegex("^[0-9]+");
            break;
        case floatConst:
            re = makeRegex("^[0-9]+\\.[0-9]+");
            break;
        case stringConst:
            re = makeRegex("^\".*\"");
            break;

        // Names
        case variableName:
            re = makeRegex("^[_a-zA-Z]+[_a-zA-Z0-9]*");
            break;

        // Punctuation
        case leftParen:
            re = makeRegex("^\\(");
            break;
        case rightParen:
            re = makeRegex("^\\)");
            break;
        case leftCurly:
            re = makeRegex("^\\{");
            break;
        case rightCurly:
            re = makeRegex("^\\}");
            break;
        case leftSquare:
            re = makeRegex("^\\[");
            break;
        case rightSquare:
            re = makeRegex("^\\]");
            break;
        case semiColon:
            re = makeRegex("^;");
            break;
        case colon:
            re = makeRegex("^:");
            break;

        default:
            return 0;
    }
    if (re == NULL)
        perror("Failed to make regular expression");
    numMatchedChars = matchRegex(re, text);
    free(re);
    return numMatchedChars;
}
