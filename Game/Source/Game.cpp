/*
    Game.cpp
    Peon Game

    Declan Hopkins
    8/1/2016
*/

#include "PCH.hpp"
#include "Game.hpp"

Game::Game() :
    m_engine(this)
{
}

bool Game::Initialize()
{
    if (!m_engine.Initialize())
    {
        std::cout << "Engine initialization failed!" << std::endl;
        return false;
    }

    std::cout << "Game initialized." << std::endl;
    return true;
}

void Game::Terminate()
{
    std::cout << "Game terminated." << std::endl;
}

void Game::Run()
{
    m_engine.Run();
}

void Game::Update()
{
    //std::cout << "Game Update()" << std::endl;
}

void Game::Render()
{
    //std::cout << "Game Render()" << std::endl;
}