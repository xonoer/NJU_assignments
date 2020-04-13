#ifndef PROLOG_H
#define PROLOG_H

#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <iomanip>
using namespace std;
enum Type {None,Atom,Const,Variable,Symbol,Note};
/*
Atom: The title of the facts or rules, following the naming rules of CONST.
Const: A const starts with a lowercase, often appears in a fact. Only letters, numbers and "_" are allowed.
Variable: A variable starts with a capital, often appears in a rule. Only letters, numbers and "_" are allowed.
Symbol: All the symbols are "(" ")" "," "." ":-".
Note: Lines between the symbol (included) " / * " and " * / ".
None: Invalid symbols or words that cannot be interpreted.
*/
struct Token{
	string word;
	Type type;
	bool valid;
	Token(){valid = true;}
}; 

struct Sentence{
	int line;
	vector <Token> parts;
};

struct Fact{
	string atom;
	vector <Token> name;
};

struct Rule{
	string atom;
	vector <Fact> def; //the first one is the definition of atom.
};

class Prolog{
	private:
		int num;
		string file;
		bool can;
		vector <Sentence> lines;
		vector <Fact> list1;
		vector <Rule> list2;
		vector <string> errors;
	public:
		Prolog();
		Prolog(string filename);
		bool has_error();
		bool error_check(Sentence a); 
		string check(string s); //'\n' included.
		string search(Fact f);
		bool report_legal();
		void saveToFile();
		//test
		void test_token();
		string trans_type(Type p);
		void output1();
		void output2();
		//assist
		bool isLegallyNamed(char s);
		bool hasVariable(Fact f);
		bool can_open();
		bool has_atom(string s);
		~Prolog();
};


#endif //PROLOG_H
