cmake_minimum_required(VERSION 3.22)

project("thing-tests")

set(CMAKE_CXX_STANDARD 20)

include(CTest)

function(new_test_static_fail unit)
  string(REPLACE "/" "_" norm ${unit})
  string(REPLACE ".cpp" "" name ${norm})
  add_executable(${name} ${unit})
  set_target_properties(${name} PROPERTIES
    EXCLUDE_FROM_ALL TRUE
    EXCLUDE_FROM_DEFAULT_BUILD TRUE)
  target_link_libraries(${name} thing)

  add_test(NAME ${name}
    COMMAND ${CMAKE_COMMAND} --build . --target ${name} --config $<CONFIGURATION>
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  set_tests_properties(${name} PROPERTIES WILL_FAIL TRUE)
endfunction()

function(new_test unit)
  string(REPLACE "/" "_" norm ${unit})
  string(REPLACE ".cpp" "" name ${norm})
  add_executable(${name} ${unit})
  target_link_libraries(${name} thing)

  add_test(NAME ${name} COMMAND ${name})
endfunction()

# Context/system
new_test_static_fail(context/duplicate_tags.cpp)
new_test_static_fail(context/no_properties.cpp)

new_test(context/basic_system.cpp)
new_test(context/system_resize.cpp)
new_test(context/zero_system.cpp)


# Iterator
new_test(iterator/range_based_assign.cpp)
new_test(iterator/range_based_for.cpp)
new_test(iterator/iterate_over.cpp)
