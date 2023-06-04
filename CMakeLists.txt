cmake_minimum_required(VERSION 3.10)
project(antiterror_security VERSION 1.0.0)
set(CXX_STANDARD 17)

add_executable(antiterror_security main.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCv_INCLUDE_DIRS})

target_link_libraries(antiterror_security
                             ${OpenCV_LIBS}
                             "-Wl,-z,stack-size=1000000"
                      )

add_subdirectory(src)

target_link_libraries(antiterror_security src)

enable_testing()
add_subdirectory(tests)