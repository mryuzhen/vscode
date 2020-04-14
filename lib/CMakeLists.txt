#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#MESSAGE(STATUS "${CMAKE_INSTALL_PREFIX}")

set(LIBHELLO_SOURCE hello.cpp)
add_library(hello_static STATIC ${LIBHELLO_SOURCE})
#add_library(hello SHARED ${LIBHELLO_SOURCE})
set_target_properties(hello_static PROPERTIES OUTPUT_NAME "hello")
#set_target_properties(hello PROPERTIES CLEAN_DIRECT_OUTPUT 1)
#set_target_properties(hello PROPERTIES VERSION 0.1 SOVERSION 0.1) #linux

