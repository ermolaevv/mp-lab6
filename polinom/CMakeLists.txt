set(nameBaseProj polinom)
set(test "${nameBaseProj}_test")

set_property(GLOBAL PROPERTY INCLUDE_DIR ${INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)
add_subdirectory(test)
