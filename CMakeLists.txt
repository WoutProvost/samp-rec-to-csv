cmake_minimum_required(VERSION 3.10)
project(samp-rec-to-csv
	VERSION 1.0.0
	DESCRIPTION "File format converter from .rec to .csv and vice versa, which NPCs use in SA-MP to play back recordings"
	LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add these libraries to be built
add_library(converter SHARED src/Converter.h src/Converter.cpp)

# Define the dependencies of these libraries
target_link_libraries(converter
	rec_file
	csv_file)

# Add these executables to be built
add_executable(rec2csv src/RecToCsv.cpp)
add_executable(csv2rec src/CsvToRec.cpp)

# Define the dependencies of these executables
target_link_libraries(rec2csv
	converter)
target_link_libraries(csv2rec
	converter)

# Descend into these subdirectories
add_subdirectory(src/data)
add_subdirectory(src/file)