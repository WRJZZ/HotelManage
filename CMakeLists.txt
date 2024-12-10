cmake_minimum_required(VERSION 3.28)
project(HotelManage)

set(CMAKE_CXX_STANDARD 11)

add_executable(HotelManage main.cpp
        Room.cpp
        Room.h
        Guest.cpp
        Guest.h
        Manager.cpp
        Manager.h)
