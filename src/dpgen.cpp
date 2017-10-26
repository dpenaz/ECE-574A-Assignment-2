#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include "Verilog_Imp.h"
#include "dpgen.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 3) {
		cout << "Usage: " << argv[0] << " netlistFile verilogFile" << endl;
		return 1;
	}

	ifstream infile(argv[1]);
	ofstream outfile(argv[2]);

	string msg = "";
	string type;
	string token;

	int errorFlag = 0;

	map<string, vector<string>> var_map;	// Store variable info ex: variables[name][type, input/output/wire]
	vector<string> storedTokens;

	for (string line; getline(infile, line);)	// Pass through all lines of code
	{
		istringstream iss(line);

		while (iss >> token)	// Pass through each token in line
		{
			if (!token.compare("+")) {	// ADD and INC
				msg = Add_or_INC(line, var_map);
				break;
			}
			else if (!token.compare("=")) {	// REG
				msg = REG_(line, var_map);
				break;
			}
			else if (!token.compare("-")) {	// SUB and DEC
				msg = SUB_or_DEC(line, var_map);
				break;
			}
			else if (!token.compare("*")) {	// MUL
				msg = MUL_(line, var_map);
				break;
			}
			else if (!token.compare(">")) {	// COMP (gt output)
				msg = COMP_gt(line, var_map);
				break;
			}
			else if (!token.compare("<")) {	// COMP (lt output)
				msg = COMP_lt(line, var_map);
				break;
			}
			else if (!token.compare("==")) {// COMP (eq output)
				msg = COMP_eq(line, var_map);
				break;
			}
			else if (!token.compare("?") || 
				     !token.compare(":")) {	// MUX2x1
				msg = MUX2x1_(line, var_map);
				break;
			}
			else if (!token.compare("<<")) { // SHR
				msg = SHR_(line, var_map);
				break;
			}
			else if (!token.compare(">>")) { // SHL
				msg = SHL_(line, var_map);
				break;
			}
			else if (!token.compare("/")) {	// DIV
				msg = DIV_(line, var_map);
				break;
			}
			else if (!token.compare("%")) {	// MOD
				msg = MOD_(line, var_map);
				break;
			}
			else if (!token.compare("//")) { // COMMENT!!!
				break;
			}
			else if (!token.compare("input")) {	// input variables
				errorFlag = grabVariables(line, var_map);
				break;	// finished grabbing line continue to next 
			}
			else if (!token.compare("output")) { // output variables
				errorFlag = grabVariables(line, var_map);
				break;	// finished grabbing line continue to next line
			}
			else if (!token.compare("wire")) {	// wire variables
				errorFlag = grabVariables(line, var_map);
				break;	// finished grabbing line continue to next line
			}
			else if (!token.compare("register")) { // register variables
				errorFlag = grabVariables(line, var_map);
				break;	// finished grabbing line continue to next line
			}
			else {
				if (!checkKey(token, var_map))
				{
					// ERROR VARIABLE NOT DEFINED AS INPUT, OUTPUT, REGISTER or WIRE
					errorFlag = 1;
				}
				storedTokens.push_back(token);
				msg = "";
			}
		}

		if (errorFlag != 0) {
			outfile << errorMsg[errorFlag];
			break;
		}
		else
			outfile << msg;
	} 

	infile.close();
	outfile.close();

	return 0;
}

bool checkKey(string key, map<string, vector<string>> &my_map)
{
	for (map<string, vector<string>>::iterator it = my_map.begin(); it != my_map.end(); ++it) {
		if (!it->first.compare(key))
			return true;
	}
	return false;
}

int grabVariables(string line, map<string, vector<string>> &my_map)
{
	int error = 2;
	string func;
	string type;
	string token;
	istringstream iss(line);

	iss >> func;
	iss >> type;

	if (!checkType(type)) {	
		return error;
	}
										
	while (iss >> token)	// grab all tokens after input
	{
		if (token.back() == ',')
			token.pop_back();
		vector<string> newVector;
		newVector.push_back(func);
		newVector.push_back(type);
		my_map[token] = newVector;
	}
	return 0;
}

bool checkType(string type)
{
	for (int i = 0; i < 10; ++i) {
		if (!type.compare(dataTypes[i]))
			return true;
	}
	return false;
};