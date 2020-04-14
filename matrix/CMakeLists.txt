set(CXX_STANDARD 11)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(SUMMARY_SOURCE_DIR D:/opengl)
set(GLFW_INCLUDE_DIR ${SUMMARY_SOURCE_DIR}/include/)
set(GLFW_LIBRARY_DIR ${SUMMARY_SOURCE_DIR}/lib-vc2019/debug)
set(GLAD_SRC "D:/opengl/glad")
set(user_inc ../src)
#set(stb_SRC ${SUMMARY_SOURCE_DIR}/include/stb)

include_directories(. ${user_inc} ${GLFW_INCLUDE_DIR}) #${stb_SRC})
link_directories(${GLFW_LIBRARY_DIR})
link_libraries(glfw3)
link_libraries(glfw3dll)

#set(SOURCE main.cpp ${GLAD_SRC}/glad.c)
set(SOURCE matrix.cpp)
add_executable(matrix ${SOURCE})

target_link_libraries(matrix glfw3)
target_link_libraries(matrix glfw3dll)


