#include "Converter.h"

int main(int argc, char **argv) {
	Converter app(Converter::REC, Converter::CSV);
	app.run(argc, argv);
}