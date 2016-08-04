/*
    Game.cpp
    Peon Game

    Declan Hopkins
    8/1/2016
*/

#include "PCH.hpp"
#include "Game.hpp"

Game::Game() :
    m_engine(nullptr)
{
}

bool Game::Initialize()
{
    LOG() << "Game initializing...";

    m_engine = std::make_unique<grim::Engine>(this);
    if (!m_engine->Initialize())
    {
        LOG_ERROR() << "Engine initialization failed!";
        return false;
    }

    LOG() << "Game initialized.";
    return true;
}

void Game::Terminate()
{
    LOG() << "Game terminating...";

    m_engine->Terminate();

    LOG() << "Game terminated.";
}

void Game::Run()
{
    LOG() << "Running game...";

    m_engine->Run();
}

void Game::Update()
{
}

void Game::Render()
{
}