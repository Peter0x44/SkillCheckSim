cmake_minimum_required(VERSION 3.0)
project(SkillCheckSimulator CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games
set(OPENGL_VERSION "1.1" CACHE STRING "" FORCE)

add_subdirectory(libs/raylib)

#add_compile_options(-Wall -Wextra -pedantic)

add_executable(SkillCheckSimulator
	src/skillcheck.cpp
)

target_link_libraries(SkillCheckSimulator PRIVATE raylib)
