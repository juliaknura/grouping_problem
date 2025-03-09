add_executable(main
    main.cpp)

add_library(problemEntities 
    problemEntities/GroupingProblemInstance.cpp)

target_include_directories(problemEntities PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
)

add_library(visualization
    visualization/DrawProblem.cpp
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