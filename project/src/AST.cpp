/***
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
#include <sstream>
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
    string innerStmt = stmts->cppCode();
    return "#include <cmath>\n#include <iostream>\n#include "
           "\"Matrix.h\"\n\nint " +
           varName + "() {\n" + indent(innerStmt) + "}";
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
string SeqStmts::cppCode() { return st1->cppCode() + "\n" + stmts->cppCode(); }


// DeclStmt, inherits from Stmt
// Stmt ::= Decl
DeclStmt::DeclStmt(Decl *_decl) { decl = _decl; }
string DeclStmt::unparse() { return decl->unparse(); }
string DeclStmt::cppCode() { return decl->cppCode(); }


// NestedStmt, inherits from Stmt
// Stmt ::= '{' Stmts '}'
NestedStmt::NestedStmt(Stmts *_stmts) { stmts = _stmts; }
string NestedStmt::unparse() { return "{ " + stmts->unparse() + " }"; }
string NestedStmt::cppCode() {
    string innerStmt = stmts->cppCode();
    return "{\n" + indent(innerStmt) + "}";
}


// IfStmt, inherits from Stmt
// Stmt ::= 'if' '(' Expr ')' Stmt
IfStmt::IfStmt(Expr *_ex1, Stmt *_st1) {
    ex1 = _ex1;
    st1 = _st1;
}
string IfStmt::unparse() {
    return "if ( " + ex1->unparse() + " ) " + st1->unparse();
}
string IfStmt::cppCode() {
    return "if (" + ex1->cppCode() + ") " + st1->cppCode();
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
string IfElseStmt::cppCode() {
    return "if (" + ex1->cppCode() + ") " + st1->cppCode() + " else " +
           st2->cppCode();
}


// AssignStmt, inherits from Stmt
// Stmt ::= varName '=' Expr ';'
AssignStmt::AssignStmt(string _varName, Expr *_ex1) {
    varName = _varName;
    ex1 = _ex1;
}
string AssignStmt::unparse() { return varName + " = " + ex1->unparse() + ";"; }

string AssignStmt::cppCode() { return varName + " = " + ex1->cppCode() + ";"; }


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
string RangeAssignStmt::cppCode() {
    return varName + "[" + ex1->cppCode() + "][" + ex2->cppCode() + "] = " +
           ex3->cppCode() + ";";
}


// PrintStmt, inherits from Stmt
// Stmt ::= 'print' '(' Expr ')' ';'
PrintStmt::PrintStmt(Expr *_ex1) { ex1 = _ex1; }
string PrintStmt::unparse() { return "print ( " + ex1->unparse() + " );"; }
string PrintStmt::cppCode() { return "std::cout << " + ex1->cppCode() + ";"; }


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
string RepeatStmt::cppCode() {
    return "for (" + varName + " = " + ex1->cppCode() + "; " + varName +
           " <= " + ex2->cppCode() + "; " + varName + "++) " + st1->cppCode();
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
string WhileStmt::cppCode() {
    return "while (" + ex1->cppCode() + ") " + st1->cppCode();
}


// SemicolonStmt, inherits from Stmt
// Stmt ::= ';'
SemicolonStmt::SemicolonStmt() {}
string SemicolonStmt::unparse() { return ";"; }
string SemicolonStmt::cppCode() { return ";"; }


// IntDecl
// Decl ::= 'int' varName ';'
IntDecl::IntDecl(string _varName) { varName = _varName; }
string IntDecl::unparse() { return "int " + varName + ";"; }
string IntDecl::cppCode() { return "int " + varName + ";"; }


// FloatDecl
// Decl ::= 'float' varName ';'
FloatDecl::FloatDecl(string _varName) { varName = _varName; }
string FloatDecl::unparse() { return "float " + varName + ";"; }
string FloatDecl::cppCode() { return "float " + varName + ";"; }


// StringDecl
// Decl ::= 'string' varName ';'
StringDecl::StringDecl(string _varName) { varName = _varName; }
string StringDecl::unparse() { return "string " + varName + ";"; }
string StringDecl::cppCode() { return "string " + varName + ";"; }


// BooleanDecl
// Decl ::= 'boolean' varName ';'
BooleanDecl::BooleanDecl(string _varName) { varName = _varName; }
string BooleanDecl::unparse() { return "boolean " + varName + ";"; }
string BooleanDecl::cppCode() { return "bool " + varName + ";"; }


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
string MatrixLongDecl::cppCode() {
    string forStmt1 = "matrix " + varName1 + "(" + ex1->cppCode() + ", " +
                      ex2->cppCode() + ");\n" + "for (int " + varName2 +
                      " = 0; " + varName2 + " != " + varName1 + ".numRows(); " +
                      varName2 + "++) {\n";
    string innerStmts = varName1 + "[" + varName2 + "][" + varName3 + "] = " +
                        ex3->cppCode() + ";";
    string forStmt2 = "for (int " + varName3 + " = 0; " + varName3 + " != " +
                      varName1 + ".numCols(); " + varName3 + "++) {\n" +
                      indent(innerStmts) + "}";

    return forStmt1 + indent(forStmt2) + "}";
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
string MatrixShortDecl::cppCode() {
    return "matrix " + varName + " = " + ex1->cppCode() + ";";
}


// VarNameExpr
// Expr ::= varName
VarNameExpr::VarNameExpr(string _varName) { varName = _varName; }
string VarNameExpr::unparse() { return varName; }
string VarNameExpr::cppCode() { return varName; }


// IntExpr
// Expr ::= integerConst
IntExpr::IntExpr(int _val) { val = _val; }
string IntExpr::unparse() { return to_string(val); }
string IntExpr::cppCode() { return to_string(val); }


// FloatExpr
// Expr ::= floatConst
FloatExpr::FloatExpr(double _val) { val = _val; }
string FloatExpr::unparse() { return to_string(val); }
string FloatExpr::cppCode() { return to_string(val); }


// StringExpr
// Expr ::= stringConst
StringExpr::StringExpr(string _val) { val = _val; }
string StringExpr::unparse() { return val; }
string StringExpr::cppCode() { return val; }


// TrueExpr
// Expr ::= 'true'
TrueExpr::TrueExpr() {}
string TrueExpr::unparse() { return string("true"); }
string TrueExpr::cppCode() { return string("true"); }


// FalseExpr
// Expr ::= 'false'
FalseExpr::FalseExpr() {}
string FalseExpr::unparse() { return string("false"); }
string FalseExpr::cppCode() { return string("false"); }


// MultiplyExpr
// Expr ::= Expr '*' Expr
MultiplyExpr::MultiplyExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string MultiplyExpr::unparse() {
    return ex1->unparse() + " * " + ex2->unparse();
}
string MultiplyExpr::cppCode() {
    return ex1->cppCode() + " * " + ex2->cppCode();
}


// DevideExpr
// Expr ::= Expr '/' Expr
DevideExpr::DevideExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string DevideExpr::unparse() { return ex1->unparse() + " / " + ex2->unparse(); }
string DevideExpr::cppCode() { return ex1->cppCode() + " / " + ex2->cppCode(); }


// AddExpr
// Expr ::= Expr '+' Expr
AddExpr::AddExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string AddExpr::unparse() { return ex1->unparse() + " + " + ex2->unparse(); }
string AddExpr::cppCode() { return ex1->cppCode() + " + " + ex2->cppCode(); }


// SubtractExpr
// Expr ::= Expr '-' Expr
SubtractExpr::SubtractExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string SubtractExpr::unparse() {
    return ex1->unparse() + " - " + ex2->unparse();
}
string SubtractExpr::cppCode() {
    return ex1->cppCode() + " - " + ex2->cppCode();
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
string GreaterExpr::cppCode() {
    return ex1->cppCode() + " > " + ex2->cppCode();
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
string GreaterEqualExpr::cppCode() {
    return ex1->cppCode() + " >= " + ex2->cppCode();
}


// LessExpr
// Expr ::= Expr '<' Expr
LessExpr::LessExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string LessExpr::unparse() { return ex1->unparse() + " < " + ex2->unparse(); }
string LessExpr::cppCode() { return ex1->cppCode() + " < " + ex2->cppCode(); }


// LessEqualExpr
// Expr ::= Expr '<=' Expr
LessEqualExpr::LessEqualExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string LessEqualExpr::unparse() {
    return ex1->unparse() + " <= " + ex2->unparse();
}
string LessEqualExpr::cppCode() {
    return ex1->cppCode() + " <= " + ex2->cppCode();
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
string EqualEqualExpr::cppCode() {
    return ex1->cppCode() + " == " + ex2->cppCode();
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
string NotEqualExpr::cppCode() {
    return ex1->cppCode() + " != " + ex2->cppCode();
}


// AndExpr
// Expr ::= Expr '&&' Expr
AndExpr::AndExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string AndExpr::unparse() { return ex1->unparse() + " && " + ex2->unparse(); }
string AndExpr::cppCode() { return ex1->cppCode() + " && " + ex2->cppCode(); }


// OrExpr
// Expr ::= Expr '||' Expr
OrExpr::OrExpr(Expr *_ex1, Expr *_ex2) {
    ex1 = _ex1;
    ex2 = _ex2;
}
string OrExpr::unparse() { return ex1->unparse() + " || " + ex2->unparse(); }
string OrExpr::cppCode() { return ex1->cppCode() + " || " + ex2->cppCode(); }


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
string MatrixExpr::cppCode() {
    return varName + "[" + ex1->cppCode() + "][" + ex2->cppCode() + "]";
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
string NestedOrFunctionCallExpr::cppCode() {
    return varName + "(" + ex1->cppCode() + ")";
}


// NestedExpr
// Expr ::= '(' Expr ')'
NestedExpr::NestedExpr(Expr *_ex1) { ex1 = _ex1; }
string NestedExpr::unparse() { return "( " + ex1->unparse() + " )"; }
string NestedExpr::cppCode() { return "(" + ex1->cppCode() + ")"; }


// LetExpr
// Expr ::= 'let' Stmts 'in' Expr 'end'
LetExpr::LetExpr(Stmts *_stmts, Expr *_ex1) {
    stmts = _stmts;
    ex1 = _ex1;
}
string LetExpr::unparse() {
    return "let " + stmts->unparse() + " in " + ex1->unparse() + " end";
}
string LetExpr::cppCode() {
    string innerStmts = stmts->cppCode() + ex1->cppCode() + ";";
    return "({\n" + indent(innerStmts) + "})";
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
string IfExpr::cppCode() {
    return ex1->cppCode() + " ? " + ex2->cppCode() + " : " + ex3->cppCode();
}


// NotExpr
// Expr ::= '!' Expr
NotExpr::NotExpr(Expr *_ex1) { ex1 = _ex1; }
string NotExpr::unparse() { return "!" + ex1->unparse(); }
string NotExpr::cppCode() { return "!" + ex1->cppCode(); }


/**
 * make indentation for all lines in the given input string
 * @param  input a given input string
 * @return       string with well indented lines
 */
string indent(string &s) {
    std::stringstream ss(s);
    std::string item;
    std::string output;
    while (std::getline(ss, item, '\n')) {
        output += "    " + item + '\n';
    }
    return output;
}
