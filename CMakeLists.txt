cmake_minimum_required(VERSION 3.28)
project(GroupingProblem)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

option(ENABLE_VISUALIZATION "Enable visualization - OpenCV required" OFF)
configure_file(config.h.in config.h)

# G-TEST
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.16.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

if(ENABLE_VISUALIZATION)
  # OPEN-CV
  find_package( OpenCV REQUIRED )
  include_directories( ${OpenCV_INCLUDE_DIRS} )
endif()

# FLATBUFFERS v25.2.10
FetchContent_Declare(
    flatbuffers
    GIT_REPOSITORY https://github.com/google/flatbuffers.git
    GIT_TAG v25.2.10
)
FetchContent_MakeAvailable(flatbuffers)

add_subdirectory(app)
add_subdirectory(src)
add_subdirectory(tests)

