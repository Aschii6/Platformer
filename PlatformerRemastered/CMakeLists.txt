cmake_minimum_required(VERSION 3.27)
project(Platformer)

set(CMAKE_CXX_STANDARD 17)

add_executable(Platformer main.cpp
        GameEngine.cpp
        GameEngine.h
        Assets.h
        Animation.h
        Components.h
        Entity.h
        EntityManager.h
        scenes/Scene.h
        scenes/SceneStartMenu.cpp
        scenes/SceneStartMenu.h
        scenes/ScenePlaying.cpp
        scenes/ScenePlaying.h
        scenes/SceneOptions.cpp
        scenes/SceneOptions.h
        scenes/SceneGameOver.cpp
        scenes/SceneGameOver.h)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_ROOT "C:/SFML")

set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML COMPONENTS graphics audio REQUIRED)

include_directories(C:/SFML)

target_link_libraries(Platformer sfml-graphics sfml-audio)