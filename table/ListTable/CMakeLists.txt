set(nameBaseProj ListTable)
set(test "${nameBaseProj}_test")


include_directories("../Table/include")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)
add_subdirectory(test)
