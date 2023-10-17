cmake_minimum_required(VERSION 3.28)

project(Language_Plus LANGUAGES CXX C VERSION 1.1.4.514)

string(TIMESTAMP Language_Plus_BUILD_TIME "%Y-%m-%d %H:%M:%S" UTC)

include_directories(Inc)

file(GLOB_RECURSE Language_Plus_Src Src/*.c)

add_executable(Language_Plus ${Language_Plus_Src})