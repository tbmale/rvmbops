cmake_minimum_required(VERSION 3.12)
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

add_library (${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/cork/lib/libcork.a)
add_dependencies(rvmbops cork)