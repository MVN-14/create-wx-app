cmake_minimum_required(VERSION 3.0.0)
project(create-wxApp VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp
                               src/createwxapp.cpp)

