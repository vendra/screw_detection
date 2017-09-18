project(screw_detection)
cmake_minimum_required(VERSION 2.8)

find_package(OpenCV REQUIRED)
include_directories( ${PROJECT_SOURCE_DIR}/include )
#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_library(screw_matching include/screw_matching.h src/screw_matching.cpp)
add_library(utility include/utility.h src/utility.cpp)

target_link_libraries(screw_matching ${OpenCV_LIBS} )
target_link_libraries(utility ${OpenCV_LIBS} )

add_executable (main src/main.cpp)
target_link_libraries( main ${OpenCV_LIBS} screw_matching utility)
