set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "Debug")

set(PROJECTNAME "TurnBasedGame")
set(EXECUTABLE_NAME "Game")

project(TurnBasedGame)

set(SRC src/main.cpp)

add_executable(${EXECUTABLE_NAME} ${SRC})
