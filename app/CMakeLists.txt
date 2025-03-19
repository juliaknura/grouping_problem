add_executable(groupingProblem
    groupingProblem.cpp
)

target_link_libraries(groupingProblem
    problemEntities
    reader
)

if(ENABLE_VISUALIZATION)
target_link_libraries(groupingProblem
    visualization
)
endif()