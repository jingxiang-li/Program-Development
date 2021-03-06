CXX_DIR = ../lib/cxxtest
CXXTEST = $(CXX_DIR)/cxxtestgen.pl
CXXFLAGS = --error-printer --abort-on-fail --have-eh

FLAGS = -Wall -g -O -fstack-protector -std=c++0x

# Program files.
readInput.o:	readInput.cpp readInput.h
	g++ $(FLAGS) -c readInput.cpp

regex.o:	regex.cpp regex.h
	g++ $(FLAGS) -c regex.cpp

scanner.o:	scanner.cpp scanner.h regex.h
	g++ $(FLAGS) -c scanner.cpp

extToken.o:	extToken.cpp extToken.h
	g++ $(FLAGS) -c extToken.cpp

parseResult.o:	parseResult.cpp parseResult.h
	g++ $(FLAGS) -c parseResult.cpp

parser.o:	parser.cpp parser.h
	g++ $(FLAGS) -c parser.cpp

AST.o:	AST.cpp AST.h
	g++ $(FLAGS) -c AST.cpp



# Testing files and targets.
.PHONEY: run-tests
run-tests:	regex_tests scanner_tests parser_tests ast_tests codegeneration_tests
	./regex_tests
	./scanner_tests
	./parser_tests
	./ast_tests
	./codegeneration_tests

regex_tests:	regex_tests.cpp regex.o
	g++ $(FLAGS) -I$(CXX_DIR) -o regex_tests regex.o regex_tests.cpp

regex_tests.cpp:	regex_tests.h regex.h
	$(CXXTEST) $(CXXFLAGS) -o regex_tests.cpp regex_tests.h

scanner_tests:	scanner_tests.cpp scanner.o regex.o readInput.o
	g++ $(FLAGS) -I$(CXX_DIR)  -o scanner_tests \
		scanner.o regex.o readInput.o scanner_tests.cpp

scanner_tests.cpp:	scanner_tests.h scanner.h regex.h readInput.h
	$(CXXTEST) $(CXXFLAGS) -o scanner_tests.cpp scanner_tests.h

parser_tests:	parser_tests.cpp parser.o extToken.o parseResult.o scanner.o regex.o readInput.o AST.o
	g++ $(FLAGS) -I$(CXX_DIR)  -o parser_tests \
		parser.o extToken.o parseResult.o scanner.o regex.o readInput.o AST.o parser_tests.cpp

parser_tests.cpp:	parser_tests.h parser.h readInput.h scanner.h extToken.h
	$(CXXTEST) $(CXXFLAGS) -o parser_tests.cpp parser_tests.h

ast_tests:	ast_tests.cpp parser.o extToken.o parseResult.o scanner.o regex.o readInput.o AST.o
	g++ $(FLAGS) -I$(CXX_DIR)  -o ast_tests \
		parser.o extToken.o parseResult.o scanner.o regex.o readInput.o AST.o ast_tests.cpp

ast_tests.cpp:	ast_tests.h parser.h readInput.h
	$(CXXTEST) $(CXXFLAGS) -o ast_tests.cpp ast_tests.h

codegeneration_tests: codegeneration_tests.cpp parser.o extToken.o parseResult.o scanner.o regex.o readInput.o AST.o
	g++ $(FLAGS) -I$(CXX_DIR)  -o codegeneration_tests \
		parser.o extToken.o parseResult.o scanner.o regex.o readInput.o AST.o codegeneration_tests.cpp

codegeneration_tests.cpp:	codegeneration_tests.h parser.h readInput.h
	$(CXXTEST) $(CXXFLAGS) -o codegeneration_tests.cpp codegeneration_tests.h

clean:
	rm -Rf *.o \
		regex_tests regex_tests.cpp \
		scanner_tests scanner_tests.cpp \
		parser_tests parser_tests.cpp \
		ast_tests ast_tests.cpp \
		codegeneration_tests codegeneration_tests.cpp \
		../samples/*up* ../samples/*.diff ../samples/*.output \
		../samples/my_code_1 ../samples/my_code_2 \
		../samples/sample_1 ../samples/sample_2 \
		../samples/sample_3 ../samples/sample_7 \
		../samples/sample_8 ../samples/forest_loss_v2 \
		../samples/my_code_1.cpp ../samples/my_code_2.cpp \
		../samples/sample_1.cpp ../samples/sample_2.cpp \
		../samples/sample_3.cpp ../samples/sample_7.cpp \
		../samples/sample_8.cpp ../samples/forest_loss_v2.cpp

