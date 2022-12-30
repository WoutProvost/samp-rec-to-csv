#include "Converter.h"

int main(int argc, char **argv) {
	Converter app(Converter::CSV, Converter::REC);
	app.run(argc, argv);
}