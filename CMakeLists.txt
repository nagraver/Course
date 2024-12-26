    cmake_minimum_required(VERSION 3.20)
    project(MyProject)

    set(CMAKE_CXX_STANDARD 20)

    add_executable(main main.cpp files.cpp refactoring.cpp scrolling.cpp service.cpp)
    
    