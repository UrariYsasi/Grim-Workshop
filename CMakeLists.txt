cmake_minimum_required(VERSION 3.3)
project(peon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Peon/Source/Engine/Input.cpp
    Peon/Source/Engine/Input.hpp
    Peon/Source/Engine/Renderer.cpp
    Peon/Source/Engine/Renderer.hpp
    Peon/Source/Engine/Timer.cpp
    Peon/Source/Engine/Timer.hpp
    Peon/Source/Engine/Vector2D.cpp
    Peon/Source/Engine/Vector2D.hpp
    Peon/Source/Engine/Window.cpp
    Peon/Source/Engine/Window.hpp
    Peon/Source/Game/Entity/Entity.cpp
    Peon/Source/Game/Entity/Entity.hpp
    Peon/Source/Game/Entity/Monster.cpp
    Peon/Source/Game/Entity/Monster.hpp
    Peon/Source/Game/Entity/Peon.cpp
    Peon/Source/Game/Entity/Peon.hpp
    Peon/Source/Game/Entity/Prop.cpp
    Peon/Source/Game/Entity/Prop.hpp
    Peon/Source/Game/Entity/Resource.cpp
    Peon/Source/Game/Entity/Resource.hpp
    Peon/Source/Game/Entity/Stockpile.cpp
    Peon/Source/Game/Entity/Stockpile.hpp
    Peon/Source/Game/Entity/Tree.cpp
    Peon/Source/Game/Entity/Tree.hpp
    Peon/Source/Game/Game.cpp
    Peon/Source/Game/Game.hpp
    Peon/Source/Main.cpp
    Peon/Source/PCH.hpp)

add_executable(peon ${SOURCE_FILES})