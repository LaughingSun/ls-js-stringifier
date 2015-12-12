
set(SEP "/")
set(INCLUDE_SUBDIR_NAME "include")
set(SOURCE_SUBDIR_NAME "src")

set(SAMPLES_DIR ${CMAKE_BINARY_DIR}${SEP}samples)
set(RUNTIME_DIR ${CMAKE_BINARY_DIR}${SEP}bin)
set(RUNTIME_LIBRARY_DIR ${RUNTIME_DIR}${SEP}lib)

message(STATUS "SAMPLES_DIR=${SAMPLES_DIR}")

file(GLOB TMP "${SAMPLES_DIR}${SEP}*${SEP}lib*.cpp")
string(REGEX REPLACE "${SEP}+" "${SEP}" SAMPLE_LIB_SOURCES "${TMP}")

file(GLOB TMP "${SAMPLES_DIR}${SEP}*${SEP}*.cpp")
string(REGEX REPLACE "${SAMPLES_DIR}(${SEP}+[a-z0-9-]+)*${SEP}+lib[a-z0-9-]+\\.cpp[:;]?" "" TMP "${TMP}")
string(REGEX REPLACE "${SEP}+" "${SEP}" SAMPLE_SOURCES "${TMP}")

cmake_minimum_required(VERSION 2.8.9)
project(samples)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${RUNTIME_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${RUNTIME_LIBRARY_DIR}")

set(CMAKE_C_COMPILER_ID "GNU")
set(CMAKE_CXX_COMPILER_ID "GNU")
set(CMAKE_COMPILER_IS_GNUCXX TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


#
# loop foreach lib build target
#

message(STATUS "SAMPLE_LIB_SOURCES=${SAMPLE_LIB_SOURCES}")
set(TARGET_LIBRARIES "")
foreach(MAIN_SRC IN LISTS SAMPLE_LIB_SOURCES)
  
  message(STATUS "")
  
  string(LENGTH "${SAMPLES_DIR}" SAMPLES_DIR_LENGTH)
  string(REGEX REPLACE "\\.cpp" "" END_DIR "${MAIN_SRC}")
  string(LENGTH "${END_DIR}" END_DIR_LENGTH)
  set(TARGET_INCLUDE_PATHS "")
  set(TARGET_SOURCES "${MAIN_SRC}")
  while(NOT "${END_DIR_LENGTH}" LESS "${SAMPLES_DIR_LENGTH}")
    
    set(TMP "${END_DIR}${SEP}${INCLUDE_SUBDIR_NAME}")
    if (IS_DIRECTORY "${TMP}")
      list(APPEND TARGET_INCLUDE_PATHS "${TMP}")
    endif (IS_DIRECTORY "${TMP}")
    
    set(TMP "${END_DIR}${SEP}${SOURCE_SUBDIR_NAME}")
    if (IS_DIRECTORY "${TMP}")
      file(GLOB TMP "${TMP}/*.cpp")
      list(APPEND TARGET_INCLUDE_PATHS "${TMP}")
    endif (IS_DIRECTORY "${TMP}")
    
    string(REGEX REPLACE "${SEP}[a-z0-9-]+$" "" END_DIR "${END_DIR}")
    string(LENGTH "${END_DIR}" END_DIR_LENGTH)
  endwhile(NOT "${END_DIR_LENGTH}" LESS "${SAMPLES_DIR_LENGTH}")

  string(REGEX REPLACE "${SAMPLES_DIR}${SEP}+(([a-z0-9-]+${SEP}+)*)lib([a-z0-9-]+)\\.cpp" "\\1\\3" TMP "${MAIN_SRC}")
  string(REGEX REPLACE "${SEP}" "-" TMP "${TMP}")
  set(TARGET "${TMP}")
  list(APPEND TARGET_LIBRARIES "${TARGET}")
  
  message(STATUS "TARGET=${TARGET}")
  message(STATUS "TARGET_INCLUDE_PATHS=${TARGET_INCLUDE_PATHS}")
  message(STATUS "TARGET_SOURCES=${TARGET_SOURCES}")

  add_library("${TARGET}" SHARED "${TARGET_SOURCES}")
  target_include_directories("${TARGET}" PUBLIC "${TARGET_INCLUDE_PATHS}")

endforeach(MAIN_SRC)

message(STATUS "")
message(STATUS "TARGET_LIBRARIES=${TARGET_LIBRARIES}")

#
# loop foreach build target
#

message(STATUS "SAMPLE_SOURCES=${SAMPLE_SOURCES}")
foreach(MAIN_SRC IN LISTS SAMPLE_SOURCES)
  
  message(STATUS "")
  
  string(LENGTH "${SAMPLES_DIR}" SAMPLES_DIR_LENGTH)
  string(REGEX REPLACE "\\.cpp" "" END_DIR "${MAIN_SRC}")
  string(LENGTH "${END_DIR}" END_DIR_LENGTH)
  set(TARGET_INCLUDE_PATHS "")
  set(TARGET_SOURCES "${MAIN_SRC}")
  while(NOT "${END_DIR_LENGTH}" LESS "${SAMPLES_DIR_LENGTH}")
    
    set(TMP "${END_DIR}${SEP}${INCLUDE_SUBDIR_NAME}")
    if (IS_DIRECTORY "${TMP}")
      list(APPEND TARGET_INCLUDE_PATHS "${TMP}")
    endif (IS_DIRECTORY "${TMP}")
    
    set(TMP "${END_DIR}${SEP}${SOURCE_SUBDIR_NAME}")
    if (IS_DIRECTORY "${TMP}")
      file(GLOB TMP "${TMP}/*.cpp")
      list(APPEND TARGET_INCLUDE_PATHS "${TMP}")
    endif (IS_DIRECTORY "${TMP}")
    
    string(REGEX REPLACE "${SEP}[a-z0-9-]+$" "" END_DIR "${END_DIR}")
    string(LENGTH "${END_DIR}" END_DIR_LENGTH)
  endwhile(NOT "${END_DIR_LENGTH}" LESS "${SAMPLES_DIR_LENGTH}")

  string(REGEX REPLACE "${SAMPLES_DIR}${SEP}+(([a-z0-9-]+${SEP}+)*)([a-z0-9-]+)\\.cpp" "\\1\\3" TMP "${MAIN_SRC}")
  string(REGEX REPLACE "${SEP}" "-" TMP "${TMP}")
  set(TARGET "${TMP}")
  
  message(STATUS "TARGET=${TARGET}")
  message(STATUS "TARGET_INCLUDE_PATHS=${TARGET_INCLUDE_PATHS}")
  message(STATUS "TARGET_SOURCES=${TARGET_SOURCES}")

  add_executable("${TARGET}" "${TARGET_SOURCES}")
  target_link_libraries("${TARGET}" LINK_PUBLIC "${TARGET_LIBRARIES}" )
  target_include_directories("${TARGET}" PUBLIC "${TARGET_INCLUDE_PATHS}")

endforeach(MAIN_SRC)

message(STATUS "")


