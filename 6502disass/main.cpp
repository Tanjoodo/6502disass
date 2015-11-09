#include "decoder.h"
#include <iostream> 
#include <fstream>
#include <algorithm>

#include <cstdint>

using namespace std;
int main(int argc, char **argv)
{
	char *bytes;
	uint8_t *bytes8;
	int index = 0;
	size_t size = 0;
	if (argc < 2)
	{
		cout << "Please enter a file name" << endl;
		return 1;
	}
	else
	{
		ifstream inFile;
		inFile.open(argv[1], ios::in | ios::binary | ios::ate);
		if (inFile.is_open())
		{
			inFile.seekg(0, ios::end);
			size = inFile.tellg();
			inFile.seekg(0, ios::beg);

			bytes = new char[size];
			inFile.read(bytes, size);

			bytes8 = new uint8_t[size];
			std::copy(bytes, bytes + size, bytes8);
			delete[] bytes;
		}
		else
		{
			cout << "File input failed" << endl;
		}
	}

	while (index < size)
	{
		cout << hex << index << ": ";
		index += Decode(index, bytes8);
	}
	return 0;
}