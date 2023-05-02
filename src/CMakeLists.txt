add_library(
    src STATIC
    filters/filters.cpp
    preprocessing/grayscale/preprocessing.cpp
    preprocessing/RGB/preprocessing.cpp
    utils/utils.cpp
)

target_include_directories(src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(src ${OpenCV_LIBS})