#include "PCH.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "../../Game/Game.hpp"

namespace grim
{

namespace graphics
{

Renderer::Renderer(Game* game, const grim::graphics::Window* window) :
    m_game(game)
{
    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set default clear color
    SetClearColor(grim::graphics::Color(0.2f, 0.2f, 0.2f));
}

Renderer::~Renderer()
{
}

void Renderer::SetClearColor(const grim::graphics::Color& color)
{
    glClearColor((GLfloat)color.r, (GLfloat)color.g, (GLfloat)color.b, (GLfloat)color.a);
}

void Renderer::SetActiveCamera(graphics::Camera* camera)
{
    m_activeCamera = camera;
}

graphics::Camera* Renderer::GetActiveCamera()
{
    return m_activeCamera;
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RenderTexture(const std::string& id, const int& x, const int& y, const int& width, const int& height)
{
    // DEPRECATED

    /*
    SDL_Texture* texture = m_game->GetTexture(id);
    if (texture == nullptr)
    {
        Debug::LogError("Texture %s can't be rendered, as it does not exist!", id.c_str());
        return;
    }

    SDL_Rect srcRect = { 0, 0, width, height };
    SDL_Rect destRect = { x - (int)m_activeCamera->GetPosition().x, y - (int)m_activeCamera->GetPosition().y, 32, 64 };

    SDL_RenderCopyEx(m_SDLRenderer, texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
    */
}

void Renderer::RenderSprite(const std::string& id, const int& col, const int& row, const int& x, const int& y, const int& width, const int& height)
{
    // DEPRECATED

    /*
    SDL_Texture* texture = m_game->GetTexture(id);
    if (texture == nullptr)
    {
        Debug::LogError("Spritesheet %s can't be rendered, as it does not exist!", id.c_str());
        return;
    }

    SDL_Rect srcRect = { col * 32, row * 32, width, height };
    SDL_Rect destRect = { x - (int)m_activeCamera->GetPosition().x, y - (int)m_activeCamera->GetPosition().y, width, height };

    SDL_RenderCopyEx(m_SDLRenderer, texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
    */
}

void Renderer::RenderText(const std::string& id, const int& x, const int& y, const std::string& text, const SDL_Color& color)
{
    // DEPRECATED

    //TTF_Font* font = m_game->GetFont(id);
    //if (font == nullptr)
    //{
    //    Debug::LogError("Font %s can't be rendered, as it does not exist!", id.c_str());
    //    return;
    //}

    //SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    //if (surface == nullptr)
    //{
    //    Debug::LogError("Failed to render font %s to surface! SDL_ttf error: %s", id.c_str(), TTF_GetError());
    //}

    //SDL_Texture* texture = SDL_CreateTextureFromSurface(m_SDLRenderer, surface);
    //int width;
    //int height;
    //SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    //if (texture == nullptr)
    //{
    //    Debug::LogError("Failed to create font texture from surface! SDL error: ", SDL_GetError());
    //}

    //SDL_Rect srcRect = { 0, 0, width, height };
    //SDL_Rect destRect = { x - (int)m_activeCamera->GetPosition().x, y - (int)m_activeCamera->GetPosition().y, width, height };

    //SDL_RenderCopyEx(m_SDLRenderer, texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);

    //SDL_FreeSurface(surface);
    //SDL_DestroyTexture(texture);
}

void Renderer::RenderOutlineRect(const grim::graphics::Rect& rect, const SDL_Color& color)
{
    // DEPRECATED

    //(color);
    //Vector2D pos(rect.x, rect.y);
    //Vector2D screenPos = m_activeCamera->ConvertToScreen(pos);

    //SDL_Rect r = {(int)screenPos.x, (int)screenPos.y, (int)rect.width, (int)rect.height};
    //SDL_RenderDrawRect(m_SDLRenderer, &r);
}

void Renderer::RenderFillRect(const grim::graphics::Rect& rect, const SDL_Color& color)
{
    // DEPRECATED

    //SetDrawColor(color);
    //Vector2D pos(rect.x, rect.y);
    //Vector2D screenPos = m_activeCamera->ConvertToScreen(pos);

    //SDL_Rect r = { (int)screenPos.x, (int)screenPos.y, (int)rect.width, (int)rect.height };
    //SDL_RenderFillRect(m_SDLRenderer, &r);
}

}

}