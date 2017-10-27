#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Verilog_Imp.h"

using namespace std;

bool checkKey(string key, const map<string, vector<string>> &my_map);
extern ofstream outfile;

bool is_wire(string sym, const map<string, vector<string>> &my_map)
{
	string symFunc = my_map.find(sym)->second[0];
	return !symFunc.compare("wire");
}

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

bool assign_op_result(string op, string line, const map<string, vector<string>> &my_map)
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
	else if (!is_wire(curSym, my_map)) {
		cerr << "Error: '" << curSym << "'is not a wire in following line:" << endl << line << endl;
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
	else if (!is_input(curSym, my_map) && !is_wire(curSym,my_map)) {
		cerr << "Error: " << curSym << " is not an input or a wire in following line:" << endl << line << endl;
		return false;
	}
	in1 = curSym;

	// operation
	iss >> curSym;

	if (curSym.compare(op)) {
		cerr << "Error: expected '" << op << "', not '" << curSym << "' in following line:" << endl << line << endl;
		return false;
	}

	// IN2
	iss >> curSym;

	if (!checkKey(curSym, my_map)) {
		cerr << "Error: unexpected symbol: " << curSym << " in following line:" << endl << line << endl;
		return false;
	}
	else if (!is_input(curSym, my_map) && !is_wire(curSym,my_map)) {
		cerr << "Error: " << curSym << " is not an input or a wire in following line:" << endl << line << endl;
		return false;
	}
	in2 = curSym;

	// end of line
	iss >> curSym;
	if (!iss.eof()) {
		cerr << "Error: expected end of line, not '" << curSym << "' in following line:" << endl << line << endl;
		return false;
	}

	string startStr;
	if (!op.compare("+"))
		startStr = "ADD#? Adder_?";
	else if (!op.compare("-"))
		startStr = "SUB#? Sub_?";
	else if (!op.compare("%"))
		startStr = "MOD#? Mod_?";
	else if (!op.compare("/"))
		startStr = "DIV#? Div_?";
	else if (!op.compare("<<"))
		startStr = "SHL#? Shl_?";
	else if (!op.compare(">>"))
		startStr = "SHR#? Shr_?";
	else if (!op.compare("=="))
		startStr = "[TO BE DONE] =="; // TBD
	else if (!op.compare("<"))
		startStr = "[TO BE DONE] <"; // TBD
	else if (!op.compare(">"))
		startStr = "[TO BE DONE] >"; // TBD
	else if (!op.compare("*"))
		startStr = "MUL#? Mul_?";
	else {
		cerr << "Unknown operation: " << op << "in line: " << endl << line << endl;
		return false;
	}

	outfile << startStr << "(" << in1 << "," << in2 << "," << out << ");" << endl;
	
	return true;
}

bool Add_or_INC(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result("+", line, my_map);
};

bool REG_(string line, const map<string, vector<string>> &my_map)
{
	outfile << "[UNPROCESSED REG] " << line << endl;
	return true;
};

bool SUB_or_DEC(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result("-", line, my_map);
};

bool MOD_(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result("%", line, my_map);
};

bool DIV_(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result("/", line, my_map);
};

bool SHL_(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result("<<", line, my_map);
};

bool SHR_(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result(">>", line, my_map);
};

bool MUX2x1_(string line, const map<string, vector<string>> &my_map)
{
	outfile << "[UNPROCESSED MUX] " << line << endl;
	return true;
};

bool COMP_eq(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result("==", line, my_map);
};

bool COMP_lt(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result("<", line, my_map);
	return true;
};

bool COMP_gt(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result(">", line, my_map);
};

bool MUL_(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result("*", line, my_map);
};