#include <string>

string dataTypes[12] = {"Int1", "UInt1", "Int2", "UInt2", "Int8", "UInt8",
						"Int16", "UInt16", "Int32", "UInt32", "Int64", "UInt64" };
string errorMsg[3] = {"","ERROR: Invalid Format Detected in netlistFile",
					  "ERROR: Invalid Type Provided in netlistFile" };

bool checkType(string type);
bool checkKey(string key, map<string, vector<string>> &my_map);
int grabVariables(string line, map<string, vector<string>> &my_map);
