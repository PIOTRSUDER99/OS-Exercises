#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;
int main()
{
	ifstream infile("pipe1");
	string outStr;
	int count = 0;

	while (getline(infile, outStr))
	{
		if (outStr == "Operation successful.")
		{
			count++;
		}
		if (outStr == "Operation failed.")
		{
			count++;
		}
	}

	infile.close();
	cout << "Program failed on operation " << count << endl;

	return 0;
}
