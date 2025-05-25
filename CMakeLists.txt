cmake_minimum_required(VERSION 3.26)
project(OIAKP)

set(CMAKE_CXX_STANDARD 17)

add_executable(OIAKP main.cpp
        CarrySkipAdder.cpp
        include/CarrySkipAdder.h
        RandomData.cpp
        include/RandomData.h
        AdderEta.cpp
        include/AdderEta.h
        CheckResult.cpp
        include/CheckResult.h
        WriteData.cpp
        include/WriteData.h
        Timer.cpp
        include/Timer.h
        CheckCSA.cpp
        include/CheckCSA.h
)
