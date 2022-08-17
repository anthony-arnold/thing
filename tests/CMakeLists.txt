cmake_minimum_required(VERSION 3.22)

project("thing-tests")

set(CMAKE_CXX_STANDARD 20)

include(CTest)

function(new_test unit)
  # Check params
  set (WILL_FAIL OFF)
  set (STATIC OFF)
  foreach(V ${ARGN})
    if(${V} STREQUAL STATIC)
      set (STATIC ON)
    endif()
    if(${V} STREQUAL WILL_FAIL)
      set (WILL_FAIL ON)
    endif()
  endforeach()

  # Make hidden target
  string(REPLACE "/" "_" norm ${unit})
  string(REPLACE ".cpp" "" name ${norm})
  add_executable(${name} ${unit})
  set_target_properties(${name} PROPERTIES
    EXCLUDE_FROM_ALL TRUE
    EXCLUDE_FROM_DEFAULT_BUILD TRUE)
  target_link_libraries(${name} thing)

  # Add a test for building the target
  add_test(NAME build_${name}
    COMMAND ${CMAKE_COMMAND} --build . --target ${name} --config $<CONFIGURATION>
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

  # If not static, add a test for running the target
  if (NOT ${STATIC})
    add_test(NAME run_${name} COMMAND ${name})
    set_tests_properties(run_${name}
      PROPERTIES DEPENDS build_${name})
    set_tests_properties(run_${name}
      PROPERTIES WILL_FAIL ${WILL_FAIL})
  else()
    set_tests_properties(build_${name}
      PROPERTIES WILL_FAIL ${WILL_FAIL})
  endif()
endfunction()

# Context/system
new_test(context/duplicate_tags.cpp STATIC WILL_FAIL)
new_test(context/no_properties.cpp STATIC WILL_FAIL)

new_test(context/basic_system.cpp)
new_test(context/system_resize.cpp)
new_test(context/zero_system.cpp)

# Iterator
new_test(iterator/range_based_assign.cpp)
new_test(iterator/range_based_for.cpp)
new_test(iterator/iterate_over.cpp)

# Properties
new_test(properties/any_same.cpp STATIC)
new_test(properties/not_any_same.cpp STATIC)
new_test(properties/any_duplicates.cpp STATIC)
new_test(properties/not_any_duplicates.cpp STATIC)
new_test(properties/index_of_tag.cpp STATIC)
new_test(properties/index_when_duplicates.cpp STATIC)

# Refs
new_test(ref/ref_to.cpp)
new_test(ref/ref_assign.cpp)

# Adaptor
new_test(adapt/adapt_struct.cpp)
new_test(adapt/adaptive_subscript.cpp)
