#include "./regex.h"
#include "scanner.h"
#include "string.h"
#include <iostream>

using namespace std;

Token::Token(string lexeme, tokenType terminal, Token *next) {
    // cout << "Token is created, lexeme is " << lexeme << endl;
    this->lexeme = lexeme;
    this->terminal = terminal;
    this->next = next;
}

/**
 * given the input text and the token type, return the length of the
 * matched string
 * @param  text     input string
 * @param  terminal the type of token
 * @return          On success, length of the matched string; otherwise -1;
 */
int Scanner::matchTokenType(const char *text, tokenType terminal) {
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
        case boolKwd:
            re = makeRegex("^boolean");
            break;
        case trueKwd:
            re = makeRegex("^true");
            break;
        case falseKwd:
            re = makeRegex("^false");
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
        case whileKwd:
            re = makeRegex("^while");
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
            re = makeRegex("^\"[^\"]*\"");
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

        // Operators
        case assign:
            re = makeRegex("^\\=");
            break;
        case plusSign:
            re = makeRegex("^\\+");
            break;
        case star:
            re = makeRegex("^\\*");
            break;
        case dash:
            re = makeRegex("^\\-");
            break;
        case forwardSlash:
            re = makeRegex("^/");
            break;
        case lessThan:
            re = makeRegex("^<");
            break;
        case lessThanEqual:
            re = makeRegex("^<=");
            break;
        case greaterThan:
            re = makeRegex("^>");
            break;
        case greaterThanEqual:
            re = makeRegex("^>=");
            break;
        case equalsEquals:
            re = makeRegex("^==");
            break;
        case notEquals:
            re = makeRegex("^!=");
            break;
        case andOp:
            re = makeRegex("^&&");
            break;
        case orOp:
            re = makeRegex("^\\|\\|");
            break;
        case notOp:
            re = makeRegex("^!");
            break;

        // Special Terminal Types
        case endOfFile:
            // re = makeRegex("^$");
            if (strlen(text) == 0)
                return 1;
            else
                return 0;
            break;
        default:
            return 0;
    }

    if (re == NULL) {
        cerr << "Failed to make regular expression" << endl;
        return -1;
    }

    numMatchedChars = matchRegex(re, text);

    return numMatchedChars;
}

/**
 * match white space and comments, modified from WordCount.cpp
 * @param  text input text
 * @return      the length of string that contains space or comments
 */
int Scanner::consumeWhiteSpaceAndComments(const char *text) {
    regex_t *whiteSpace = makeRegex("^[\n\t\r ]+");
    regex_t *blockComment = makeRegex("^/\\*([^\\*]|\\*+[^\\*/])*\\*+/");
    regex_t *lineComment = makeRegex("^//[^\n]*\n");

    int numMatchedChars = 0;
    int totalNumMatchedChars = 0;
    int stillConsumingWhiteSpace;

    do {
        stillConsumingWhiteSpace = 0;  // exit loop if not reset by a match

        // Try to match white space
        numMatchedChars = matchRegex(whiteSpace, text);
        totalNumMatchedChars += numMatchedChars;
        if (numMatchedChars > 0) {
            text = text + numMatchedChars;
            stillConsumingWhiteSpace = 1;
        }

        // Try to match block comments
        numMatchedChars = matchRegex(blockComment, text);
        totalNumMatchedChars += numMatchedChars;
        if (numMatchedChars > 0) {
            text = text + numMatchedChars;
            stillConsumingWhiteSpace = 1;
        }

        // Try to match line comments
        numMatchedChars = matchRegex(lineComment, text);
        totalNumMatchedChars += numMatchedChars;
        if (numMatchedChars > 0) {
            text = text + numMatchedChars;
            stillConsumingWhiteSpace = 1;
        }
    } while (stillConsumingWhiteSpace);

    return totalNumMatchedChars;
}

/**
 * given the input text match the Token and return the length of
 * the matched characters
 * @param  text        input string
 * @param  mathedToken a reference to the pointer to the Token instance,
 * which will be modified by this function
 * @return             On success, return the nubmer of mached characters;
 * otherwise -1;
 */
int Scanner::matchToken(const char *text, Token *&matchedToken) {
    /**
     * iterate through all tokens by using a for loop and find the one
     * that gives the maximum match length. Note that the order of
     * tokens is very important. For example, "int" will be matched
     * by both intKwd and variableName with exactly the same length, and we
     * want it to be intKwd, not variableName.
     */

    int maxNumMatchedChars = -1;
    tokenType matchedType = lexicalError;

    for (int tokenTypeIndex = intKwd; tokenTypeIndex < lexicalError;
         tokenTypeIndex++) {
        tokenType currentType = static_cast<tokenType>(tokenTypeIndex);
        int numMatchedChars = matchTokenType(text, currentType);

        if (numMatchedChars > maxNumMatchedChars) {
            // this is strictly larger than, if we have two match with
            // same length then priority is given to the first one
            // that was tried.

            maxNumMatchedChars = numMatchedChars;
            matchedType = currentType;
        }
    }

    if (maxNumMatchedChars == -1) {
        cerr << "Failed to parse the token, didn't match any token type"
             << endl;
        return -1;
    }

    if (maxNumMatchedChars == 0) {
        matchedType = lexicalError;
        maxNumMatchedChars = 1;
    }

    string lexeme(text, 0, maxNumMatchedChars);
    tokenType terminal = matchedType;
    matchedToken = new Token(lexeme, terminal, NULL);

    if (matchedToken == NULL) {
        cerr << "Failed to allocate memory for the token" << lexeme << endl;
        return -1;
    }

    return maxNumMatchedChars;
}

/**
 * make a list of Tokens given the input text, head and tail will be
 * modified after calling this function
 * @param  text input string
 * @return      on success, return the pointer to the head of the list;
 * otherwise NULL
 */
Token *Scanner::makeTokenList(const char *text) {
    // int totalLength = strlen(text);
    head = NULL;
    tail = NULL;
    Token *matchedToken;
    do {
        int skipLength = consumeWhiteSpaceAndComments(text);
        text += skipLength;
        // totalLength -= skipLength;
        // if (totalLength <= 0) break;

        int matchedLength = matchToken(text, matchedToken);

        if (matchedToken == NULL) return NULL;

        if (head == NULL && tail == NULL) {
            head = matchedToken;
            tail = head;
        } else {
            tail->next = matchedToken;
            tail = tail->next;
        }

        text += matchedLength;
        // totalLength -= matchedLength;
    } while (tail->terminal != endOfFile);
    return head;
}

/**
 * scan the input text and return a list of Tokens parsed from the text
 * @param  text input string
 * @return      On success, a pointer pointing to the head of the list of
 * Tokens; otherwise NULL
 */
Token *Scanner::scan(const char *text) { return makeTokenList(text); }
