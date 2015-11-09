#ifndef Node_H
#define Node_H

#include <string>
#include <iostream>

#include "scanner.h"

using namespace std;

// Node, super class, abstract, interface
class Node {
public:
    virtual string unparse() = 0;
    virtual string cppCode() = 0;
    virtual ~Node() {}
};

//===================================================================

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

// Program, inherits from Node
// Program ::= varName '(' ')' '{' Stmts '}'  //root
class Program : public Node {
private:
    string varName;
    Stmts stmts;

public:
    Program(string _varName, Stmts _stmts) {
        varName = _varName;
        stmts = _stmts;
    }
    string unparse() { return varName + " ( ) { " + stmts.unparse() + " }"; }
    string cppCode() { return varName + " ( ) { " + stmts.cppCode() + " }"; }
};

//=========================================================
/**
 * Concrete classes for Stmts
 */

// EmptyStmts, inherits from Stmts
// Stmts ::= <<empty>>
class EmptyStmts : public Stmts {
public:
    EmptyStmts() {}
    string unparse() { return ""; }
};

// SeqStmts, inherits from Stmts
// Stmts ::= Stmt Stmts
class SeqStmts : public Stmts {
private:
    Stmt stmt;
    Stmts stmts;

public:
    SeqStmts(Stmt _stmt, Stmts _stmts) {
        stmt = _stmt;
        stmts = _stmts;
    }
    string unparse() { return stmt.unparse() + "\n" + stmts.unparse(); }
};

//========================================================
/**
 * Concrete classes for Stmt
 */

// DeclStmt, inherits from Stmt
// Stmt ::= Decl
class DeclStmt : public Stmt {
private:
    Decl decl;

public:
    DeclStmt(Decl _decl) { decl = _decl; }
    string unparse() { return decl.unparse(); }
};

// NestedStmt, inherits from Stmt
class NestedStmt : public Stmt {
private:
    Stmt s1;

public:
    NestedStmt(Stmt _s1) { s1 = _s1; }
    string unparse() { return "{ " + s1.unparse() + " }"; }
};

// IfExprStmt, inherits from Stmt
class IfExprStmt : public Stmt {
private:
    Expr ex1;
    Stmt st1;

public:
    IfExprStmt(Expr ex, Stmt st) {
        ex1 = ex;
        st1 = st;
    }
    string unparse() { return "if ( " + ex1.unparse() + " ) " + st1.unparse(); }
};

// IfElseStmt, inherits from Stmt
class IfElseStmt : public Stmt {
private:
    Expr ex1;
    Stmt st1;
    Stmt st2;

public:
    IfElseStmt(Expr _ex1, Stmt _st1, Stmt _st2) {
        ex1 = _ex1;
        st1 = _st1;
        st2 = _st2;
    }
    string unparse() {
        return "if ( " + ex1.unparse() + " ) " + st1.unparse() + " else " +
               st2.unparse();
    }
};

// AssignStmt, inherits from Stmt
class AssignStmt : public Stmt {
private:
    string varName;
    Expr ex;

public:
    AssignStmt(string _varName, Expr _ex) {
        varName = _varName;
        ex = _ex;
    }
    string unparse() { return varName + "=" + ex.unparse() + ";\n"; }
};

// RangeAssginStmt, inherits from Stmt
// varName '[' Expr ':' Expr ']' '=' Expr ';'
class RangeAssignStmt : public Stmt {
private:
    string varName;
    Expr ex1, ex2, ex3;

public:
    RangeAssignStmt(string _varName, Expr _ex1, Expr _ex2, Expr _ex3) {
        varName = _varName;
        ex1 = _ex1;
        ex2 = _ex2;
        ex3 = _ex3;
    }
    string unparse() {
        return varName + "[ " + ex1.unparse() + " : " + ex2.unparse() +
               " ] = " + ex3.unparse() + ";\n";
    }
};

// PrintStmt, inherits from Stmt
// Stmt ::= 'print' '(' Expr ')' ';'
class PrintStmt : public Stmt {
private:
    Expr ex;

public:
    PrintStmt(Expr _ex) { ex = _ex; }
    string unparse() { return "print ( " + ex.unparse() + " );\n"; }
};

// RepeatStmt, inherits from Stmt
// Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
class RepeatStmt : public Stmt {
private:
    string varName;
    Expr ex1, ex2;
    Stmt st;

public:
    RepeatStmt(string _varName, Expr _ex1, Expr _ex2, Stmt _st) {
        varName = _varName;
        ex1 = _ex1;
        ex2 = _ex2;
        st = _st;
    }
    string unparse() {
        return "repeat ( " + varName + " = " + ex1.unparse() + " to " +
               ex2.unparse() + " ) " + st.unparse();
    }
};

// WhileStmt, inherits from Stmt
// Stmt ::= 'while' '(' Expr ')' Stmt
class WhileStmt : public Stmt {
private:
    Expr ex;
    Stmt st;

public:
    WhileStmt(Expr _ex, Stmt _st) {
        ex = _ex;
        st = _st;
    }
    string unparse() {
        return "while ( " + ex.unparse() + " ) " + st.unparse();
    }
};

// SemicolonStmt, inherits from Stmt
// Stmt ::= ';'
class SemicolonStmt : public Stmt {
public:
    SemicolonStmt() {}
    string unparse() { return ";\n"; }
};

//===================================================================

// IntDecl
class IntDecl : public Decl {
    string varName;

public:
    IntDecl(string _varName) { varName = _varName; }
    string unparse() { return "int " + varName + " ;"; }
};

// FloatDecl
class FLoatDecl : public Decl {
    string varName;

public:
    FLoatDecl(string _varName) { varName = _varName; }
    string unparse() { return "float " + varName + " ;"; }
};

// StringDecl
class StringDecl : public Decl {
    string varName;

public:
    StringDecl(string _varName) { varName = _varName; }
    string unparse() { return "string " + varName + " ;"; }
};

// BooleanDecl
class BooleanDecl : public Decl {
    string varName;

public:
    BooleanDecl(string _varName) { varName = _varName; }
    string unparse() { return "boolean " + varName + " ;"; }
};

// MatrixLongDecl
class MatrixLongDecl : public Decl {
    string varName1, varName2, varName3;
    Expr ex1, ex2, ex3;

public:
    MatrixLongDecl(string _varName1, string _varName2, string _varName3,
                   Expr _ex1, Expr _ex2, Expr _ex3) {
        varName1 = _varName1;
        varName2 = _varName2;
        varName3 = _varName3;
        ex1 = _ex1;
        ex2 = _ex2;
        ex3 = _ex3;
    }
    string unparse() {
        return "matrix " + varName1 + "[ " + ex1.unparse() + " :  " +
               ex2.unparse() + " ] " + varName2 + " : " + varName3 + " = " +
               ex3.unparse() + ";\n";
    }
};

// MatrixShortDecl
class MatrixShortDecl : public Decl {
    string varName;
    Expr ex;

public:
    MatrixShortDecl(string _varName, Expr _ex) {
        varName = _varName;
        ex = _ex;
    }
    string unparse() {
        return "matrix " + varName + " = " + ex.unparse() + ";\n";
    }
};

// VarNameExpr
class VarNameExpr : public Expr {
private:
    string varName;

public:
    VarNameExpr(string _varName) { varName = _varName; }
    string unparse() { return varName; }
};

// IntExpr
class IntExpr : public Expr {
    int val;

public:
    IntExpr(int _val) { val = _val; }
    string unparse() { return to_string(val); }
};

// FloatExpr
class FloatExpr : public Expr {
    double val;

public:
    FloatExpr(double _val) { val = _val; }
    string unparse() { return to_string(val); }
};

// StringExpr
class StringExpr : public Expr {
    string val;

public:
    StringExpr(string _val) { val = _val; }
    string unparse() { return val; }
};

// TrueExpr
class TrueExpr : public Expr {
    bool val;

public:
    TrueExpr(bool _val) { val = _val; }
    string unparse() { return to_string(val); }
};

// FalseExpr
class FalseExpr : public Expr {
    bool val;

public:
    FalseExpr(bool _val) { val = _val; }
    string unparse() { return to_string(val); }
};

// MultiplyExpr
class MultiplyExpr : public Expr {
    Expr e1, e2;

public:
    MultiplyExpr(Expr _e1, Expr _e2) {
        e1 = _e1;
        e2 = _e2;
    }
    string unparse() { return e1.unparse() + " * " + e2.unparse(); }
};

// DevideExpr
class DevideExpr : public Expr {
    Expr e1, e2;

public:
    DevideExpr(Expr _e1, Expr _e2) {
        e1 = _e1;
        e2 = _e2;
    }
    string unparse() { return e1.unparse() + " / " + e2.unparse(); }
};

// AddExpr
class AddExpr : public Expr {
    Expr e1, e2;

public:
    AddExpr(Expr _e1, Expr _e2) {
        e1 = _e1;
        e2 = _e2;
    }
    string unparse() { return e1.unparse() + " + " + e2.unparse(); }
};

// SubtractExpr
class SubtractExpr : public Expr {
    Expr e1, e2;

public:
    SubtractExpr(Expr _e1, Expr _e2) {
        e1 = _e1;
        e2 = _e2;
    }
    string unparse() { return e1.unparse() + " - " + e2.unparse(); }
};

// GreaterExpr
class GreaterExpr : public Expr {
    Expr e1, e2;

public:
    GreaterExpr(Expr _e1, Expr _e2) {
        e1 = _e1;
        e2 = _e2;
    }
    string unparse() { return e1.unparse() + " > " + e2.unparse(); }
};

// GreaterEqualExpr
class GreaterEqualExpr : public Expr {
    Expr e1, e2;

public:
    GreaterEqualExpr(Expr _e1, Expr _e2) {
        e1 = _e1;
        e2 = _e2;
    }
    string unparse() { return e1.unparse() + " >= " + e2.unparse(); }
};

// LessExpr
class LessExpr : public Expr {
    Expr e1, e2;

public:
    LessExpr(Expr _e1, Expr _e2) {
        e1 = _e1;
        e2 = _e2;
    }
    string unparse() { return e1.unparse() + " < " + e2.unparse(); }
};

// LessEqualExpr
class LessEqualExpr : public Expr {
    Expr e1, e2;

public:
    LessEqualExpr(Expr _e1, Expr _e2) {
        e1 = _e1;
        e2 = _e2;
    }
    string unparse() { return e1.unparse() + " <= " + e2.unparse(); }
};

// EqualEqualExpr
class EqualEqualExpr : public Expr {
    Expr e1, e2;

public:
    EqualEqualExpr(Expr _e1, Expr _e2) {
        e1 = _e1;
        e2 = _e2;
    }
    string unparse() { return e1.unparse() + " == " + e2.unparse(); }
};

// NotEqualExpr
class NotEqualExpr : public Expr {
    Expr e1, e2;

public:
    NotEqualExpr(Expr _e1, Expr _e2) {
        e1 = _e1;
        e2 = _e2;
    }
    string unparse() { return e1.unparse() + " != " + e2.unparse(); }
};

// AndExpr
class AndExpr : public Expr {
    Expr e1, e2;

public:
    AndExpr(Expr _e1, Expr _e2) {
        e1 = _e1;
        e2 = _e2;
    }
    string unparse() { return e1.unparse() + " && " + e2.unparse(); }
};

// OrExpr
class OrExpr : public Expr {
    Expr e1, e2;

public:
    OrExpr(Expr _e1, Expr _e2) {
        e1 = _e1;
        e2 = _e2;
    }
    string unparse() { return e1.unparse() + " || " + e2.unparse(); }
};

// MatrixExpr
class MatrixExpr : public Expr {
    string varName;
    Expr e1, e2;

public:
    MatrixExpr(string _varName, Expr _e1, Expr _e2) {
        varName = _varName;
        e1 = _e1;
        e2 = _e2;
    }
    string unparse() {
        return varName + " [ " + e1.unparse() + " : " + e2.unparse() + " ]";
    }
};

// NestedOrFunctionCallExpr
class NestedOrFunctionCallExpr : public Expr {
    string varName;
    Expr e1;

public:
    NestedOrFunctionCallExpr(string _varName, Expr _e1) {
        varName = _varName;
        e1 = _e1;
    }
    string unparse() { return varName + "( " + e1.unparse() + " )"; }
};

// NestedExpr
class NestedExpr : public Expr {
    Expr e1;

public:
    NestedExpr(Expr _e1) { e1 = _e1; }
    string unparse() { return "( " + e1.unparse() + " )"; }
};

// LetExpr
class LetExpr : public Expr {
    Stmts stmts;
    Expr expr;

public:
    LetExpr(Stmts _stmts, Expr _expr) {
        stmts = _stmts;
        expr = _expr;
    }
    string unparse() {
        return "let " + stmts.unparse() + " in " + expr.unparse() + " end";
    }
};

// IfExpr
class IfExpr : public Expr {
    Expr e1, e2, e3;

public:
    IfExpr(Expr _e1, Expr _e2, Expr _e3) {
        e1 = _e1;
        e1 = _e2;
        e3 = _e3;
    }
    string unparse() {
        return "if " + e1.unparse() + " then " + e2.unparse() + " else " +
               e3.unparse();
    }
};

// NotExpr
class NotExpr : public Expr {
    Expr expr;

public:
    NotExpr(Expr _expr) { expr = _expr; }
    string unparse() { return "! " + expr.unparse(); }
};

#endif
