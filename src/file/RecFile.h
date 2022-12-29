#ifndef REC_FILE_H
#define REC_FILE_H

#include "File.h"

class RecFile : public File {

	public:
		// Constructors
		RecFile(const string &name);

		// Overriden abstract methods from base class
		vector<DataBlock*> load();
		void save(const vector<DataBlock*> &data);

};

#endif