#pragma once

namespace grim
{

class Engine;

namespace ui
{

class GrimUI : public IUserInterface
{
public:
    GrimUI(grim::Engine* engine);
    ~GrimUI();
    
    virtual bool Initialize();
    virtual void Terminate();
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void RegisterWidget(grim::ui::Widget* widget);

private:
    grim::Engine* m_engine;
    std::list<grim::ui::Widget*> m_widgets;
};

}

}