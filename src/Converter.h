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
		bool convertFile(const path &src, const path &dest, bool exitOnError = true);
		void printSourceError(const path &src, bool printUsageAndExit = true);
		void printError(const string &msg, bool printUsageAndExit = true);
		void printUsageAndExitWithCode(bool fail = true);

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