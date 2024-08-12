
cmake_minimum_required(VERSION 3.20)
project(rgb-remote-control VERSION 1.0.0)

set(SRC_DIR src)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -Wextra -O3")

# Find and include libcurl
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

# Find and include libjson-c
find_path(JSON_C_INCLUDE_DIR json-c/json.h)
find_library(JSON_C_LIBRARY json-c)

include_directories(${JSON_C_INCLUDE_DIR})

# Add source files
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES} ${JSON_C_LIBRARY})
