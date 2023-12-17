cmake_minimum_required(VERSION 3.1)
project(stb_image)

add_library(stb_image stb_image.h stb_image.c)
target_include_directories(stb_image PUBLIC ./)
