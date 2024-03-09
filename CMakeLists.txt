cmake_minimum_required(VERSION 2.8...3.13)
set (CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME TableLab)
project(${PROJECT_NAME})

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest)
add_subdirectory(gtest)
add_subdirectory(polinom)
add_subdirectory(postfix)
add_subdirectory(table)

set(nameMain "Main")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:${nameMain}")

file(GLOB hdrs "interface/include/*.h*" "interface/src/*.h*")
file(GLOB srcs "*.cpp" "interface/src/*.cpp")
file(GLOB resx "interface/include/*.resx")

add_executable(${PROJECT_NAME} WIN32 ${srcs} ${hdrs} ${resx})
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DOTNET_REFERENCES "System;System.Data;System.Drawing;System.Windows.Forms;System.Xml"
    VS_GLOBAL_ROOTNAMESPACE ${PROJECT_NAME}
    COMMON_LANGUAGE_RUNTIME ""
    CMAKE_VS_TARGET_FRAMEWORK_VERSION "v4.7.2"
)
target_include_directories(${PROJECT_NAME} PRIVATE
    "interface/include"
    "polinom/include"
    "postfix/include"
    "postfix/stack/include"
    "table/OrderedTable/include"
    "table/Table/include"
    "table/VectorTable/include"
    "table/ListTable/include"
)
