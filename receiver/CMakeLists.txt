cmake_minimum_required(VERSION 3.28)
project(receiver)

set(CMAKE_CXX_STANDARD 23)

#Boost 라이브러리 설치 확인
find_package(Boost)

if(Boost_FOUND)
        # include 패스 설정
        include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(receiver main.cpp
        )
