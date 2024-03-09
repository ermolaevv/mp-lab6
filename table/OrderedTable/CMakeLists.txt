set(nameBaseProj OrderedTable)
set(test "${nameBaseProj}_test")


include_directories("../VectorTable/include")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)
add_subdirectory(test)
