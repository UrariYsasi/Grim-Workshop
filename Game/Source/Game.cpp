#include "PCH.hpp"
#include "Game.hpp"

Game::Game()
{

}

bool Game::Initialize()
{
    if (!m_engine.Initialize())
    {
        std::cout << "Engine initialization failed!" << std::endl;

        return false;
    }

    m_engine->SubscribeUpdate(&Game::Update);
    m_engine->AddRenderSubscription(&Game::Render);

    std::cout << "Game initialized." << std::endl;

    return true;
}

void Game::Terminate()
{
    m_engine.Terminate();
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