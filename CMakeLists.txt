cmake_minimum_required(VERSION 3.12)
project(school-cpp-project)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)

set(SOURCE_FILES
        main.h
        main.cpp
        testyStack.cpp

        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc testyExpressions.cpp testySubory.cpp)

include_directories(GoogleTest)
add_executable(school-cpp-project ${SOURCE_FILES})
target_link_libraries(school-cpp-project ${CMAKE_THREAD_LIBS_INIT})

add_custom_command(TARGET school-cpp-project PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/vyrazy.txt
        ${CMAKE_SOURCE_DIR}/vyrazySPremennou.txt
        ${CMAKE_SOURCE_DIR}/vyrazySCyklom.txt
        ${CMAKE_SOURCE_DIR}/dalsieVyrazy.txt
        $<TARGET_FILE_DIR:school-cpp-project>
        VERBATIM)
