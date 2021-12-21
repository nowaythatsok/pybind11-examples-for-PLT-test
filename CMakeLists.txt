cmake_minimum_required(VERSION 3.4...3.18)
project(cpp_mean_source)
add_subdirectory(pybind11)
pybind11_add_module(cpp_mean_module_name cpp_mean_source.cpp)