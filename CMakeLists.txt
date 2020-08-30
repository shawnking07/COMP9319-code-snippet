cmake_minimum_required(VERSION 3.16)
project(demo)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        /usr/local/include
)

link_directories(
        /usr/local/lib
)

file(GLOB_RECURSE mains RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" linear-time-SA.cpp XBW.cpp q1.cpp q2.cpp q3.cpp)

foreach(mainfile IN LISTS mains)
    get_filename_component(mainname ${mainfile} NAME_WE)
    add_executable(${mainname} ${mainfile})
    target_link_libraries(${mainname})
endforeach()

#add_executable(a1 aencoder.cpp)


