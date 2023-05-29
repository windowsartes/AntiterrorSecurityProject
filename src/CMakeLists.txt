add_library(
    src STATIC
    filters/filters.cpp
    preprocessing/preprocessing.cpp
    utils/utils.cpp
    noise_borders/noise_borders.cpp
    detection/detection.cpp
    working_surface/working_surface.cpp
)

target_include_directories(src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(src ${OpenCV_LIBS})