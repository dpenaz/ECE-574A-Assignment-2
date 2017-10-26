#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Verilog_Imp.h"

using namespace std;

bool checkKey(string key, const map<string, vector<string>> &my_map);
extern ofstream outfile;

bool is_output(string sym, const map<string, vector<string>> &my_map)
{
	string symFunc = my_map.find(sym)->second[0];
	return !symFunc.compare("output");
}

bool is_input(string sym, const map<string, vector<string>> &my_map)
{
	string symFunc = my_map.find(sym)->second[0];
	return !symFunc.compare("input");
}

bool Add_or_INC(string line, const map<string, vector<string>> &my_map)
{
	string out, in1, in2;
	istringstream iss(line);

	string curSym;

	// OUT
	iss >> curSym;

	if (!checkKey(curSym, my_map)) {
		cerr << "Error: unexpected symbol: " << curSym << " in following line:" << endl << line << endl;
		return false;
	}
	else if (!is_output(curSym, my_map)) {
		cerr << "Error: " << curSym << "is not an output in following line:" << endl << line << endl;
		return false;
	}

	out = curSym;

	// =
	iss >> curSym;

	if (curSym.compare("=")) {
		cerr << "Expected '=' instead of '" << curSym << "' in following line:" << endl << line << endl;
		return false;
	}

	// IN1
	iss >> curSym;

	if (!checkKey(curSym, my_map)) {
		cerr << "Error: unexpected symbol: " << curSym << " in following line:" << endl << line << endl;
		return false;
	}
	else if (!is_input(curSym, my_map)) {
		cerr << "Error: " << curSym << "is not an input in following line:" << endl << line << endl;
		return false;
	}
	in1 = curSym;

	// +
	iss >> curSym;

	if (curSym.compare("+")) {
		cerr << "Error: expected '+', not '" << curSym << "' in following line:" << endl << line << endl;
		return false;
	}

	// IN2
	iss >> curSym;

	if (!checkKey(curSym, my_map)) {
		cerr << "Error: unexpected symbol: " << curSym << " in following line:" << endl << line << endl;
		return false;
	}
	else if (!is_input(curSym, my_map)) {
		cerr << "Error: " << curSym << "is not an input in following line:" << endl << line << endl;
		return false;
	}
	in2 = curSym;

	// end of line
	iss >> curSym;
	if (!ss.eof()) {
		cerr << "Error: expected end of line, not '" << curSym << "' in following line:" << endl << line << endl;
		return false;
	}

	outfile << "ADD#? Adder_?(" << in1 << in2 << out << ");" << endl;
	
	return true;
};

string REG_(string line, const map<string, vector<string>> &my_map)
{
	return "WRITE ME";
};

string SUB_or_DEC(string line, const map<string, vector<string>> &my_map)
{
	return "WRITE ME";
};

string MOD_(string line, const map<string, vector<string>> &my_map)
{
	return "WRITE ME";
};

string DIV_(string line, const map<string, vector<string>> &my_map)
{
	return "WRITE ME";
};

string SHL_(string line, const map<string, vector<string>> &my_map)
{
	return "WRITE ME";
};

string SHR_(string line, const map<string, vector<string>> &my_map)
{
	return "WRITE ME";
};

string MUX2x1_(string line, const map<string, vector<string>> &my_map)
{
	return "WRITE ME";
};

string COMP_eq(string line, const map<string, vector<string>> &my_map)
{
	return "WRITE ME";
};

string COMP_lt(string line, const map<string, vector<string>> &my_map)
{
	return "WRITE ME";
};

string COMP_gt(string line, const map<string, vector<string>> &my_map)
{
	return "WRITE ME";
};

string MUL_(string line, const map<string, vector<string>> &my_map)
{
	return "WRITE ME";
};