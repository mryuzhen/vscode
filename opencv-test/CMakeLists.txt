SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(OpenCV_DIR "D:/opencv-vc1415/build")
find_package(OpenCV REQUIRED)

MESSAGE(STATUS "Version : ${OpenCV_VERSION}")
MESSAGE(STATUS "library : ${OpenCV_LIBS}")
MESSAGE(STATUS "Include Path : ${OpenCV_INCLUDE_DIRS}")

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    )

link_libraries(${OpenCV_LIBS})

set(SOURCE opencv-test.cpp)
add_executable(main ${SOURCE})

target_link_libraries(main ${OpenCV_LIBS})

