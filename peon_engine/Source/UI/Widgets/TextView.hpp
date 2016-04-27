#pragma once
#include "Widget.hpp"

namespace grim
{

namespace graphics
{
    
class Mesh;
class Texture;

}

namespace ui
{

class TextView : public Widget
{
public:
    TextView(Engine* const engine, const std::string& text, TTF_Font* font, const grim::graphics::Material& material);
    ~TextView();

    virtual void Update(float deltaTime);
    virtual void Render();

    void SetText(const std::string& text);
    std::string& GetText();

private:
    void Construct();

private:
    std::string m_text;
    TTF_Font* m_font;
    grim::graphics::Mesh m_mesh;
    grim::graphics::Material m_material;
    grim::graphics::Texture m_texture;
    bool m_isInvalid;
};

}

}