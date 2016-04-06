#include "PCH.hpp"
#include "Text.hpp"
#include "../../Graphics/Mesh.hpp"
#include "../../Graphics/Texture.hpp"

namespace grim
{

namespace ui
{

Text::Text(const std::string& text, TTF_Font* font, grim::graphics::ShaderProgram* shaderProgram) :
    m_text(text),
    m_font(font),
    m_mesh(nullptr),
    m_texture(nullptr),
    m_isInvalid(true)
{
    m_texture = std::make_unique<grim::graphics::Texture>("doosk.png");
    m_mesh = std::make_unique <grim::graphics::Mesh>(shaderProgram, m_texture.get());

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 1
    };

    m_mesh->UploadElementData(elements, sizeof(elements));
    m_mesh->SetRenderMode(GL_TRIANGLES);
}

Text::~Text()
{
}

void Text::Update(float deltaTime)
{
    if (m_isInvalid)
    {
        Construct();
    }
}

void Text::Render()
{
    m_mesh->Render(glm::vec3(0.0), glm::vec3(0.0), glm::vec3(1.0f, 1.0f, 0.0f));
}

void Text::Construct()
{
    SDL_Surface* surface = TTF_RenderText_Blended(m_font, m_text.c_str(), SDL_Color{0, 0, 0, 255});
    m_texture->SetData(surface->pixels, GL_RGBA, GL_BGRA, surface->w, surface->h);
    SDL_FreeSurface(surface);

    GLfloat vertices[] = {
        // Top left
        64.0f, 64.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        // Top right
        64.0f + surface->w, 64.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        // Bottom left
        64.0f, 64.0f + surface->h, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        // Bottom right
        64.0f + surface->w, 64.0f + surface->h, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
    };

    m_mesh->UploadVertexData(vertices, sizeof(vertices));

    m_isInvalid = false;
}

void Text::SetText(const std::string& text)
{
    m_text = text;
    m_isInvalid = true;
}

std::string& Text::GetText()
{
    return m_text;
}

}

}