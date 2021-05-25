cmake_minimum_required(VERSION 3.4...3.18)
project(pycelex5 LANGUAGES CXX)

find_package(Python COMPONENTS Interpreter Development)
find_package(OpenCV 3.3 REQUIRED)

include_directories(include)
link_directories(lib)

add_subdirectory(pybind11)
pybind11_add_module(PyCeleX5 SHARED src/main.cpp src/pycelex5.cpp src/binfileobserver.cpp)

target_link_libraries(PyCeleX5 PUBLIC libCeleX.so ${OpenCV_LIBS})
