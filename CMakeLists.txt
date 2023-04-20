cmake_minimum_required(VERSION 3.10)
project(antiterror_security VERSION 0.0.1)
set(CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCv_INCLUDE_DIRS})

set(SOURCES
    src/utils.cpp
    main.cpp
    src/preprocessing/RGB/preprocessing.cpp
    src/preprocessing/grayscale/preprocessing.cpp
    src/utils/utils.cpp
    src/filters/filters.cpp
)

set(HEADERS
    src/utils.h
    include/preprocessing/RGB/preprocessing.h
    include/preprocessing/grayscale/preprocessing.h
    include/utils/utils.h
    include/filters/filters.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

enable_testing()
add_subdirectory(tests)