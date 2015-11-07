#ifndef Node_H
#define Node_H

#include <string>
#include <iostream>

#include "scanner.h"

using namespace std;

// Node, abstract class
class Node {
public:
    virtual string unparse() = 0;
    virtual string cppCode() = 0;
    virtual ~Node() {}
};

// Stmtsm abstract class
class Stmts : public Node {
public:
    virtual string unparse() { return string("this is pure virtual"); }
    virtual string cppCode() { return string("this is pure virtual"); }
    virtual ~Stmts() {}
};

// Expr, abstract class
class Expr : public Node {
public:
    virtual string unparse() { return string("this is pure virtual"); }
    virtual string cppCode() { return string("this is pure virtual"); };
    virtual ~Expr() {}
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
