/**
 * AST: a tree representation of the abstract syntactic structure of source
 * code written in a programming language
 *
 * Node: a node in the AST tree parsed from the CDAL language text file.
 * it contains methods to unparse the node and translate it to cpp code.
 *
 * Author: Jingxiang Li, Tanoja Sunkam
 *
 * Last modified: Sun 15 Nov 2015 10:09:54 PM CST
 */

#ifndef Node_H
#define Node_H

#include "./scanner.h"
#include <iostream>
#include <string>

using namespace std;

//===================================================================
// Node

/**
 * super class Node in the Abstract Syntax Tree (AST)
 */
class Node {
public:
    virtual string unparse() = 0;
    virtual string cppCode() = 0;
    virtual ~Node() {}
};


//===================================================================
// Subclasses of Node

// Stmts, abstract class, inherits from Node
class Stmts : public Node {
public:
    virtual string unparse() { return string("this is pure virtual"); }
    virtual string cppCode() { return string("this is pure virtual"); }
    virtual ~Stmts() {}
};

// Stmt, abstract class, inherits from Node
class Stmt : public Node {
public:
    virtual string unparse() { return string("this is pure virtual"); }
    virtual string cppCode() { return string("this is pure virtual"); }
    virtual ~Stmt() {}
};

// Decl, abstract class, inherits from Node
class Decl : public Node {
public:
    virtual string unparse() { return string("this is pure virtual"); }
    virtual string cppCode() { return string("this is pure virtual"); }
    virtual ~Decl() {}
};

// Expr, abstract class, inherits from Node
class Expr : public Node {
public:
    virtual string unparse() { return string("this is pure virtual"); }
    virtual string cppCode() { return string("this is pure virtual"); }
    virtual ~Expr() {}
};

// Program, concrete class, inherits from Node
// Program ::= varName '(' ')' '{' Stmts '}'
class Program : public Node {
private:
    string varName;
    Stmts *stmts;

public:
    Program(string _varName, Stmts *_stmts);
    string unparse();
    string cppCode();
};


//=========================================================
// Subclasses of Stmts

// EmptyStmts, inherits from Stmts
// Stmts ::= <<empty>>
class EmptyStmts : public Stmts {
public:
    EmptyStmts();
    string unparse();
    string cppCode();
};

// SeqStmts, inherits from Stmts
// Stmts ::= Stmt Stmts
class SeqStmts : public Stmts {
private:
    Stmt *st1;
    Stmts *stmts;

public:
    SeqStmts(Stmt *_st1, Stmts *_stmts);
    string unparse();
};


//========================================================
// Subclasses of Stmt

// DeclStmt, inherits from Stmt
// Stmt ::= Decl
class DeclStmt : public Stmt {
private:
    Decl *decl;

public:
    DeclStmt(Decl *_decl);
    string unparse();
};

// NestedStmt, inherits from Stmt
// Stmt ::= '{' Stmts '}'
class NestedStmt : public Stmt {
private:
    Stmts *stmts;

public:
    NestedStmt(Stmts *_stmts);
    string unparse();
};

// IfStmt, inherits from Stmt
// Stmt ::= 'if' '(' Expr ')' Stmt
class IfStmt : public Stmt {
private:
    Expr *ex1;
    Stmt *st1;

public:
    IfStmt(Expr *_ex1, Stmt *_st1);
    string unparse();
};

// IfElseStmt, inherits from Stmt
// Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
class IfElseStmt : public Stmt {
private:
    Expr *ex1;
    Stmt *st1;
    Stmt *st2;

public:
    IfElseStmt(Expr *_ex1, Stmt *_st1, Stmt *_st2);
    string unparse();
};

// AssignStmt, inherits from Stmt
// Stmt ::= varName '=' Expr ';'
class AssignStmt : public Stmt {
private:
    string varName;
    Expr *ex1;

public:
    AssignStmt(string _varName, Expr *_ex1);
    string unparse();
};

// RangeAssginStmt, inherits from Stmt
// Stmt ::= varName '[' Expr ':' Expr ']' '=' Expr ';'
class RangeAssignStmt : public Stmt {
private:
    string varName;
    Expr *ex1, *ex2, *ex3;

public:
    RangeAssignStmt(string _varName, Expr *_ex1, Expr *_ex2, Expr *_ex3);
    string unparse();
};

// PrintStmt, inherits from Stmt
// Stmt ::= 'print' '(' Expr ')' ';'
class PrintStmt : public Stmt {
private:
    Expr *ex1;

public:
    PrintStmt(Expr *_ex1);
    string unparse();
};

// RepeatStmt, inherits from Stmt
// Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
class RepeatStmt : public Stmt {
private:
    string varName;
    Expr *ex1, *ex2;
    Stmt *st1;

public:
    RepeatStmt(string _varName, Expr *_ex1, Expr *_ex2, Stmt *_st1);
    string unparse();
};

// WhileStmt, inherits from Stmt
// Stmt ::= 'while' '(' Expr ')' Stmt
class WhileStmt : public Stmt {
private:
    Expr *ex1;
    Stmt *st1;

public:
    WhileStmt(Expr *_ex1, Stmt *_st1);
    string unparse();
};

// SemicolonStmt, inherits from Stmt
// Stmt ::= ';'
class SemicolonStmt : public Stmt {
public:
    SemicolonStmt();
    string unparse();
};


//========================================================
// Subclasses of Decl

// IntDecl
// Decl ::= 'int' varName ';'
class IntDecl : public Decl {
    string varName;

public:
    IntDecl(string _varName);
    string unparse();
};

// FloatDecl
// Decl ::= 'float' varName ';'
class FloatDecl : public Decl {
    string varName;

public:
    FloatDecl(string _varName);
    string unparse();
};

// StringDecl
// Decl ::= 'string' varName ';'
class StringDecl : public Decl {
    string varName;

public:
    StringDecl(string _varName);
    string unparse();
};

// BooleanDecl
// Decl ::= 'boolean' varName ';'
class BooleanDecl : public Decl {
    string varName;

public:
    BooleanDecl(string _varName);
    string unparse();
};

// MatrixLongDecl
// Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':' varName  '=' Expr
// ';'
class MatrixLongDecl : public Decl {
    string varName1, varName2, varName3;
    Expr *ex1, *ex2, *ex3;

public:
    MatrixLongDecl(string _varName1, string _varName2, string _varName3,
                   Expr *_ex1, Expr *_ex2, Expr *_ex3);
    string unparse();
};

// MatrixShortDecl
// Decl ::= 'matrix' varName '=' Expr ';'
class MatrixShortDecl : public Decl {
    string varName;
    Expr *ex1;

public:
    MatrixShortDecl(string _varName, Expr *_ex1);
    string unparse();
};


//========================================================
// Subclasses of Expr

// VarNameExpr
// Expr ::= varName
class VarNameExpr : public Expr {
private:
    string varName;

public:
    VarNameExpr(string _varName);
    string unparse();
};

// IntExpr
// Expr ::= integerConst
class IntExpr : public Expr {
    int val;

public:
    IntExpr(int _val);
    string unparse();
};

// FloatExpr
// Expr ::= floatConst
class FloatExpr : public Expr {
    double val;

public:
    FloatExpr(double _val);
    string unparse();
};

// StringExpr
// Expr ::= stringConst
class StringExpr : public Expr {
    string val;

public:
    StringExpr(string _val);
    string unparse();
};

// TrueExpr
// Expr ::= 'true'
class TrueExpr : public Expr {
public:
    TrueExpr();
    string unparse();
};

// FalseExpr
// Expr ::= 'false'
class FalseExpr : public Expr {
public:
    FalseExpr();
    string unparse();
};

// MultiplyExpr
// Expr ::= Expr '*' Expr
class MultiplyExpr : public Expr {
    Expr *ex1, *ex2;

public:
    MultiplyExpr(Expr *_ex1, Expr *_ex2);
    string unparse();
};

// DevideExpr
// Expr ::= Expr '/' Expr
class DevideExpr : public Expr {
    Expr *ex1, *ex2;

public:
    DevideExpr(Expr *_ex1, Expr *_ex2);
    string unparse();
};

// AddExpr
// Expr ::= Expr '+' Expr
class AddExpr : public Expr {
    Expr *ex1, *ex2;

public:
    AddExpr(Expr *_ex1, Expr *_ex2);
    string unparse();
};

// SubtractExpr
// Expr ::= Expr '-' Expr
class SubtractExpr : public Expr {
    Expr *ex1, *ex2;

public:
    SubtractExpr(Expr *_ex1, Expr *_ex2);
    string unparse();
};

// GreaterExpr
// Expr ::= Expr '>' Expr
class GreaterExpr : public Expr {
    Expr *ex1, *ex2;

public:
    GreaterExpr(Expr *_ex1, Expr *_ex2);
    string unparse();
};

// GreaterEqualExpr
// Expr ::= Expr '>=' Expr
class GreaterEqualExpr : public Expr {
    Expr *ex1, *ex2;

public:
    GreaterEqualExpr(Expr *_ex1, Expr *_ex2);
    string unparse();
};

// LessExpr
// Expr ::= Expr '<' Expr
class LessExpr : public Expr {
    Expr *ex1, *ex2;

public:
    LessExpr(Expr *_ex1, Expr *_ex2);
    string unparse();
};

// LessEqualExpr
// Expr ::= Expr '<=' Expr
class LessEqualExpr : public Expr {
    Expr *ex1, *ex2;

public:
    LessEqualExpr(Expr *_ex1, Expr *_ex2);
    string unparse();
};

// EqualEqualExpr
// Expr ::= Expr '==' Expr
class EqualEqualExpr : public Expr {
    Expr *ex1, *ex2;

public:
    EqualEqualExpr(Expr *_ex1, Expr *_ex2);
    string unparse();
};

// NotEqualExpr
// Expr ::= Expr '!=' Expr
class NotEqualExpr : public Expr {
    Expr *ex1, *ex2;

public:
    NotEqualExpr(Expr *_ex1, Expr *_ex2);
    string unparse();
};

// AndExpr
// Expr ::= Expr '&&' Expr
class AndExpr : public Expr {
    Expr *ex1, *ex2;

public:
    AndExpr(Expr *_ex1, Expr *_ex2);
    string unparse();
};

// OrExpr
// Expr ::= Expr '||' Expr
class OrExpr : public Expr {
    Expr *ex1, *ex2;

public:
    OrExpr(Expr *_ex1, Expr *_ex2);
    string unparse();
};

// MatrixExpr
// Expr ::= varName '[' Expr ':' Expr ']'
class MatrixExpr : public Expr {
    string varName;
    Expr *ex1, *ex2;

public:
    MatrixExpr(string _varName, Expr *_ex1, Expr *_ex2);
    string unparse();
};

// NestedOrFunctionCallExpr
// Expr ::= varName '(' Expr ')'
class NestedOrFunctionCallExpr : public Expr {
    string varName;
    Expr *ex1;

public:
    NestedOrFunctionCallExpr(string _varName, Expr *_ex1);
    string unparse();
};

// NestedExpr
// Expr ::= '(' Expr ')'
class NestedExpr : public Expr {
    Expr *ex1;

public:
    NestedExpr(Expr *_ex1);
    string unparse();
};

// LetExpr
// Expr ::= 'let' Stmts 'in' Expr 'end'
class LetExpr : public Expr {
    Stmts *stmts;
    Expr *ex1;

public:
    LetExpr(Stmts *_stmts, Expr *_ex1);
    string unparse();
};

// IfExpr
// Expr ::= 'if' Expr 'then' Expr 'else' Expr
class IfExpr : public Expr {
    Expr *ex1, *ex2, *ex3;

public:
    IfExpr(Expr *_ex1, Expr *_ex2, Expr *_ex3);
    string unparse();
};

// NotExpr
// Expr ::= '!' Expr
class NotExpr : public Expr {
    Expr *ex1;

public:
    NotExpr(Expr *_ex1);
    string unparse();
};

#endif  // Node_H
