/* A recursive descent parser with operator precedence.

   Author: Eric Van Wyk
   Modified: Robert Edge
   Modified: Kevin Thomsen
   Modified: Dan Challou

   This algorithm is based on the work of Douglas Crockford in "Top
   Down Operator Precedence", a chapter in the book "Beautiful Code".
   Mr. Crockford describes in his chapter how his work is based on an
   algorithm described Vaughan Pratt in "Top Down Operator
   Precedence", presented at the ACM Symposium on Principles of
   Programming Languages.

   Douglas Crockford's chapter is available at
    http://javascript.crockford.com/tdop/tdop.html

   Vaughan Pratt's paper is available at
    http://portal.acm.org/citation.cfm?id=512931

   These are both quite interesting works and worth reading if you
   find the problem of parsing to be an interesting one.

   Last modified: Oct 19, 2015.

*/

#include "./AST.h"
#include "./parser.h"
#include "./scanner.h"
#include "./extToken.h"
#include <stdio.h>
#include <assert.h>
using namespace std;

Parser::~Parser() {
    if (s) delete s;

    ExtToken *extTokenToDelete;
    currToken = tokens;
    while (currToken) {
        extTokenToDelete = currToken;
        currToken = currToken->next;
        delete extTokenToDelete;
    }

    Token *tokenToDelete;
    Token *currScannerToken = stokens;
    while (currScannerToken) {
        tokenToDelete = currScannerToken;
        currScannerToken = currScannerToken->next;
        delete tokenToDelete;
    }
}


Parser::Parser() {
    currToken = NULL;
    prevToken = NULL;
    tokens = NULL;
    s = NULL;
    stokens = NULL;
}

ParseResult Parser::parse(const char *text) {
    assert(text != NULL);

    ParseResult pr;
    try {
        s = new Scanner();
        stokens = s->scan(text);
        tokens = extendTokenList(this, stokens);

        assert(tokens != NULL);
        currToken = tokens;
        pr = parseProgram();
    } catch (string errMsg) {
        pr.ok = false;
        pr.errors = errMsg;
        pr.ast = NULL;
    }
    return pr;
}

/*
 * parse methods for non-terminal symbols
 * --------------------------------------
 */


// Program
ParseResult Parser::parseProgram() {
    ParseResult pr;
    // root
    // Program ::= varName '(' ')' '{' Stmts '}'
    match(variableName);
    string varName(prevToken->lexeme);
    match(leftParen);
    match(rightParen);
    match(leftCurly);
    ParseResult prStmts = parseStmts();
    match(rightCurly);
    match(endOfFile);
    pr.ast = new Program(varName, dynamic_cast<Stmts *>(prStmts.ast));
    pr.ok = true;
    return pr;
}


// MatrixDecl
// identical purpose of parseDecl, handles special matrix syntax.
ParseResult Parser::parseMatrixDecl() {
    ParseResult pr;
    match(matrixKwd);
    match(variableName);
    string varName(prevToken->lexeme);

    // Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':' varName  '='
    // Expr ';'
    if (attemptMatch(leftSquare)) {
        ParseResult result1 = parseExpr(0);
        match(colon);
        ParseResult result2 = parseExpr(0);
        match(rightSquare);
        ParseResult result3 = parseVariableName();
        match(colon);
        ParseResult result4 = parseVariableName();
        match(assign);
        ParseResult result5 = parseExpr(0);
        match(semiColon);

        pr.ast = new MatrixLongDecl(
            varName, dynamic_cast<VarNameExpr *>(result3.ast)->unparse(),
            dynamic_cast<VarNameExpr *>(result4.ast)->unparse(),
            dynamic_cast<Expr *>(result1.ast),
            dynamic_cast<Expr *>(result2.ast),
            dynamic_cast<Expr *>(result5.ast));
        pr.ok = true;
    }
    // Decl ::= 'matrix' varName '=' Expr ';'
    else if (attemptMatch(assign)) {
        ParseResult result1 = parseExpr(0);
        match(semiColon);
        pr.ast =
            new MatrixShortDecl(varName, dynamic_cast<Expr *>(result1.ast));
        pr.ok = true;
    } else {
        throw((string) "Bad Syntax of Matrix Decl in in parseMatrixDecl");
    }
    return pr;
}
// standardDecl
// Decl ::= integerKwd varName | floatKwd varName | stringKwd varName
ParseResult Parser::parseStandardDecl() {
    ParseResult pr;

    enum declType { int_d, float_d, string_d, bool_d, error_d };

    enum declType cur_type = error_d;

    if (attemptMatch(intKwd)) {
        // Type ::= intKwd
        cur_type = int_d;
    } else if (attemptMatch(floatKwd)) {
        // Type ::= floatKwd
        cur_type = float_d;
    } else if (attemptMatch(stringKwd)) {
        // Type ::= stringKwd
        cur_type = string_d;
    } else if (attemptMatch(boolKwd)) {
        // Type ::= boolKwd
        cur_type = bool_d;
    } else {
        throw((string) "Bad Syntax of Standard Decl in parseStandardDecl");
    }

    match(variableName);
    string varName(prevToken->lexeme);
    match(semiColon);

    Decl *decl;
    switch (cur_type) {
        case int_d:
            decl = new IntDecl(varName);
            break;
        case float_d:
            decl = new FloatDecl(varName);
            break;
        case string_d:
            decl = new StringDecl(varName);
            break;
        case bool_d:
            decl = new BooleanDecl(varName);
            break;
        default:
            throw((string) "Bad Syntax of Standard Decl in parseStandardDecl");
    }
    pr.ast = decl;
    pr.ok = true;
    return pr;
}

// Decl
ParseResult Parser::parseDecl() {
    ParseResult pr;
    // Decl :: matrix variableName ....
    if (nextIs(matrixKwd)) {
        pr = parseMatrixDecl();
    }
    // Decl ::= Type variableName semiColon
    else {
        pr = parseStandardDecl();
    }
    return pr;
}


// Stmts
ParseResult Parser::parseStmts() {
    ParseResult pr;
    if (!nextIs(rightCurly) && !nextIs(inKwd)) {
        // Stmts ::= Stmt Stmts
        ParseResult prStmt = parseStmt();
        ParseResult prStmts = parseStmts();
        pr.ast = new SeqStmts(dynamic_cast<Stmt *>(prStmt.ast),
                              dynamic_cast<Stmts *>(prStmts.ast));
        pr.ok = true;
    } else {
        // Stmts ::=
        // nothing to match.
        pr.ast = new EmptyStmts();
        pr.ok = true;
    }
    return pr;
}


// Stmt
ParseResult Parser::parseStmt() {
    ParseResult pr;
    // Stmt ::= Decl
    if (nextIs(intKwd) || nextIs(floatKwd) || nextIs(matrixKwd) ||
        nextIs(stringKwd) || nextIs(boolKwd)) {
        ParseResult result1 = parseDecl();
        pr.ast = new DeclStmt(dynamic_cast<Decl *>(result1.ast));
        pr.ok = true;
    }
    // Stmt ::= '{' Stmts '}'
    else if (attemptMatch(leftCurly)) {
        ParseResult result_stmts = parseStmts();
        match(rightCurly);
        pr.ast = new NestedStmt(dynamic_cast<Stmts *>(result_stmts.ast));
        pr.ok = true;
    }
    // Stmt ::= 'if' '(' Expr ')' Stmt
    // Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
    else if (attemptMatch(ifKwd)) {
        match(leftParen);
        ParseResult result_expr1 = parseExpr(0);
        match(rightParen);
        ParseResult result_stmt = parseStmt();

        if (attemptMatch(elseKwd)) {
            ParseResult result_expr2 = parseStmt();
            pr.ast = new IfElseStmt(dynamic_cast<Expr *>(result_expr1.ast),
                                    dynamic_cast<Stmt *>(result_stmt.ast),
                                    dynamic_cast<Stmt *>(result_expr2.ast));
        } else {
            pr.ast = new IfStmt(dynamic_cast<Expr *>(result_expr1.ast),
                                dynamic_cast<Stmt *>(result_stmt.ast));
        }

    }
    // Stmt ::= varName '=' Expr ';'  | varName '[' Expr ':' Expr ']' '=' Expr
    // ';'
    else if (attemptMatch(variableName)) {
        string varName(prevToken->lexeme);
        if (attemptMatch(leftSquare)) {
            ParseResult result_expr = parseExpr(0);
            match(colon);
            ParseResult result_expr2 = parseExpr(0);
            match(rightSquare);
            match(assign);
            ParseResult result_expr3 = parseExpr(0);
            match(semiColon);
            pr.ast = new RangeAssignStmt(
                varName, dynamic_cast<Expr *>(result_expr.ast),
                dynamic_cast<Expr *>(result_expr2.ast),
                dynamic_cast<Expr *>(result_expr3.ast));
            pr.ok = true;
        } else {
            match(assign);
            ParseResult result_expr = parseExpr(0);
            match(semiColon);
            pr.ast =
                new AssignStmt(varName, dynamic_cast<Expr *>(result_expr.ast));
            pr.ok = true;
        }
    }
    // Stmt ::= 'print' '(' Expr ')' ';'
    else if (attemptMatch(printKwd)) {
        match(leftParen);
        ParseResult result_expr = parseExpr(0);
        match(rightParen);
        match(semiColon);
        pr.ast = new PrintStmt(dynamic_cast<Expr *>(result_expr.ast));
        pr.ok = true;
    }
    // Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
    else if (attemptMatch(repeatKwd)) {
        match(leftParen);
        match(variableName);
        string varName(prevToken->lexeme);
        match(assign);
        ParseResult result_expr = parseExpr(0);
        match(toKwd);
        ParseResult result_expr2 = parseExpr(0);
        match(rightParen);
        ParseResult result_stmt = parseStmt();
        pr.ast = new RepeatStmt(varName, dynamic_cast<Expr *>(result_expr.ast),
                                dynamic_cast<Expr *>(result_expr2.ast),
                                dynamic_cast<Stmt *>(result_stmt.ast));
        pr.ok = true;
    }
    // Stmt ::= 'while' '(' Expr ')' Stmt
    else if (attemptMatch(whileKwd)) {
        match(leftParen);
        ParseResult result_expr = parseExpr(0);
        match(rightParen);
        ParseResult result_stmt = parseStmt();
        pr.ast = new WhileStmt(dynamic_cast<Expr *>(result_expr.ast),
                               dynamic_cast<Stmt *>(result_stmt.ast));
        pr.ok = true;
    }
    // Stmt ::= ';
    else if (attemptMatch(semiColon)) {
        // parsed a skip
        pr.ast = new SemicolonStmt();
        pr.ok = true;
    } else {
        throw(makeErrorMsg(currToken->terminal) + " while parsing a statement");
    }
    // Stmt ::= variableName assign Expr semiColon
    return pr;
}

// Expr
ParseResult Parser::parseExpr(int rbp) {
    /* Examine current token, without consuming it, to call its
       associated parse methods.  The ExtToken objects have 'nud' and
       'led' methods that are dispatchers that call the appropriate
       parse methods.*/
    ParseResult left = currToken->nud();

    while (rbp < currToken->lbp()) {
        left = currToken->led(left);
    }

    return left;
}


/*
 * parse methods for Expr productions
 * ----------------------------------
 */

// Expr ::= trueKwd
ParseResult Parser::parseTrueKwd() {
    ParseResult pr;
    match(trueKwd);
    pr.ast = new TrueExpr();
    pr.ok = true;
    return pr;
}

// Expr ::= trueKwd
ParseResult Parser::parseFalseKwd() {
    ParseResult pr;
    match(falseKwd);
    pr.ast = new FalseExpr();
    pr.ok = true;
    return pr;
}

// Expr ::= intConst
ParseResult Parser::parseIntConst() {
    ParseResult pr;
    match(intConst);
    int val = stoi(prevToken->lexeme);
    pr.ast = new IntExpr(val);
    pr.ok = true;
    return pr;
}

// Expr ::= floatConst
ParseResult Parser::parseFloatConst() {
    ParseResult pr;
    match(floatConst);
    double val = stod(prevToken->lexeme);
    pr.ast = new FloatExpr(val);
    pr.ok = true;
    return pr;
}

// Expr ::= stringConst
ParseResult Parser::parseStringConst() {
    ParseResult pr;
    match(stringConst);
    string val = prevToken->lexeme;
    pr.ast = new StringExpr(val);
    pr.ok = true;
    return pr;
}

// Expr ::= variableName .....
ParseResult Parser::parseVariableName() {
    ParseResult pr;
    match(variableName);
    string varName(prevToken->lexeme);
    // Expr ::= varName '[' Expr ':' Expr ']'
    if (attemptMatch(leftSquare)) {
        ParseResult result1 = parseExpr(0);
        match(colon);
        ParseResult result2 = parseExpr(0);
        match(rightSquare);
        pr.ast = new MatrixExpr(varName, dynamic_cast<Expr *>(result1.ast),
                                dynamic_cast<Expr *>(result2.ast));
        pr.ok = true;
    }
    // Expr ::= varableName '(' Expr ')'        //NestedOrFunctionCall
    else if (attemptMatch(leftParen)) {
        ParseResult result1 = parseExpr(0);
        match(rightParen);
        pr.ast = new NestedOrFunctionCallExpr(
            varName, dynamic_cast<Expr *>(result1.ast));
        pr.ok = true;
    }
    // Expr := variableName
    else {
        // variable
        pr.ast = new VarNameExpr(varName);
        pr.ok = true;
    }
    return pr;
}


// Expr ::= leftParen Expr rightParen
ParseResult Parser::parseNestedExpr() {
    ParseResult pr;
    match(leftParen);
    ParseResult result1 = parseExpr(0);
    match(rightParen);
    pr.ast = new NestedExpr(dynamic_cast<Expr *>(result1.ast));
    pr.ok = true;
    return pr;
}

// Expr ::= 'if' Expr 'then' Expr 'else' Expr
ParseResult Parser::parseIfExpr() {
    ParseResult pr;

    match(ifKwd);
    ParseResult result1 = parseExpr(0);
    match(thenKwd);
    ParseResult result2 = parseExpr(0);
    match(elseKwd);
    ParseResult result3 = parseExpr(0);
    pr.ast = new IfExpr(dynamic_cast<Expr *>(result1.ast),
                        dynamic_cast<Expr *>(result2.ast),
                        dynamic_cast<Expr *>(result3.ast));
    pr.ok = true;
    return pr;
}


// Expr ::= 'let' Stmts 'in' Expr 'end'
ParseResult Parser::parseLetExpr() {
    ParseResult pr;
    match(letKwd);
    ParseResult result1 = parseStmts();
    match(inKwd);
    ParseResult result2 = parseExpr(0);
    match(endKwd);
    pr.ast = new LetExpr(dynamic_cast<Stmts *>(result1.ast),
                         dynamic_cast<Expr *>(result2.ast));
    pr.ok = true;
    return pr;
}

// Expr ::= '!' Expr
ParseResult Parser::parseNotExpr() {
    ParseResult pr;
    match(notOp);
    ParseResult result1 = parseExpr(0);
    pr.ast = new NotExpr(dynamic_cast<Expr *>(result1.ast));
    pr.ok = true;
    return pr;
}
// Expr ::= Expr plusSign Expr
ParseResult Parser::parseAddition(ParseResult prLeft) {
    // parser has already matched left expression
    ParseResult pr;
    match(plusSign);
    ParseResult result1 = parseExpr(prevToken->lbp());
    pr.ast = new AddExpr(dynamic_cast<Expr *>(prLeft.ast),
                         dynamic_cast<Expr *>(result1.ast));
    pr.ok = true;
    return pr;
}

// Expr ::= Expr star Expr
ParseResult Parser::parseMultiplication(ParseResult prLeft) {
    // parser has already matched left expression
    ParseResult pr;
    match(star);
    ParseResult result1 = parseExpr(prevToken->lbp());
    pr.ast = new MultiplyExpr(dynamic_cast<Expr *>(prLeft.ast),
                              dynamic_cast<Expr *>(result1.ast));
    pr.ok = true;
    return pr;
}

// Expr ::= Expr dash Expr
ParseResult Parser::parseSubtraction(ParseResult prLeft) {
    // parser has already matched left expression
    ParseResult pr;
    match(dash);
    ParseResult result1 = parseExpr(prevToken->lbp());
    pr.ast = new SubtractExpr(dynamic_cast<Expr *>(prLeft.ast),
                              dynamic_cast<Expr *>(result1.ast));
    pr.ok = true;
    return pr;
}

// Expr ::= Expr forwardSlash Expr
ParseResult Parser::parseDivision(ParseResult prLeft) {
    // parser has already matched left expression
    ParseResult pr;
    match(forwardSlash);
    ParseResult result1 = parseExpr(prevToken->lbp());
    pr.ast = new DevideExpr(dynamic_cast<Expr *>(prLeft.ast),
                            dynamic_cast<Expr *>(result1.ast));
    pr.ok = true;
    return pr;
}


// Expr ::= Expr equalEquals Expr
// Expr ::= Expr lessThanEquals Expr
// Expr ::= Expr greaterThanEquals Expr
// Expr ::= Expr notEquals Expr
// Expr ::= Expr leftAngle Expr
// Expr ::= Expr rightAngle Expr
/* Notice that for relational operators we use just one parse
   function.  This shows another possible means for implementing
   expressions, as opposed to the method used for arithmetic
   expressions in which each operation has its own parse method.  It
   will depend on what we do in iteration 3 in building an abstract
   syntax tree to decide which method is better.
 */
ParseResult Parser::parseRelationalExpr(ParseResult prLeft) {
    // parser has already matched left expression
    ParseResult pr;
    Expr *ex = NULL;
    nextToken();
    // just advance token, since examining it in parseExpr caused
    // this method being called.
    string op = prevToken->lexeme;

    ParseResult result1 = parseExpr(prevToken->lbp());
    if ("==" == op)
        ex = new EqualEqualExpr(dynamic_cast<Expr *>(prLeft.ast),
                                dynamic_cast<Expr *>(result1.ast));
    else if ("<=" == op)
        ex = new LessEqualExpr(dynamic_cast<Expr *>(prLeft.ast),
                               dynamic_cast<Expr *>(result1.ast));
    else if (">=" == op)
        ex = new GreaterEqualExpr(dynamic_cast<Expr *>(prLeft.ast),
                                  dynamic_cast<Expr *>(result1.ast));
    else if ("!=" == op)
        ex = new NotEqualExpr(dynamic_cast<Expr *>(prLeft.ast),
                              dynamic_cast<Expr *>(result1.ast));
    else if ("<" == op)
        ex = new LessExpr(dynamic_cast<Expr *>(prLeft.ast),
                          dynamic_cast<Expr *>(result1.ast));
    else if (">" == op)
        ex = new GreaterExpr(dynamic_cast<Expr *>(prLeft.ast),
                             dynamic_cast<Expr *>(result1.ast));

    if (NULL == ex)
        throw((string) "Bad Syntax of Relational Expr in parseRelationalExpr");

    pr.ast = ex;
    pr.ok = true;
    return pr;
}


// Helper function used by the parser.

void Parser::match(tokenType tt) {
    if (!attemptMatch(tt)) {
        throw(makeErrorMsgExpected(tt));
    }
}

bool Parser::attemptMatch(tokenType tt) {
    if (currToken->terminal == tt) {
        nextToken();
        return true;
    }
    return false;
}

bool Parser::nextIs(tokenType tt) { return currToken->terminal == tt; }

void Parser::nextToken() {
    if (currToken == NULL)
        throw(string(
            "Internal Error: should not call nextToken in unitialized state"));
    else if (currToken->terminal == endOfFile && currToken->next == NULL) {
        prevToken = currToken;
    } else if (currToken->terminal != endOfFile && currToken->next == NULL) {
        throw(makeErrorMsg("Error: tokens end with endOfFile"));
    } else {
        prevToken = currToken;
        currToken = currToken->next;
    }
}

string Parser::terminalDescription(tokenType terminal) {
    Token *dummyToken = new Token("", terminal, NULL);
    ExtToken *dummyExtToken = extendToken(this, dummyToken);
    string s = dummyExtToken->description();
    delete dummyToken;
    delete dummyExtToken;
    return s;
}

string Parser::makeErrorMsgExpected(tokenType terminal) {
    string s = (string) "Expected " + terminalDescription(terminal) +
               " but found " + currToken->description();
    return s;
}

string Parser::makeErrorMsg(tokenType terminal) {
    string s = "Unexpected symbol " + terminalDescription(terminal);
    return s;
}

string Parser::makeErrorMsg(const char *msg) { return msg; }
