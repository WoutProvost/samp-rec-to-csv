#include "File.h"

using std::ios_base;

File::File(const string &name, bool binary) :
	// Initialize attributes
	name(name),
	binary(binary) {
}

vector<DataBlock*> File::load() {
	ios_base::openmode mode = ios_base::in;
	if (binary) {
		mode |= ios_base::binary;
	}

	input = ifstream(name, mode);

	return vector<DataBlock*>();
}

void File::save(const vector<DataBlock*> &data) {
	ios_base::openmode mode = ios_base::out;
	if (binary) {
		mode |= ios_base::binary;
	}

	output = ofstream(name, mode);
}