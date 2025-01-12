cmake_minimum_required(VERSION 3.10)
project(dijkstra)
set(CMAKE_CXX_STANDARD 20)

set(PATH_TO_INCLUDES 
    ./src/include
)

set(app_SOURCES  
    ./src/main.cpp
   )


add_executable(${PROJECT_NAME} ${app_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PATH_TO_INCLUDES})