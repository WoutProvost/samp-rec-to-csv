# Add these libraries to be built
add_library(file SHARED File.h File.cpp)
add_library(rec_file MODULE RecFile.h RecFile.cpp)
add_library(csv_file MODULE CsvFile.h CsvFile.cpp)

# Define the dependencies of these libraries
target_link_libraries(rec_file
	file
	header_data_block
	on_foot_data_block
	vehicle_data_block)
target_link_libraries(csv_file
	file
	header_data_block
	on_foot_data_block
	vehicle_data_block)