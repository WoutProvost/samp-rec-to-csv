cmake_minimum_required(VERSION 3.10)
project(samp-rec-to-csv
	VERSION 1.0.0
	DESCRIPTION "File format converter from .rec to .csv and vice versa, which NPCs use in SA-MP to play back recordings"
	LANGUAGES CXX)

# Add these executables to be built
add_executable(rec2csv src/RecToCsv.cpp)
add_executable(csv2rec src/CsvToRec.cpp)

# Define the dependencies of these executables
target_link_libraries(rec2csv
	rec_file
	csv_file)
target_link_libraries(csv2rec
	rec_file
	csv_file)

# Descend into these subdirectories
add_subdirectory(src/data)
add_subdirectory(src/file)