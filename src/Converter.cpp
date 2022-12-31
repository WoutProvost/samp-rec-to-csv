#include "Converter.h"
#include <iostream>
#include <cstring>
#include <vector>
#include "data/DataBlock.h"
#include "file/RecFile.h"
#include "file/CsvFile.h"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;

#define ANSI_RESET	"\u001b[0m"
#define ANSI_RED	"\u001b[31m"
#define ANSI_GREEN	"\u001b[32m"

const string Converter::REC = ".rec";
const string Converter::CSV = ".csv";

Converter::Converter(const string &extSrc, const string extDest) :
	// Initialize attributes
	cmd(""),
	extSrc(extSrc),
	extDest(extDest) {
}

void Converter::run(int argc, char **argv) {
	cmd = argv[0];

	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
			printUsageAndExitWithCode(false);
		}
	}

	if (argc < 3) {
		printUsageAndExitWithCode();
	}

	if (argc == 3) {
		path src(argv[1]);
		path dest(argv[2]);

		if (!fs::is_regular_file(src) || src.extension() != extSrc) {
			printSourceError(src);
		}

		if (dest.extension() != extDest) {
			printError("Destination '" + dest.string() + "' does not have extension '" + extDest + "'");
		}

		fs::create_directories(dest.parent_path());
		convertFile(src, dest);
	} else {
		path dir(argv[argc-1]);

		if (fs::is_regular_file(dir)) {
			printError("Directory '" + dir.string() + "' exists as a file");
		}

		fs::create_directories(dir);

		int success = 0;
		for (int i = 1; i < argc-1; i++) {
			path src(argv[i]);

			if (!fs::is_regular_file(src) || src.extension() != extSrc) {
				printSourceError(src, false);
			} else {
				if (convertFile(src, dir / src.stem().concat(extDest), false)) {
					success++;
				}
			}
		}
		cout << cmd << ": " << ANSI_GREEN << "Converted " << success << "/" << argc-2 << " files successfully." << ANSI_RESET << endl;
	}
	exit(EXIT_SUCCESS);
}

bool Converter::convertFile(const path &src, const path &dest, bool exitOnError) {
	File *input;
	File *output;

	if (src.extension() == REC) {
		input = new RecFile(src);
	} else {
		input = new CsvFile(src);
	}
	if (dest.extension() == CSV) {
		output = new CsvFile(dest);
	} else {
		output = new RecFile(dest);
	}

	// Load data from source file
	vector<DataBlock*> data = input->load();

	if (data.empty()) {
		// Handle corrupt source file
		delete input;
		delete output;
		printError("Source '" + src.string() + "' is corrupt", false);
		if (exitOnError) {
			exit(EXIT_FAILURE);
		}
		return false;
	} else {
		// Save data to destination file
		output->save(data);

		for (auto block : data) {
			delete block;
		}
		data.clear();
		delete input;
		delete output;
		return true;
	}
}

void Converter::printSourceError(const path &src, bool printUsageAndExit) {
	printError("Source '" + src.string() + "' is not an existing '" + extSrc + "' file", printUsageAndExit);
}

void Converter::printError(const string &msg, bool printUsageAndExit) {
	cerr << cmd << ": " << ANSI_RED << msg << "." << ANSI_RESET << endl;
	if (printUsageAndExit) {
		printUsageAndExitWithCode();
	}
}

void Converter::printUsageAndExitWithCode(bool fail) {	
	cerr << "Usage: " << cmd << " [source" << extSrc << "] [destination" << extDest << "]" << endl;
	cerr << "       " << cmd << " [source" << extSrc << "]... [directory]" << endl;
	exit(fail ? EXIT_FAILURE : EXIT_SUCCESS);
}