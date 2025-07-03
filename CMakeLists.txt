cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(project_name to_do)
set(src
    lib/colours.hpp
    lib/helper.cpp
    src/tasksaver.cpp
    src/optionsmenu.cpp 
    src/taskdata.cpp
    src/todomanager.cpp
    src/taskloader.cpp
    main.cpp
)
project(${project_name})
include_directories(${CMAKE_SOURCE_DIR})
add_executable(${project_name} ${src})
