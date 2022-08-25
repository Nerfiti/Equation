cmake_minimum_required(VERSION 3.23)
project (Equation)

set(CMAKE_CXX_STANDARD 14)

add_executable(Equation main.cpp SolveEquation.cpp UnitTestEquation.cpp)
