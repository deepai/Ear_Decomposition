cmake_minimum_required(VERSION 3.0)

add_compile_options(-O3 -std=c++11 -fopenmp -w)

add_executable(
	Ear_V1
	Codes/Modified_Ear_Decomposition_V1.cpp
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

