cmake_minimum_required(VERSION 3.5.0)
project(leveldb_bench VERSION 0.1.0 LANGUAGES C CXX)

add_executable(leveldb_bench main.cpp)

find_package(LevelDB REQUIRED)
target_link_libraries(leveldb_bench leveldb)