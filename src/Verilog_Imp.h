#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool Add_or_INC(string line, const map<string, vector<string>> &my_map);
bool REG_(string line, const map<string, vector<string>> &my_map);
bool SUB_or_DEC(string line, const map<string, vector<string>> &my_map);
bool MOD_(string line, const map<string, vector<string>> &my_map);
bool DIV_(string line, const map<string, vector<string>> &my_map);
bool SHL_(string line, const map<string, vector<string>> &my_map);
bool SHR_(string line, const map<string, vector<string>> &my_map);
bool MUX2x1_(string line, const map<string, vector<string>> &my_map);
bool COMP_eq(string line, const map<string, vector<string>> &my_map);
bool COMP_lt(string line, const map<string, vector<string>> &my_map);
bool COMP_gt(string line, const map<string, vector<string>> &my_map);
bool MUL_(string line, const map<string, vector<string>> &my_map);