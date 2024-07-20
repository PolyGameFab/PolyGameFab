cmake_minimum_required(VERSION 3.28)
project(glad)

include_directories(include)
add_library(glad src/glad.c)
