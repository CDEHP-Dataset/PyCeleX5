cmake_minimum_required(VERSION 3.4...3.18)
project(pycelex5)

add_subdirectory(pybind11)
pybind11_add_module(PyCeleX5 src/main.cpp)

target_compile_definitions(PyCeleX5 PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
