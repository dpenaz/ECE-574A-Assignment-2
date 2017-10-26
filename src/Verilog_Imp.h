#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool Add_or_INC(string line, map<string, vector<string>> &my_map);
string REG_(string line, map<string, vector<string>> &my_map);
string SUB_or_DEC(string line, map<string, vector<string>> &my_map);
string MOD_(string line, map<string, vector<string>> &my_map);
string DIV_(string line, map<string, vector<string>> &my_map);
string SHL_(string line, map<string, vector<string>> &my_map);
string SHR_(string line, map<string, vector<string>> &my_map);
string MUX2x1_(string line, map<string, vector<string>> &my_map);
string COMP_eq(string line, map<string, vector<string>> &my_map);
string COMP_lt(string line, map<string, vector<string>> &my_map);
string COMP_gt(string line, map<string, vector<string>> &my_map);
string MUL_(string line, map<string, vector<string>> &my_map);