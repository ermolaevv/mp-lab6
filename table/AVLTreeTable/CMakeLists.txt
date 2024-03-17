set(nameBaseProj AVLTreeTable)
set(test "${nameBaseProj}_test")

include_directories("../TreeTable/include")
set(include_dir ${include_dir} ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)
add_subdirectory(test)
