#ifndef CSV_FILE_H
#define CSV_FILE_H

#include "File.h"

class CsvFile : public File {

	private:
		// Methods
		vector<string> readLine();

	public:
		// Constructors
		CsvFile(const string &name);

		// Overriden abstract methods from base class
		vector<DataBlock*> load();
		void save(const vector<DataBlock*> &data);

};

#endif