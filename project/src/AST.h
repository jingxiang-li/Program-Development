#ifndef Node_H
#define Node_H

#include <string>
#include <iostream> 

#include "scanner.h"

class Node ;

// Node
class Node {
	public:
		virtual std::string unparse ( ) { return " This should be pure virtual ";} ;
		virtual std::string cppCode ( ) { return " This should be pure virtual" ; } ;
		virtual ~Node() { }
} ;

#endif

