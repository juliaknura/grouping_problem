add_library(visualization
    DrawProblem.cpp
)

target_include_directories(visualization PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
)

target_link_libraries(
    visualization
    problemEntities
    ${OpenCV_LIBS}
)

add_executable(visualize_app
    visualize.cpp
)

target_link_libraries(
    visualize_app
    problemEntities
    visualization
)