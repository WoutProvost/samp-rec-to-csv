#include <iostream>
#include <vector>
#include "data/DataBlock.h"
#include "file/RecFile.h"
#include "file/CsvFile.h"

using std::vector;

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " [input.rec] [output.csv]" << std::endl;
		return 1;
	}

	RecFile input(argv[1]);
	vector<DataBlock*> data = input.load();

	CsvFile output(argv[2]);
	output.save(data);

	for (auto block : data) {
		delete block;
	}
	return 0;
}