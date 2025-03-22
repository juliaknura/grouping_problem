add_executable(main
    main.cpp)

add_library(problemEntities 
    problemEntities/GroupingProblemInstance.cpp)

target_include_directories(problemEntities PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
)

add_library(reader
    reader/ReaderUtils.cpp
)

target_link_libraries(reader 
    problemEntities
    flatbuffers
)

target_include_directories(reader PUBLIC 
    ${CMAKE_BINARY_DIR}
)

if(ENABLE_VISUALIZATION)
  add_subdirectory(visualization)
endif()

add_library(solver
    solver/geneticAlgo/GeneticAlgorithmSolver.cpp
)

target_link_libraries(solver
    problemEntities
)