#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		printf("First Argument is the name of the file\n");
		return 0;
	}
	
	int num_nodes, num_columns;

	ifstream fin(argv[1],ios::in);

	fin >> num_nodes;
	fin >> num_columns;

	cout << num_nodes << " " << num_columns/2 << endl;

	fin.close();	

	return 0;
}
