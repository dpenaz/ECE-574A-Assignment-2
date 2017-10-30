#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Verilog_Imp.h"

using namespace std;

bool checkKey(string key, const map<string, vector<string>> &my_map);
extern ofstream outfile;
extern bool regFound;

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

unsigned int numAdd = 0, numSub = 0, numMod = 0, numDiv = 0, numShl = 0, numShr = 0, numComp = 0, numMul = 0, numMux = 0, numReg = 0;

bool assign_op_result(string op, string line, const map<string, vector<string>> &my_map)
{
	string out, in1, in2;
	istringstream iss(line);
	int bitSize = getLgBit(line, my_map);

	string curSym;

	// OUT
	iss >> curSym;

	if (!checkKey(curSym, my_map)) {
		cerr << "Error: unexpected symbol: " << curSym << " in following line:" << endl << line << endl;
		return false;
	}
	else if (!is_wire(curSym, my_map)) {
		cerr << "Error: '" << curSym << "' is not a wire in following line:" << endl << line << endl;
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

	string outstr;
	bool gt = false, lt = false, eq = false;

	if (!op.compare("+"))
		outstr = "ADD#(" + to_string(bitSize) + ") Adder_" + to_string(++numAdd);
	else if (!op.compare("-"))
		outstr = "SUB#(" + to_string(bitSize) + ") Sub_" + to_string(++numSub);
	else if (!op.compare("%"))
		outstr = "MOD#(" + to_string(bitSize) + ") Mod_" + to_string(++numMod);
	else if (!op.compare("/"))
		outstr = "DIV#(" + to_string(bitSize) + ") Div_" + to_string(++numDiv);
	else if (!op.compare("<<"))
		outstr = "SHL#(" + to_string(bitSize) + ") Shl_" + to_string(++numShl);
	else if (!op.compare(">>"))
		outstr = "SHR#(" + to_string(bitSize) + ") Shr_" + to_string(++numShr);
	else if (!op.compare("==")) {
		eq = true;
		outstr = "COMP#(" + to_string(bitSize) + ") Comp_" + to_string(++numComp);
	}
	else if (!op.compare("<")) {
		lt = true;
		outstr = "COMP#(" + to_string(bitSize) + ") Comp_" + to_string(++numComp);
	}
	else if (!op.compare(">")) {
		gt = true;
		outstr = "COMP#(" + to_string(bitSize) + ") Comp_" + to_string(++numComp);
	}
	else if (!op.compare("*"))
		outstr = "MUL#(" + to_string(bitSize) + ") Mul_" + to_string(++numMul);
	else {
		cerr << "Unknown operation: " << op << "in line: " << endl << line << endl;
		return false;
	}

	if (gt)
		outstr = outstr + "(" + in1 + "," + in2 + "," + out + ",,);";
	else if (lt)
		outstr = outstr + "(" + in1 + "," + in2 + ",," + out + ",);";
	else if (eq)
		outstr = outstr + "(" + in1 + "," + in2 + ",,," + out + ");";
	else
		outstr = outstr + "(" + in1 + "," + in2 + "," + out + ");";

	outfile << outstr << endl;
	
	return true;
}

bool Add_or_INC(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result("+", line, my_map);
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

bool COMP_eq(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result("==", line, my_map);
};

bool COMP_lt(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result("<", line, my_map);
};

bool COMP_gt(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result(">", line, my_map);
};

bool MUL_(string line, const map<string, vector<string>> &my_map)
{
	return assign_op_result("*", line, my_map);
};

bool REG_(string line, const map<string, vector<string>> &my_map)
{
	string out, in;
	istringstream iss(line);
	int bitSize = getLgBit(line, my_map);

	string curSym;

	// OUT
	iss >> curSym;

	if (!checkKey(curSym, my_map)) {
		cerr << "Error: unexpected symbol: " << curSym << " in following line:" << endl << line << endl;
		return false;
	}
	else if (!is_output(curSym, my_map)) {
		cerr << "Error: '" << curSym << "' is not an output in following line:" << endl << line << endl;
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
	else if (!is_input(curSym, my_map) && !is_wire(curSym, my_map)) {
		cerr << "Error: " << curSym << " is not an input or a wire in following line:" << endl << line << endl;
		return false;
	}
	in = curSym;

	// end of line
	iss >> curSym;
	if (!iss.eof()) {
		cerr << "Error: expected end of line, not '" << curSym << "' in following line:" << endl << line << endl;
		return false;
	}

	outfile << "REG#(" + to_string(bitSize) + ") Reg_" << ++numReg << "(" << in << "," << out << ",clk,rst);" << endl;
	regFound = true;

	return true;
};

bool MUX2x1_(string line, const map<string, vector<string>> &my_map)
{
	string out, in1, in2, in3;
	istringstream iss(line);
	int bitSize = getLgBit(line, my_map);

	string curSym;

	// OUT
	iss >> curSym;

	if (!checkKey(curSym, my_map)) {
		cerr << "Error: unexpected symbol: " << curSym << " in following line:" << endl << line << endl;
		return false;
	}
	else if (!is_wire(curSym, my_map) && !is_output(curSym, my_map)) { //TBD
		cerr << "Error: '" << curSym << "' is not a wire or output in following line:" << endl << line << endl;
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
	else if (!is_input(curSym, my_map) && !is_wire(curSym, my_map)) {
		cerr << "Error: " << curSym << " is not an input or a wire in following line:" << endl << line << endl;
		return false;
	}
	in1 = curSym;

	// operation
	iss >> curSym;

	if (curSym.compare("?")) {
		cerr << "Error: expected '?', not '" << curSym << "' in following line:" << endl << line << endl;
		return false;
	}

	// IN2
	iss >> curSym;

	if (!checkKey(curSym, my_map)) {
		cerr << "Error: unexpected symbol: " << curSym << " in following line:" << endl << line << endl;
		return false;
	}
	else if (!is_input(curSym, my_map) && !is_wire(curSym, my_map)) {
		cerr << "Error: " << curSym << " is not an input or a wire in following line:" << endl << line << endl;
		return false;
	}
	in2 = curSym;

	// operation
	iss >> curSym;

	if (curSym.compare(":")) {
		cerr << "Error: expected ':', not '" << curSym << "' in following line:" << endl << line << endl;
		return false;
	}

	// IN3
	iss >> curSym;

	if (!checkKey(curSym, my_map)) {
		cerr << "Error: unexpected symbol: " << curSym << " in following line:" << endl << line << endl;
		return false;
	}
	else if (!is_input(curSym, my_map) && !is_wire(curSym, my_map)) {
		cerr << "Error: " << curSym << " is not an input or a wire in following line:" << endl << line << endl;
		return false;
	}
	in3 = curSym;

	// end of line
	iss >> curSym;
	if (!iss.eof()) {
		cerr << "Error: expected end of line, not '" << curSym << "' in following line:" << endl << line << endl;
		return false;
	}

	outfile << "MUX2x1#(" + to_string(bitSize) + ") Mux_" << ++numMux << "(" << in2 << "," << in3 << "," << in1 << ");" << endl;

	return true;
}


int getLgBit(string line, const map<string, vector<string>> &my_map)
{
	char curSym[20];
	string key;
	string type;
	int bitSize = 0;
	istringstream iss(line);

	while (iss >> curSym)
	{
		if (!isalpha(curSym[0]))
			continue;
		key = curSym;
		map<string, vector<string>>::const_iterator it = my_map.find(key);
		if (it == my_map.end())
			return 0;
		type = it->second[1];
		if (type[0] == 'I')
			type.erase(0, 3);
		else
			type.erase(0, 4);

		if (stoi(type) > bitSize)
			bitSize = stoi(type);
	}
	return bitSize;
}