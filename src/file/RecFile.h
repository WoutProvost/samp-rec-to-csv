#ifndef REC_FILE_H
#define REC_FILE_H

#include "File.h"

class RecFile : public File {

	private:
		// Overriden abstract methods from base class
		void loadData(vector<DataBlock*> &data);
		void saveData(const vector<DataBlock*> &data);

	public:
		// Constructors
		RecFile(const string &name);

};

#endif