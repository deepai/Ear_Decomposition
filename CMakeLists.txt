cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

include_directories(/opt/OGDF/include)
LINK_DIRECTORIES(/opt/OGDF/_release)


add_compile_options(-std=c++11 -fopenmp -w)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -DVERIFY")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG")

add_executable(
	Ear_V1
	Codes/Modified_Ear_Decomposition_V1.cpp
)

add_executable(
	graph_csr_cc
	Codes/graph_csr_cc.cpp
)

add_executable(
	info
	Codes/info.cpp
)

add_executable(
	generator
	Codes/Generator.cpp
)

add_executable(
	Ear_V2
	Codes/Modified_Ear_Decomposition_V2.cpp
)

add_executable(
	Ear_Original
	Codes/Original_Ear_Decomposition.cpp
)

target_link_libraries(
	generator
	-lOGDF
	-lCOIN
	-pthread
)


target_link_libraries(
    Ear_V1
    -lgomp
)

target_link_libraries(
    Ear_V2
    -lgomp
)

target_link_libraries(
    Ear_Original
    -lgomp
)

set_target_properties( Ear_V1 Ear_V2 Ear_Original
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

