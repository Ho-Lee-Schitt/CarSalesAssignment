# cmake_minimum_required(VERSION <specify CMake version here>)
project(CarSalesAssignment)

set(CMAKE_CXX_STANDARD 17)

add_executable(CarSalesAssignment
        src/main.cpp
        src/car.cpp
        src/car_database.cpp)

