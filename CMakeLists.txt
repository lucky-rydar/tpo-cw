project(cw-qsort)

cmake_minimum_required(VERSION 3.12)

include_directories(
	./include/
)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
