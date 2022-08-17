cmake_minimum_required(VERSION 3.22)

project("thing-examples")

set(CMAKE_CXX_STANDARD 20)


function(add_example unit)
  string(REPLACE "/" "_" norm ${unit})
  string(REPLACE ".cpp" "" name ${norm})
  add_executable(${name} ${unit})

  set_target_properties(${name} PROPERTIES
    EXCLUDE_FROM_DEFAULT_BUILD TRUE)

  target_link_libraries(${name} thing)
endfunction()

add_example(three_bodies.cpp)
