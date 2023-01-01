#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
#include <vector>
#include "../data/DataBlock.h"
#include "../data/HeaderDataBlock.h"
#include "../data/OnFootDataBlock.h"
#include "../data/VehicleDataBlock.h"
#include "../data/PlayerRecordingType.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;

class File {

	private:
		// Attributes
		bool binary;

		// Abstract methods
		virtual void loadData(vector<DataBlock*> &data) = 0;
		virtual void saveData(const vector<DataBlock*> &data) = 0;

	protected:
		// Attributes
		string name;
		ifstream input;
		ofstream output;

		// Constructors
		File(const string &name, bool binary);

	public:
		// Methods
		vector<DataBlock*> load();
		void save(const vector<DataBlock*> &data);

};

#endif