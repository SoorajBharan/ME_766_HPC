# Minimum cmake version required
cmake_minimum_required(VERSION 3.10)

# set cmake variable
set(PROJECT_NAME integration)

# set project name
project(${PROJECT_NAME})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add profiling flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
# set source files
set(SOURCES
	include/main.cpp
	include/enum_types.h
	include/random_number_generator.h
	include/monte_carlo_method.h
	include/trapezoidal_integration.h)

# set an output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Specify include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Enable installation
install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin)

# Optionally, install headers (if needed)
install(FILES include/trapezoidal_integration.h DESTINATION include)
