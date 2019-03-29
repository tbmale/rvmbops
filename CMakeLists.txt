cmake_minimum_required(VERSION 3.12)
SET(CMAKE_C_COMPILER "clang")
SET(CMAKE_CXX_COMPILER "clang++")
project(rvmbops)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(
  ${CMAKE_SOURCE_DIR}/rvmparser/src
  ${CMAKE_SOURCE_DIR}/cork/src
)

add_custom_target(
   cork
   COMMAND make
   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/cork/
)

file(GLOB SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
list(REMOVE_ITEM SOURCES
  "${CMAKE_SOURCE_DIR}/src/rvmbops.cpp"
)

add_library (${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/cork/lib/libcork.a libmpir.a)
add_executable(${PROJECT_NAME}test.exe ${SOURCES} ${CMAKE_SOURCE_DIR}/src/rvmbops.cpp)
target_link_libraries(${PROJECT_NAME}test.exe ${CMAKE_SOURCE_DIR}/cork/lib/libcork.a ${PROJECT_NAME} libmpir.a)
add_dependencies(${PROJECT_NAME} cork)