cmake_minimum_required(VERSION 3.23)
project(labcalc)

set(CMAKE_CXX_STANDARD 14)

add_executable(labcalc main.cpp src/dbHandlers/db_handlers.cpp src/dbHandlers/db_handlers.h src/classes/Calculator.cpp headers/Calculator.h src/classes/Date.cpp src/classes/Parcel.cpp src/classes/History.cpp src/classes/Map.cpp src/classes/Parameters.cpp headers/Date.h headers/History.h headers/Map.h headers/Parameters.h headers/Parcel.h headers/DTOs.h)
