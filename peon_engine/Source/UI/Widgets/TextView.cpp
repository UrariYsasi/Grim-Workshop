#include "PCH.hpp"
#include "TextView.hpp"
#include "../../Graphics/RenderCommand.hpp"
#include "../../Graphics/Mesh.hpp"
#include "../../Graphics/Texture.hpp"

namespace grim
{

namespace ui
{

TextView::TextView(Engine* const engine, const std::string& text, TTF_Font* font, const grim::graphics::Material& material) :
    Widget(engine),
    m_text(text),
    m_font(font),
    m_mesh(),
    m_material(material),
    m_texture(false),
    m_isInvalid(true)
{
    Construct();
}

TextView::~TextView()
{
}

void TextView::Update(float deltaTime)
{
    Widget::Update(deltaTime);

    if (m_isInvalid)
    {
        Construct();
    }
}

void TextView::Render()
{
    Widget::Render();

    glm::vec3 renderPosition(m_position.x, m_position.y, m_zLayer);

    if (m_parent != nullptr)
    {
        glm::vec2 parentPosition = m_parent->GetPosition();
        renderPosition.x += parentPosition.x;
        renderPosition.y += parentPosition.y;
    }

    glm::vec3 renderRotation(0.0f, 0.0f, m_rotation);
    glm::vec3 renderScale(m_scale.x, m_scale.y, 1.0f);

    grim::graphics::Transform transform(renderPosition, renderRotation, renderScale);
    grim::graphics::RenderCommand command(&m_mesh, &m_material, transform, 1);
    m_engine->GetRenderer()->Submit(command);
}

void TextView::Construct()
{
    m_mesh.ClearData();

    SDL_Surface* surface = TTF_RenderText_Blended(m_font, m_text.c_str(), SDL_Color{0, 0, 0, 255});
    m_texture.SetData(surface->pixels, GL_RGBA, GL_BGRA, surface->w, surface->h);
    SDL_FreeSurface(surface);

    m_material.texture = &m_texture;

    grim::graphics::Color color(1.0f, 1.0f, 1.0f);
    grim::graphics::Vertex topLeft(glm::vec3(0.0f, 0.0f, 0.0f), color, glm::vec2(0.0f, 0.0f));
    grim::graphics::Vertex topRight(glm::vec3(surface->w, 0.0f, 0.0f), color, glm::vec2(1.0f, 0.0f));
    grim::graphics::Vertex bottomLeft(glm::vec3(0.0f, surface->h, 0.0f), color, glm::vec2(0.0f, 1.0f));
    grim::graphics::Vertex bottomRight(glm::vec3(surface->w, surface->h, 0.0f), color, glm::vec2(1.0f, 1.0f));

    m_mesh.AddVertex(topLeft);
    m_mesh.AddVertex(topRight);
    m_mesh.AddVertex(bottomLeft);
    m_mesh.AddVertex(bottomRight);

    m_mesh.AddIndex(0);
    m_mesh.AddIndex(1);
    m_mesh.AddIndex(2);
    m_mesh.AddIndex(2);
    m_mesh.AddIndex(3);
    m_mesh.AddIndex(1);

    m_isInvalid = false;
    m_width = surface->w;
    m_height = surface->h;
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