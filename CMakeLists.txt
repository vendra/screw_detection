project(screw_detection)
cmake_minimum_required(VERSION 2.8)

find_package(OpenCV REQUIRED)
include_directories( ${PROJECT_SOURCE_DIR}/include )
#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_library(ScrewMatcher include/ScrewMatcher.h src/ScrewMatcher.cpp)
add_library(utility include/utility.h src/utility.cpp)

target_link_libraries(ScrewMatcher ${OpenCV_LIBS} )
target_link_libraries(utility ${OpenCV_LIBS} )

add_executable (ScrewDetection src/main.cpp)
target_link_libraries( ScrewDetection ${OpenCV_LIBS} ScrewMatcher utility)
