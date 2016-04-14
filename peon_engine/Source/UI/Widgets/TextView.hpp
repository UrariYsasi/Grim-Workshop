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
    TextView(const std::string& text, TTF_Font* font, grim::graphics::ShaderProgram* shaderProgram);
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
    std::unique_ptr<grim::graphics::Mesh> m_mesh;
    std::unique_ptr<grim::graphics::Texture> m_texture;
    bool m_isInvalid;
};

}

}