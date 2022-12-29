# Add these libraries to be built
add_library(data_block SHARED DataBlock.h)
add_library(header_data_block SHARED HeaderDataBlock.h)
add_library(on_foot_data_block SHARED OnFootDataBlock.h)
add_library(vehicle_data_block SHARED VehicleDataBlock.h)

# Define the dependencies of these libraries
target_link_libraries(header_data_block
	data_block)
target_link_libraries(on_foot_data_block
	data_block)
target_link_libraries(vehicle_data_block
	data_block)

# Set properties of these libraries
set_target_properties(data_block PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(header_data_block PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(on_foot_data_block PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(vehicle_data_block PROPERTIES LINKER_LANGUAGE CXX)