cmake_minimum_required(VERSION 3.10)
project(CPP_apps)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach(testsourcefile ${APP_SOURCES})
    get_filename_component(testname ${testsourcefile} NAME_WE)

    get_filename_component(testdir ${testsourcefile} DIRECTORY)

    add_executable(${testname} ${testsourcefile})

    set_target_properties(${testname} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${testdir})
endforeach(testsourcefile ${APP_SOURCES})