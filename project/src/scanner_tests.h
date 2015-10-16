#include <cxxtest/TestSuite.h>

#include "readInput.h"
#include "scanner.h"
#include "./regex.h"
#include <stdio.h>
#include <string>
#include <cstring>
using namespace std;

class ScannerTestSuite : public CxxTest::TestSuite {
public:
    /* A Scanner object is created in the test_setup_code method.
       This is a test, beginning with "test_", so that it is executed
       by the testing framework.  The scanner is used in some tests of
       the method "scan".
     */
    Scanner *s;
    void test_setup_code() { s = new Scanner(); }

    // Tests for components and functions used by "scan"
    // --------------------------------------------------

    /* You should test the regular expressions you use to make and match
       regular expressions,and the functions used by makeRegex and
       matchRegex using regex_tests.h.
       However, You will likely need to write several tests to
       adequately test  the functions that are called from "scan".
       Once you are confident that the components used by "scan"
       work properly, then you can run tests on the "scan" method itself.
    */

    // You should place tests for these other functions used by
    // scan below.

    /* Below is one of the tests for these components in the project
       solution created by your instructor.  It uses a helper
       function function called "tokenMaker_tester", which you have
       not been given.  You are expected to design your own components
       for "scan" and your own mechanisms for easily testing them.

        void xtest_TokenMaker_leftCurly ( ) {
            tokenMaker_tester ("{ ", "^\\{", leftCurly, "{" ) ;
        }

        Note that this test is here named "xtest_Token..." The leading
        "x" is so that cxxTest doesn't scan the line above and think
        it is an actual test that isn't commented out.  cxxTest is
        very simple and doesn't even process block comments.
    */

    /* You must have at least one separate test case for each terminal
       symbol.  Thus, you need a test that will pass or fail based
       solely on the regular expression (and its corresponding code)
       for each terminal symbol.

       This requires a test case for each element of the enumerated
       type tokenType.  This may look something like the sample test
       shown in the comment above.
    */

    void tokenMaker_tester(const char *text, const char *pattern,
                           tokenType terminal, const char *lexeme_target) {
        Token *head = s->scan(text);
        TS_ASSERT(head->lexeme == string(lexeme_target));
        TS_ASSERT(head->terminal == terminal);
    }

    void test_terminal_intKwd() {
        tokenMaker_tester("int ", "^int", intKwd, "int");
    }

    void test_terminal_floatKwd() {
        tokenMaker_tester("float ", "^float", floatKwd, "float");
    }

    void test_terminal_stringKwd() {
        tokenMaker_tester("string ", "^string", stringKwd, "string");
    }

    void test_terminal_matrixKwd() {
        tokenMaker_tester("matrix ", "^matrix", matrixKwd, "matrix");
    }

    void test_terminal_letKwd() {
        tokenMaker_tester("let ", "^let", letKwd, "let");
    }

    void test_terminal_inKwd() { tokenMaker_tester("in ", "^in", inKwd, "in"); }

    void test_terminal_endKwd() {
        tokenMaker_tester("end ", "^end", endKwd, "end");
    }

    void test_terminal_ifKwd() { tokenMaker_tester("if ", "^if", ifKwd, "if"); }

    void test_terminal_thenKwd() {
        tokenMaker_tester("then ", "^then", thenKwd, "then");
    }

    void test_terminal_elseKwd() {
        tokenMaker_tester("else ", "^else", elseKwd, "else");
    }

    void test_terminal_repeatKwd() {
        tokenMaker_tester("repeat ", "^repeat", repeatKwd, "repeat");
    }

    void test_terminal_printKwd() {
        tokenMaker_tester("print ", "^print", printKwd, "print");
    }

    void test_terminal_toKwd() { tokenMaker_tester("to ", "^to", toKwd, "to"); }

    void test_terminal_intConst() {
        tokenMaker_tester("132169080;", "^[0-9]+", intConst, "132169080");
    }

    void test_terminal_floatConst() {
        tokenMaker_tester("0.0;", "^[0-9]+\\.[0-9]+", floatConst, "0.0");
        tokenMaker_tester("1.234;", "^[0-9]+\\.[0-9]+", floatConst, "1.234");
    }

    void test_terminal_stringConst() {
        tokenMaker_tester("\"asdfdasf\";", "^\"[^\"]*\"", stringConst,
                          "\"asdfdasf\"");
    }

    void test_terminal_variableName() {
        tokenMaker_tester("_00_abDA__997 ", "^[_a-zA-Z]+[_a-zA-Z0-9]*",
                          variableName, "_00_abDA__997");
    }

    void test_terminal_leftParen() {
        tokenMaker_tester("( ", "^\\(", leftParen, "(");
    }

    void test_terminal_rightParen() {
        tokenMaker_tester(") ", "^\\)", rightParen, ")");
    }

    void test_terminal_leftCurly() {
        tokenMaker_tester("{ ", "^\\{", leftCurly, "{");
    }

    void test_terminal_rightCurly() {
        tokenMaker_tester("};", "^\\}", rightCurly, "}");
    }

    void test_terminal_leftSquare() {
        tokenMaker_tester("[ ", "^\\[", leftSquare, "[");
    }

    void test_terminal_rightSquare() {
        tokenMaker_tester("];", "^\\]", rightSquare, "]");
    }

    void test_terminal_semiColon() {
        tokenMaker_tester(";\n", "^;", semiColon, ";");
    }

    void test_terminal_colon() { tokenMaker_tester(": ", "^:", colon, ":"); }

    void test_terminal_assign() { tokenMaker_tester("= ", "^=", assign, "="); }

    void test_terminal_plusSign() {
        tokenMaker_tester("+ ", "^\\+", plusSign, "+");
    }

    void test_terminal_star() { tokenMaker_tester("* ", "^\\*", star, "*"); }

    void test_terminal_dash() { tokenMaker_tester("- ", "-", dash, "-"); }

    void test_terminal_forwardSlash() {
        tokenMaker_tester("/ ", "/", forwardSlash, "/");
    }

    void test_terminal_lessThan() {
        tokenMaker_tester("< ", "<", lessThan, "<");
    }

    void test_terminal_lessThanEqual() {
        tokenMaker_tester("<= ", "<=", lessThanEqual, "<=");
    }

    void test_terminal_greaterThan() {
        tokenMaker_tester("> ", ">", greaterThan, ">");
    }

    void test_terminal_greaterThanEqual() {
        tokenMaker_tester(">= ", ">=", greaterThanEqual, ">=");
    }

    void test_terminal_equalsEquals() {
        tokenMaker_tester("== ", "==", equalsEquals, "==");
    }

    void test_terminal_notEquals() {
        tokenMaker_tester("!= ", "!=", notEquals, "!=");
    }

    void test_terminal_andOp() {
        tokenMaker_tester("&& ", "\\&\\&", andOp, "&&");
    }

    void test_terminal_orOp() {
        tokenMaker_tester("|| ", "\\|\\|", orOp, "||");
    }

    void test_terminal_notOp() { tokenMaker_tester("! ", "!", notOp, "!"); }

    void test_terminal_endOfFile() {
        tokenMaker_tester("", "\\|\\|", endOfFile, "");
    }

    void test_terminal_lexicalError() {
        tokenMaker_tester("##", "", lexicalError, "#");
    }

    // Tests for "scan"
    // --------------------------------------------------

    /* Below are some helper functions and sample tests for testing the
       "scan" method on Scanner.
    */

    // Test that a list of tokens has no lexicalError tokens.
    bool noLexicalErrors(Token *tks) {
        Token *currentToken = tks;
        while (currentToken != NULL) {
            if (currentToken->terminal == lexicalError) {
                printf("priblem: %s\n", currentToken->lexeme.c_str());
                return false;
            } else {
                currentToken = currentToken->next;
            }
        }
        return true;
    }

    /* A quick, but inaccurate, test for scanning files.  It only
       checks that no lexical errors occurred, not that the right
       tokens were returned.
    */
    void scanFileNoLexicalErrors(const char *filename) {
        char *text = readInputFromFile(filename);
        TS_ASSERT(text);
        Token *tks = s->scan(text);
        TS_ASSERT(tks != NULL);
        TS_ASSERT(noLexicalErrors(tks));
    }

    /* This function checks that the terminal fields in the list of
       tokens matches a list of terminals.
    */
    bool sameTerminals(Token *tks, int numTerms, tokenType *ts) {
        Token *currentToken = tks;
        int termIndex = 0;
        while (currentToken != NULL && termIndex < numTerms) {
            if (currentToken->terminal != ts[termIndex]) {
                printf("%i: %i should be %i\n", termIndex,
                       currentToken->terminal, ts[termIndex]);
                fflush(stdout);
                return false;
            } else {
                ++termIndex;
                currentToken = currentToken->next;
            }
        }
        return true;
    }

    /* Below are the provided test files that your code should also
       pass.

       You may initially want to rename these tests to "xtest_..." so
       that the CxxTest framework does not see it as a test and won't
       run it as one.  This way you can focus on the tests that you'll
       write above for the individual terminal types first. Then focus
       on these tests.

    */

    // The "endOfFile" token is always the last one in the list of tokens.
    void test_scan_empty() {
        Token *tks = s->scan("  ");
        TS_ASSERT(tks != NULL);
        TS_ASSERT_EQUALS(tks->terminal, endOfFile);
        TS_ASSERT(tks->next == NULL);
    }

    void test_scan_empty_comment() {
        Token *tks = s->scan(" /* a comment */ ");
        TS_ASSERT(tks != NULL);
        TS_ASSERT_EQUALS(tks->terminal, endOfFile);
        TS_ASSERT(tks->next == NULL);
    }

    // When a lexical error occurs, the scanner creates a token with a
    // single-character lexeme and lexicalError as the terminal.
    void test_scan_lexicalErrors() {
        Token *tks = s->scan("$&1  ");
        TS_ASSERT(tks != NULL);
        TS_ASSERT_EQUALS(tks->terminal, lexicalError);
        TS_ASSERT_EQUALS(tks->lexeme, "$");
        tks = tks->next;
        TS_ASSERT(tks != NULL);
        TS_ASSERT_EQUALS(tks->terminal, lexicalError);
        TS_ASSERT_EQUALS(tks->lexeme, "&");
        tks = tks->next;
        TS_ASSERT(tks != NULL);
        TS_ASSERT_EQUALS(tks->terminal, intConst);
        TS_ASSERT_EQUALS(tks->lexeme, "1");
        tks = tks->next;
        TS_ASSERT(tks != NULL);
        TS_ASSERT_EQUALS(tks->terminal, endOfFile);
        TS_ASSERT(tks->next == NULL);
    }

    // A test for scanning numbers and a variable.
    void test_scan_nums_vars() {
        Token *tks = s->scan(" 123 x 12.34 ");
        TS_ASSERT(tks != NULL);
        tokenType ts[] = {intConst, variableName, floatConst, endOfFile};
        TS_ASSERT(sameTerminals(tks, 4, ts));
    }

    /* This test checks that the scanner returns a list of tokens with
       the correct terminal fields.  It doesn't check that the lexemes
       are correct.
     */

    void test_scan_bad_syntax_good_tokens() {
        const char *filename = "../samples/bad_syntax_good_tokens.dsl";
        char *text = readInputFromFile(filename);
        TS_ASSERT(text);
        Token *tks = s->scan(text);
        TS_ASSERT(tks != NULL);
        tokenType ts[] = {
            intConst, intConst, intConst, intConst,

            stringConst, stringConst, stringConst,

            floatConst, floatConst, floatConst,

            matrixKwd,

            semiColon, colon, leftCurly, leftParen, rightCurly, rightParen,

            plusSign, star, dash, forwardSlash,

            equalsEquals, lessThanEqual, greaterThanEqual, notEquals, assign,

            variableName, variableName, variableName, variableName,
            variableName, variableName, variableName,

            intKwd, floatKwd, stringKwd,

            endOfFile};
        int count = 38;
        TS_ASSERT(sameTerminals(tks, count, ts));
    }

    void test_scan_sample_forestLoss() {
        scanFileNoLexicalErrors("../samples/forest_loss_v2.dsl");
    }
};
