cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME FileServer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(${PROJECT_NAME} VERSION 1.0.0)

configure_file(
  "${PROJECT_SOURCE_DIR}/include/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_BINARY_DIR}")

aux_source_directory("${PROJECT_SOURCE_DIR}/src" SRC_DIR)

add_executable(${PROJECT_NAME} app/main.cc ${SRC_DIR})

find_package(Boost REQUIRED COMPONENTS system)
if(Boost_FOUND)
  target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system)
else()
  message("Boost Not Found!")
endif(Boost_FOUND)

