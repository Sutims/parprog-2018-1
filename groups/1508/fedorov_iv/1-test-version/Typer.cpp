// Typer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	int size;
	bool *data;
	//read this string file
	ifstream file(argv[1]);

	file >> size;
	data = new bool[size];

	for (int i = 0; i < size; i++) {
		file >> data[i];
	}
	//write binary file
	freopen(argv[2], "wb", stdout);
	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(data, sizeof(*data), size, stdout);

	return 0;
}
