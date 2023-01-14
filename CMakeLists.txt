cmake_minimum_required(VERSION 3.13.0)
project(cpp_algo VERSION 0.0 LANGUAGES C CXX)

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
  set(CMAKE_C_STANDARD_REQUIRED OFF)
  set(CMAKE_C_EXTENSIONS OFF)
endif(NOT CMAKE_C_STANDARD)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif(NOT CMAKE_CXX_STANDARD)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # Disable C++ exceptions.
  string(REGEX REPLACE "/EH[a-z]+" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHs-c-")
  add_definitions(-D_HAS_EXCEPTIONS=0)

  # Disable RTTI.
  string(REGEX REPLACE "/GR" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR-")
else(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # Enable strict prototype warnings for C code in clang and gcc.
  if(NOT CMAKE_C_FLAGS MATCHES "-Wstrict-prototypes")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wstrict-prototypes")
  endif(NOT CMAKE_C_FLAGS MATCHES "-Wstrict-prototypes")

  # Disable C++ exceptions.
#  string(REGEX REPLACE "-fexceptions" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")

  # Disable RTTI.
  string(REGEX REPLACE "-frtti" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-Wthread-safety HAVE_CLANG_THREAD_SAFETY)

# Used by googletest.
check_cxx_compiler_flag(-Wno-missing-field-initializers
                        CPP_ALGO_HAVE_NO_MISSING_FIELD_INITIALIZERS)

if(BUILD_SHARED_LIBS)
    # Only export LEVELDB_EXPORT symbols from the shared library.
    add_compile_options(-fvisibility=hidden)
endif(BUILD_SHARED_LIBS)

enable_testing()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(install_gtest OFF)
set(install_gmock OFF)
set(build_gmock ON)
add_subdirectory("third/googletest")

# GoogleTest triggers a missing field initializers warning.
if(CPP_ALGO_HAVE_NO_MISSING_FIELD_INITIALIZERS)
  set_property(TARGET gtest
      APPEND PROPERTY COMPILE_OPTIONS -Wno-missing-field-initializers)
  set_property(TARGET gmock
      APPEND PROPERTY COMPILE_OPTIONS -Wno-missing-field-initializers)
endif(CPP_ALGO_HAVE_NO_MISSING_FIELD_INITIALIZERS)

include_directories(common)

add_executable(cpp_algo "")

FILE(GLOB COMMON ${CMAKE_CURRENT_SOURCE_DIR}/common/*)
FILE(GLOB SORT ${CMAKE_CURRENT_SOURCE_DIR}/sort/*)
FILE(GLOB LINKLIST ${CMAKE_CURRENT_SOURCE_DIR}/linklist/*)
FILE(GLOB SEARCH ${CMAKE_CURRENT_SOURCE_DIR}/search/*)
FILE(GLOB BIT ${CMAKE_CURRENT_SOURCE_DIR}/bit/*)
FILE(GLOB QUEUE ${CMAKE_CURRENT_SOURCE_DIR}/queue/*)
FILE(GLOB STACK ${CMAKE_CURRENT_SOURCE_DIR}/stack/*)
FILE(GLOB RECURSIVE ${CMAKE_CURRENT_SOURCE_DIR}/recursive/*)
FILE(GLOB HEAP ${CMAKE_CURRENT_SOURCE_DIR}/heap/*)
FILE(GLOB PRACTISE ${CMAKE_CURRENT_SOURCE_DIR}/practise/*)
FILE(GLOB TREE ${CMAKE_CURRENT_SOURCE_DIR}/tree/*)
FILE(GLOB LEETCODE ${CMAKE_CURRENT_SOURCE_DIR}/leetcode/*)

target_sources(cpp_algo
  PUBLIC
  ${COMMON}
  ${SORT}
  ${LINKLIST}
  ${SEARCH}
  ${BIT}
  ${QUEUE}
  ${STACK}
  ${RECURSIVE}
  ${HEAP}
  ${PRACTISE}
  ${TREE}
  ${LEETCODE}
  main.cc
)  
target_link_libraries(cpp_algo gmock gtest gtest_main)


