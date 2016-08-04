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
        LOG_ERROR() << "Engine initialization failed!";
        return false;
    }

    LOG() << "Game initialized.";
    return true;
}

void Game::Terminate()
{
    LOG() << "Game terminated.";
}

void Game::Run()
{
    m_engine.Run();
}

void Game::Update()
{
}

void Game::Render()
{
}