#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 3) {
		cout << "Usage: " << argv[0] << " netlistFile verilogFile" << endl;
		return 1;
	}

	ifstream infile(argv[1]);
	for (string line; getline(infile, line);) {
		if (line[0] == '/' && line[1] == '/')
			continue;

		istringstream iss(line);

		string first;

		iss >> first;
	}
	infile.close();

	ofstream outfile(argv[2]);

	return 0;
}
