project(cw-qsort)

cmake_minimum_required(VERSION 3.12)

find_package(Boost COMPONENTS system)

include_directories(
	./include/
	${Boost_INCLUDE_DIRS}
)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
