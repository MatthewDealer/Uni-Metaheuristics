cmake_minimum_required(VERSION 3.0.0)
project(cVRP VERSION 0.1.0)
cmake_policy(SET CMP0074 NEW)

# include(CTest)
# enable_testing()

#profiling flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")


add_library(
  loader
  include/loader.hpp
  src/loader.cpp
)

add_library(
  problem
  include/problem.hpp
  src/problem.cpp
)

add_library(
  solution
  include/solution.hpp
  src/solution.cpp
)

add_library(
  solver
  include/solver.hpp
  src/solver.cpp
)

add_library(
  logger
  include/csvlogger.hpp
  src/csvlogger.cpp
)

add_library(
  researcher
  include/researcher.hpp
  src/researcher.cpp
)

find_package (Boost 1.55.0 REQUIRED)
if (Boost_FOUND)
  include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif ()

add_executable(cVRP main.cpp)

# Try to delete libs from cVRP. Just use researcher
target_link_libraries(cVRP PRIVATE loader)
target_link_libraries(cVRP PRIVATE problem)
target_link_libraries(cVRP PRIVATE solution)
target_link_libraries(cVRP PRIVATE solver)
target_link_libraries(cVRP PRIVATE logger)
target_link_libraries(cVRP PRIVATE researcher)
target_link_libraries(logger PRIVATE solver)
target_link_libraries(researcher PRIVATE loader)
target_link_libraries(researcher PRIVATE problem)
target_link_libraries(researcher PRIVATE solution)
target_link_libraries(researcher PRIVATE solver)
target_link_libraries(researcher PRIVATE logger)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
