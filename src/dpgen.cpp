#include <iostream>
#include <vector>
#include <string>

using namespace std;

class token
{
	enum class {
		ID,
		SUM,
		MULT,
		DIV,
		MOD,
		//etc.
	};
};

vector<token>
ParseTokens(string filename)
{
	return {};
}


int main(int argc, char *argv[])
{
	if (argc < 3) {
		cout << "Usage: " << argv[0] << " netlistFile verilogFile" << endl;
		return 1;
	}

	vector<token> netlistTokens{ ParseTokens(argv[1]) };
	//parsing netlistParsing{netlistFile{argv[1],ifstream::in}};
	
	cout << "done" << endl;
	return 0;
}