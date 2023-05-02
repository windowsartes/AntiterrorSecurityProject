CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(tests)

find_package(GTest REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${OpenCv_INCLUDE_DIRS})

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/filters/test_filters.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/noise_borders/test_noise_borders.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/filters/filters.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/noise_borders/noise_borders.cpp    
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/filters/filters.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/noise_borders/noise_borders.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(tests Threads::Threads ${GTEST_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})