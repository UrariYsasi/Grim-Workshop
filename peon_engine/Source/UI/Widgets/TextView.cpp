#include "PCH.hpp"
#include "TextView.hpp"
#include "../../Graphics/Mesh.hpp"
#include "../../Graphics/Texture.hpp"

namespace grim
{

namespace ui
{

TextView::TextView(const std::string& text, TTF_Font* font, grim::graphics::ShaderProgram* shaderProgram) :
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

TextView::~TextView()
{
}

void TextView::Update(float deltaTime)
{
    if (m_isInvalid)
    {
        Construct();
    }
}

void TextView::Render()
{
    glm::vec3 renderPosition(m_position.x, m_position.y, 0.0f);

    if (m_parent != nullptr)
    {
        glm::vec2 parentPosition = m_parent->GetPosition();
        renderPosition.x += parentPosition.x;
        renderPosition.y += parentPosition.y;
    }

    glm::vec3 renderRotation(m_rotation);
    glm::vec3 renderScale(1.0f, 1.0f, 1.0f);
    m_mesh->Render(renderPosition, renderRotation, renderScale);
}

void TextView::Construct()
{
    SDL_Surface* surface = TTF_RenderText_Blended(m_font, m_text.c_str(), SDL_Color{0, 0, 0, 255});
    m_texture->SetData(surface->pixels, GL_RGBA, GL_BGRA, surface->w, surface->h);
    SDL_FreeSurface(surface);

    GLfloat vertices[] = {
        // Top left
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        // Top right
        0.0f + surface->w, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        // Bottom left
        0.0f, 0.0f + surface->h, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        // Bottom right
        0.0f + surface->w, 0.0f + surface->h, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
    };

    m_mesh->UploadVertexData(vertices, sizeof(vertices));

    m_isInvalid = false;
}

void TextView::SetText(const std::string& text)
{
    m_text = text;
    m_isInvalid = true;
}

std::string& TextView::GetText()
{
    return m_text;
}

}

}