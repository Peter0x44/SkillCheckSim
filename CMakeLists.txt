cmake_minimum_required(VERSION 3.20)
project(SkillCheckSimulator CXX)

# Setting parameters for raylib
set(CUSTOMIZE_BUILD ON)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

if (NOT EMSCRIPTEN)
	set(OPENGL_VERSION "1.1" CACHE STRING "" FORCE)
else ()
	set(PLATFORM "Web" CACHE STRING "" FORCE)
endif ()

add_subdirectory(libs/raylib)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	add_compile_options(-Wall -Wextra -pedantic -Wno-missing-field-initializers -Wdouble-promotion)
endif ()


if (EMSCRIPTEN)
	add_link_options(-sUSE_GLFW=3 --preload-file "${CMAKE_CURRENT_LIST_DIR}/assets@assets")
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

add_executable(SkillCheckSimulator
	src/skillcheck.cpp
	src/skillcheck.h
	src/skillcheck_behavior.cpp
	src/skillcheck_behavior.h
	src/gamestates.cpp
	src/gamestates.h
	src/main.cpp
	src/globals.h
	src/achievements.cpp
	src/achievements.h
	src/help.cpp
	src/help.h
	src/settings.cpp
	src/settings.h
)

target_compile_features(SkillCheckSimulator PRIVATE cxx_std_11)
target_include_directories(SkillCheckSimulator PRIVATE libs/raygui/src)

target_link_libraries(SkillCheckSimulator PRIVATE raylib)
