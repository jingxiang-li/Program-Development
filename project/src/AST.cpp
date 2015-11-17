/**
 * AST: a tree representation of the abstract syntactic structure of source
 * code written in a programming language
 *
 * Node: a node in the AST tree parsed from the CDAL language text file.
 * it contains methods to unparse the node and translate it to cpp code.
 *
 * Author: Jingxiang Li, Tanoja Sunkam
 *
 * Last modified: Sun 15 Nov 2015 10:09:58 PM CST
 */

#include "./AST.h"
#include <iostream>
#include <string>


// Program, concrete class, inherits from Node
// Program ::= varName '(' ')' '{' Stmts '}'
Program::Program(string _varName, Stmts *_stmts) {
    varName = _varName;
    stmts = _stmts;
}
string Program::unparse() {
    return varName + " ( ) { " + stmts->unparse() + " }";
}
string Program::cppCode() {
    return varName + " ( ) { " + stmts->cppCode() + " }";
}


// EmptyStmts, inherits from Stmts
// Stmts ::= <<empty>>
EmptyStmts::EmptyStmts() {}
string EmptyStmts::unparse() { return string(""); }
string EmptyStmts::cppCode() { return string(""); }


// SeqStmts, inherits from Stmts
// Stmts ::= Stmt Stmts
SeqStmts::SeqStmts(Stmt *_st1, Stmts *_stmts) {
    st1 = _st1;
    stmts = _stmts;
}
string SeqStmts::unparse() { return st1->unparse() + "\n" + stmts->unparse(); }


// DeclStmt, inherits from Stmt
// Stmt ::= Decl
DeclStmt::DeclStmt(Decl *_decl) { decl = _decl; }
string DeclStmt::unparse() { return decl->unparse(); }


// NestedStmt, inherits from Stmt
// Stmt ::= '{' Stmts '}'
NestedStmt::NestedStmt(Stmts *_stmts) { stmts = _stmts; }
string NestedStmt::unparse() { return "{ " + stmts->unparse() + " }"; }


// IfStmt, inherits from Stmt
// Stmt ::= 'if' '(' Expr ')' Stmt
IfStmt::IfStmt(Expr *_ex1, Stmt *_st1) {
    ex1 = _ex1;
    st1 = _st1;
}
string IfStmt::unparse() {
    return "if ( " + ex1->unparse() + " ) " + st1->unparse();
}


// IfElseStmt, inherits from Stmt
// Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
IfElseStmt::IfElseStmt(Expr *_ex1, Stmt *_st1, Stmt *_st2) {
    ex1 = _ex1;
    st1 = _st1;
    st2 = _st2;
}
string IfElseStmt::unparse() {
    return "if ( " + ex1->unparse() + " ) " + st1->unparse() + " else " +
           st2->unparse();
}


// AssignStmt, inherits from Stmt
// Stmt ::= varName '=' Expr ';'
AssignStmt::AssignStmt(string _varName, Expr *_ex1) {
    varName = _varName;
    ex1 = _ex1;
}
string AssignStmt::unparse() { return varName + "=" + ex1->unparse() + ";\n"; }


// RangeAssginStmt, inherits from Stmt
// Stmt ::= varName '[' Expr ':' Expr ']' '=' Expr ';'
RangeAssignStmt::RangeAssignStmt(string _varName, Expr *_ex1, Expr *_ex2,
                                 Expr *_ex3) {
    varName = _varName;
    ex1 = _ex1;
    ex2 = _ex2;
    ex3 = _ex3;
}
string RangeAssignStmt::unparse() {
    return varName + "[ " + ex1->unparse() + " : " + ex2->unparse() + " ] = " +
           ex3->unparse() + ";\n";
}


// PrintStmt, inherits from Stmt
// Stmt ::= 'print' '(' Expr ')' ';'
PrintStmt::PrintStmt(Expr *_ex1) { ex1 = _ex1; }
string PrintStmt::unparse() { return "print ( " + ex1->unparse() + " );\n"; }


// RepeatStmt, inherits from Stmt
// Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
RepeatStmt::RepeatStmt(string _varName, Expr *_ex1, Expr *_ex2, Stmt *_st1) {
    varName = _varName;
    ex1 = _ex1;
    ex2 = _ex2;
    st1 = _st1;
}
string RepeatStmt::unparse() {
    return "repeat ( " + varName + " = " + ex1->unparse() + " to " +
           ex2->unparse() + " ) " + st1->unparse();
}


// WhileStmt, inherits from Stmt
// Stmt ::= 'while' '(' Expr ')' Stmt
WhileStmt::WhileStmt(Expr *_ex1, Stmt *_st1) {
    ex1 = _ex1;
    st1 = _st1;
}
string WhileStmt::unparse() {
    return "while ( " + ex1->unparse() + " ) " + st1->unparse();
}


// SemicolonStmt, inherits from Stmt
// Stmt ::= ';'
SemicolonStmt::SemicolonStmt() {}
string SemicolonStmt::unparse() { return ";\n"; }


// IntDecl
// Decl ::= 'int' varName ';'
IntDecl::IntDecl(string _varName) { varName = _varName; }
string IntDecl::unparse() { return "int " + varName + " ;\n"; }


// FloatDecl
// Decl ::= 'float' varName ';'
FloatDecl::FloatDecl(string _varName) { varName = _varName; }
string FloatDecl::unparse() { return "float " + varName + " ;\n"; }


// StringDecl
// Decl ::= 'string' varName ';'
StringDecl::StringDecl(string _varName) { varName = _varName; }
string StringDecl::unparse() { return "string " + varName + " ;\n"; }


// BooleanDecl
// Decl ::= 'boolean' varName ';'
BooleanDecl::BooleanDecl(string _varName) { varName = _varName; }
string BooleanDecl::unparse() { return "boolean " + varName + " ;\n"; }


// MatrixLongDecl
// Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':' varName  '=' Expr
// ';'
MatrixLongDecl::MatrixLongDecl(string _varName1, string _varName2,
                               string _varName3, Expr *_ex1, Expr *_ex2,
                               Expr *_ex3) {
    varName1 = _varName1;
    varName2 = _varName2;
    varName3 = _varName3;
    ex1 = _ex1;
    ex2 = _ex2;
    ex3 = _ex3;
}
string MatrixLongDecl::unparse() {
    return "matrix " + varName1 + "[ " + ex1->unparse() + " : " +
           ex2->unparse() + " ] " + varName2 + " : " + varName3 + " = " +
           ex3->unparse() + ";\n";
}


// MatrixShortDecl
// Decl ::= 'matrix' varName '=' Expr ';'
MatrixShortDecl::MatrixShortDecl(string _varName, Expr *_ex1) {
    varName = _varName;
    ex1 = _ex1;
}
string MatrixShortDecl::unparse() {
    return "matrix " + varName + " = " + ex1->unparse() + ";\n";
}


// VarNameExpr
// Expr ::= varName
VarNameExpr::VarNameExpr(string _varName) { varName = _varName; }
string VarNameExpr::unparse() { return varName; }


// IntExpr
// Expr ::= integerConst
IntExpr::IntExpr(int _val) { val = _val; }
string IntExpr::unparse() { return to_string(val); }


// FloatExpr
// Expr ::= floatConst
FloatExpr::FloatExpr(double _val) { val = _val; }
string FloatExpr::unparse() { return to_string(val); }


// StringExpr
// Expr ::= stringConst
StringExpr::StringExpr(string _val) { val = _val; }
string StringExpr::unparse() { return val; }


// TrueExpr
// Expr ::= 'true'
TrueExpr::TrueExpr() {}
string TrueExpr::unparse() { return string("true"); }


// FalseExpr
// Expr ::= 'false'
FalseExpr::FalseExpr() {}
string FalseExpr::unparse() { return string("false"); }


// MultiplyExpr
// Expr ::= Expr '*' Expr
MultiplyExpr::MultiplyExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string MultiplyExpr::unparse() {
    return ex1->unparse() + " * " + ex2->unparse();
}


// DevideExpr
// Expr ::= Expr '/' Expr
DevideExpr::DevideExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string DevideExpr::unparse() { return ex1->unparse() + " / " + ex2->unparse(); }


// AddExpr
// Expr ::= Expr '+' Expr
AddExpr::AddExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string AddExpr::unparse() { return ex1->unparse() + " + " + ex2->unparse(); }


// SubtractExpr
// Expr ::= Expr '-' Expr
SubtractExpr::SubtractExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string SubtractExpr::unparse() {
    return ex1->unparse() + " - " + ex2->unparse();
}


// GreaterExpr
// Expr ::= Expr '>' Expr
GreaterExpr::GreaterExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string GreaterExpr::unparse() {
    return ex1->unparse() + " > " + ex2->unparse();
}


// GreaterEqualExpr
// Expr ::= Expr '>=' Expr
GreaterEqualExpr::GreaterEqualExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}

string GreaterEqualExpr::unparse() {
    return ex1->unparse() + " >= " + ex2->unparse();
}


// LessExpr
// Expr ::= Expr '<' Expr
LessExpr::LessExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string LessExpr::unparse() { return ex1->unparse() + " < " + ex2->unparse(); }


// LessEqualExpr
// Expr ::= Expr '<=' Expr
LessEqualExpr::LessEqualExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string LessEqualExpr::unparse() {
    return ex1->unparse() + " <= " + ex2->unparse();
}


// EqualEqualExpr
// Expr ::= Expr '==' Expr
EqualEqualExpr::EqualEqualExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}

string EqualEqualExpr::unparse() {
    return ex1->unparse() + " == " + ex2->unparse();
}


// NotEqualExpr
// Expr ::= Expr '!=' Expr
NotEqualExpr::NotEqualExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string NotEqualExpr::unparse() {
    return ex1->unparse() + " != " + ex2->unparse();
}


// AndExpr
// Expr ::= Expr '&&' Expr
AndExpr::AndExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string AndExpr::unparse() { return ex1->unparse() + " && " + ex2->unparse(); }


// OrExpr
// Expr ::= Expr '||' Expr
OrExpr::OrExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string OrExpr::unparse() { return ex1->unparse() + " || " + ex2->unparse(); }


// MatrixExpr
// Expr ::= varName '[' Expr ':' Expr ']'
MatrixExpr::MatrixExpr(string _varName, Expr *_ex1, Expr *_ex2) {
    varName = _varName;
    ex1 = _ex1;
    ex2 = _ex2;
}
string MatrixExpr::unparse() {
    return varName + " [ " + ex1->unparse() + " : " + ex2->unparse() + " ]";
}


// NestedOrFunctionCallExpr
// Expr ::= varName '(' Expr ')'
NestedOrFunctionCallExpr::NestedOrFunctionCallExpr(string _varName,
                                                   Expr *_ex1) {
    varName = _varName;
    ex1 = _ex1;
}
string NestedOrFunctionCallExpr::unparse() {
    return varName + "( " + ex1->unparse() + " )";
}


// NestedExpr
// Expr ::= '(' Expr ')'
NestedExpr::NestedExpr(Expr *_ex1) { ex1 = _ex1; }
string NestedExpr::unparse() { return "( " + ex1->unparse() + " )"; }


// LetExpr
// Expr ::= 'let' Stmts 'in' Expr 'end'
LetExpr::LetExpr(Stmts *_stmts, Expr *_ex1) {
    stmts = _stmts;
    ex1 = _ex1;
}
string LetExpr::unparse() {
    return "let " + stmts->unparse() + " in " + ex1->unparse() + " end";
}


// IfExpr
// Expr ::= 'if' Expr 'then' Expr 'else' Ex
IfExpr::IfExpr(Expr *_ex1, Expr *_ex2, Expr *_ex3) {
    ex1 = _ex1;
    ex2 = _ex2;
    ex3 = _ex3;
}
string IfExpr::unparse() {
    return "if " + ex1->unparse() + " then " + ex2->unparse() + " else " +
           ex3->unparse();
}

// NotExpr
// Expr ::= '!' Expr
NotExpr::NotExpr(Expr *_ex1) { ex1 = _ex1; }
string NotExpr::unparse() { return "! " + ex1->unparse(); }
