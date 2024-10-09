cmake_minimum_required(VERSION 3.28)
project(server)

set(CMAKE_CXX_STANDARD 23)

#Boost 라이브러리 설치 확인
find_package(Boost)

# 전역적으로 C++ 컴파일러 옵션 설정
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

if(Boost_FOUND)
    # include 패스 설정
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(server main.cpp
        communication/map_handler.hpp
        communication/communication.hpp
        cmd_handler/cmd_handler.hpp
)
