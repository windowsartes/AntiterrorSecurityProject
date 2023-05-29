CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(tests)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/test_filters.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/noise_borders/test_noise_borders.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/test_utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/detection/test_detection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/working_surface/test_working_surface.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(GTest REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${OpenCv_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

target_link_libraries(tests src)
target_link_libraries(tests Threads::Threads ${GTEST_LIBRARIES})