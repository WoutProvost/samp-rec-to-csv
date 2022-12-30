#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <filesystem>

using std::string;
namespace fs = std::filesystem;
using fs::path;

class Converter {

	private:
		// Attributes
		string cmd;
		string extSrc;
		string extDest;

		// Methods
		void convertFile(const path &src, const path &dest);
		void printSourceError(const path &src, bool exit = true);
		void printError(const string &msg, bool exit = true);
		void printUsage();

	public:
		// Constants
		static const string REC;
		static const string CSV;

		// Constructors
		Converter(const string &extSrc, const string extDest);

		// Methods
		void run(int argc, char **argv);

};

#endif