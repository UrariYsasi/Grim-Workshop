#include "PCH.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "../Game/Game.hpp"

Renderer::Renderer(Game* game, const Window* window) :
    m_game(game)
{
    m_SDLRenderer = SDL_CreateRenderer(window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_SDLRenderer == nullptr)
    {
        std::cerr << "Renderer could not be created! SDL error: " << SDL_GetError() << std::endl;
    }

    SDL_SetRenderDrawBlendMode(m_SDLRenderer, SDL_BLENDMODE_BLEND);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_SDLRenderer);
}

void Renderer::SetDrawColor(const SDL_Color& drawColor)
{
    SDL_SetRenderDrawColor(m_SDLRenderer, drawColor.r, drawColor.g, drawColor.b, drawColor.a);
}

SDL_Renderer* Renderer::GetSDLRenderer() const
{
    return m_SDLRenderer;
}

void Renderer::SetActiveCamera(Camera* camera)
{
    m_activeCamera = camera;
}

Camera* Renderer::GetActiveCamera()
{
    return m_activeCamera;
}

void Renderer::Clear()
{
    SDL_RenderClear(m_SDLRenderer);
}

void Renderer::Present()
{
    SDL_RenderPresent(m_SDLRenderer);
}

void Renderer::RenderTexture(const std::string& id, const int& x, const int& y, const int& width, const int& height)
{
    SDL_Texture* texture = m_game->GetTexture(id);
    if (texture == nullptr)
    {
        Debug::LogError("Texture %s can't be rendered, as it does not exist!", id.c_str());
        return;
    }

    SDL_Rect srcRect = { 0, 0, 32, 32 };
    SDL_Rect destRect = { x - (int)m_activeCamera->GetPosition().x, y - (int)m_activeCamera->GetPosition().y, width, height };

    SDL_RenderCopyEx(m_SDLRenderer, texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void Renderer::RenderSprite(const std::string& id, const int& col, const int& row, const int& x, const int& y, const int& width, const int& height)
{
    SDL_Texture* texture = m_game->GetTexture(id);
    if (texture == nullptr)
    {
        Debug::LogError("Spritesheet %s can't be rendered, as it does not exist!", id.c_str());
        return;
    }

    SDL_Rect srcRect = { col * width, row * height, width, height };
    SDL_Rect destRect = { x - (int)m_activeCamera->GetPosition().x, y - (int)m_activeCamera->GetPosition().y, width, height };

    SDL_RenderCopyEx(m_SDLRenderer, texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void Renderer::RenderText(const std::string& id, const int& x, const int& y, const std::string& text, const SDL_Color& color)
{
    TTF_Font* font = m_game->GetFont(id);
    if (font == nullptr)
    {
        Debug::LogError("Font %s can't be rendered, as it does not exist!", id.c_str());
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr)
    {
        Debug::LogError("Failed to render font %s to surface! SDL_ttf error: %s", id.c_str(), TTF_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_SDLRenderer, surface);
    int width;
    int height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    if (texture == nullptr)
    {
        Debug::LogError("Failed to create font texture from surface! SDL error: ", SDL_GetError());
    }

    SDL_Rect srcRect = { 0, 0, width, height };
    SDL_Rect destRect = { x - (int)m_activeCamera->GetPosition().x, y - (int)m_activeCamera->GetPosition().y, width, height };

    SDL_RenderCopyEx(m_SDLRenderer, texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Renderer::RenderOutlineRect(const Rectangle& rect, const SDL_Color& color)
{
    SetDrawColor(color);
    Vector2D pos(rect.x, rect.y);
    Vector2D screenPos = m_activeCamera->ConvertToScreen(pos);

    SDL_Rect r = {(int)screenPos.x, (int)screenPos.y, (int)rect.width, (int)rect.height};
    SDL_RenderDrawRect(m_SDLRenderer, &r);
}

void Renderer::RenderFillRect(const Rectangle& rect, const SDL_Color& color)
{
    SetDrawColor(color);
    Vector2D pos(rect.x, rect.y);
    Vector2D screenPos = m_activeCamera->ConvertToScreen(pos);

    SDL_Rect r = { (int)screenPos.x, (int)screenPos.y, (int)rect.width, (int)rect.height };
    SDL_RenderFillRect(m_SDLRenderer, &r);
}