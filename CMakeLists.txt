cmake_minimum_required(VERSION 3.23)
project(labcalc)

set(CMAKE_CXX_STANDARD 14)

add_executable(labcalc main.cpp src/classes/classes.h src/classes/classes.cpp src/dbHandlers/db_handlers.cpp src/dbHandlers/db_handlers.h)
