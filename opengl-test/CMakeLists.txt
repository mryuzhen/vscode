set(CXX_STANDARD 11)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(SUMMARY_SOURCE_DIR D:/opengl)
set(GLFW_INCLUDE_DIR ${SUMMARY_SOURCE_DIR}/include/)
set(GLFW_LIBRARY_DIR ${SUMMARY_SOURCE_DIR}/lib-vc2019/debug)
set(GLAD_SRC "D:/opengl/glad")
set(class_src ../src)

include_directories(. ${class_src} ${GLFW_INCLUDE_DIR})
link_directories(${GLFW_LIBRARY_DIR})
link_libraries(glfw3)
link_libraries(glfw3dll)

#set(SOURCE main.cpp ${GLAD_SRC}/glad.c)
set(SOURCE show-test.cpp ${class_src}/shader.cpp ${class_src}/shaderprogram.cpp ${GLAD_SRC}/glad.c)
add_executable(show-test ${SOURCE})

target_link_libraries(show-test glfw3)
target_link_libraries(show-test glfw3dll)


