cmake_minimum_required(VERSION 3.7)
project(linearC)

include_directories(src/)
SET(GCC_COMPILE_FLAGS "-std=c++11 -g -rdynamic")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS} -ldl")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Debug/bin")

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        src/peripheral/argsParser.cpp src/peripheral/argsParser.h
        src/peripheral/stringParser.cpp src/peripheral/stringParser.h
        src/peripheral/sysArgs.cpp src/peripheral/sysArgs.h
        src/peripheral/timer.cpp src/peripheral/timer.h
        src/utilities/flags.cpp src/utilities/flags.h
        src/utilities/internalError.cpp src/utilities/internalError.h
        src/utilities/macros.cpp src/utilities/macros.h
        src/utilities/strings.cpp src/utilities/strings.h
        src/utilities/systems.cpp src/utilities/strings.h
        src/compiler/parser.cpp src/compiler/parser.h
        src/compiler/translator.cpp src/compiler/translator.h
        src/peripheral/fileParser.cpp src/peripheral/fileParser.h src/compiler/symbolTable.cpp src/compiler/symbolTable.h)
add_executable(linearC ${SOURCE_FILES})
target_link_libraries(linearC ${CMAKE_DL_LIBS})