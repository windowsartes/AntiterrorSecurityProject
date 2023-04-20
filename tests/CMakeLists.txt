CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(tests)

find_package(GTest REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OpenCv_INCLUDE_DIRS})

add_executable(tests filters/test_filters.cpp noise_borders/test_noise_borders.cpp ../src/filters/filters.cpp ../src/noise_borders/noise_borders.cpp)
target_link_libraries(tests Threads::Threads ${GTEST_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})