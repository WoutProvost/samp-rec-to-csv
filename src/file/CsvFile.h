#ifndef CSV_FILE_H
#define CSV_FILE_H

#include "File.h"

class CsvFile : public File {

	private:
		// Methods
		vector<string> readLine();

		// Overriden abstract methods from base class
		void loadData(vector<DataBlock*> &data);
		void saveData(const vector<DataBlock*> &data);

	public:
		// Constructors
		CsvFile(const string &name);

};

#endif