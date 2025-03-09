add_executable(main
    main.cpp)

add_library(problemEntities 
    problemEntities/GroupingProblemInstance.cpp)

target_include_directories(problemEntities PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR} 
)