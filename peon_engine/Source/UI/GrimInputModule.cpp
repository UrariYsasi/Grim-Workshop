#include "PCH.hpp"
#include "GrimInputModule.hpp"

namespace grim::ui
{

GrimInputModule::GrimInputModule()
{
}

GrimInputModule::~GrimInputModule()
{
}

bool GrimInputModule::Initialize()
{
    LOG() << "Input Module GrimInputModule initializing...";

    std::fill(m_heldKeys, m_heldKeys + static_cast<uint16_t>(KeyScancode::TotalKeys), false);
    std::fill(m_pressedKeys, m_pressedKeys + static_cast<uint16_t>(KeyScancode::TotalKeys), false);
    std::fill(m_releasedKeys, m_releasedKeys + static_cast<uint16_t>(KeyScancode::TotalKeys), false);

    LOG() << "Input Module GrimInputModule initialized.";
    return true;
}

void GrimInputModule::Terminate()
{
    LOG() << "Input Module GrimInputModule terminating...";
    LOG() << "Input Module GrimInputModule terminated.";
}

void GrimInputModule::Update()
{
    std::fill(m_pressedKeys, m_pressedKeys + static_cast<uint16_t>(KeyScancode::TotalKeys), false);
    std::fill(m_releasedKeys, m_releasedKeys + static_cast<uint16_t>(KeyScancode::TotalKeys), false);
}

void GrimInputModule::RegisterKeyPress(KeyScancode key)
{
    if (key >= KeyScancode::TotalKeys)
    {
        LOG_ERROR() << "RegisterKeyPress() called with unknown scancode " << static_cast<uint16_t>(key) << ".";
        return;
    }

    if (!IsKeyHeld(key))
    {
        m_pressedKeys[static_cast<uint16_t>(key)] = true;

        LOG() << "Key " << static_cast<uint16_t>(key) << " was pressed.";
    }

    m_heldKeys[static_cast<uint16_t>(key)] = true;
}

void GrimInputModule::RegisterKeyRelease(KeyScancode key)
{
    if (key >= KeyScancode::TotalKeys)
    {
        LOG_ERROR() << "RegisterKeyRelease() called with unknown scancode " << static_cast<uint16_t>(key) << ".";
        return;
    }

    m_releasedKeys[static_cast<uint16_t>(key)] = true;
    m_heldKeys[static_cast<uint16_t>(key)] = false;

    LOG() << "Key " << static_cast<uint16_t>(key) << " was released.";
}

void GrimInputModule::RegisterMousePress(MouseButton button)
{
    if (button >= MouseButton::TotalButtons)
    {
        LOG_ERROR() << "RegisterMousePress() called with unknown button " << static_cast<uint16_t>(button) << ".";
        return;
    }

    m_pressedMouseButtons[static_cast<uint16_t>(button)] = true;

    LOG() << "Mouse button " << static_cast<uint16_t>(button) << " was pressed.";
}

void GrimInputModule::RegisterMouseRelease(MouseButton button)
{
    if (button >= MouseButton::TotalButtons)
    {
        LOG_ERROR() << "RegisterMouseRelease() called with unknown button " << static_cast<uint16_t>(button) << ".";
        return;
    }

    m_releasedMouseButtons[static_cast<uint16_t>(button)] = true;

    LOG() << "Mouse button " << static_cast<uint16_t>(button) << " was released.";
}

bool GrimInputModule::IsKeyHeld(KeyScancode key) const
{
    if (key >= KeyScancode::TotalKeys)
    {
        LOG_ERROR() << "IsKeyHeld() called with unknown scancode " << static_cast<uint16_t>(key) << ".";
        return false;
    }

    return m_heldKeys[static_cast<uint16_t>(key)];
}

bool GrimInputModule::IsKeyPressed(KeyScancode key) const
{
    if (key >= KeyScancode::TotalKeys)
    {
        LOG_ERROR() << "IsKeyPressed() called with unknown scancode " << static_cast<uint16_t>(key) << ".";
        return false;
    }

    return m_pressedKeys[static_cast<uint16_t>(key)];
}

bool GrimInputModule::IsKeyReleased(KeyScancode key) const
{
    if (key >= KeyScancode::TotalKeys)
    {
        LOG_ERROR() << "IsKeyReleased() called with unknown scancode " << static_cast<uint16_t>(key) << ".";
        return false;
    }

    return m_releasedKeys[static_cast<uint16_t>(key)];
}

}

/*
void GrimInputModule::Update()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    m_mousePosition = glm::vec2(x, y);

    for (int i = 0; i < MAX_KEYBOARD_KEYS; i++)
    {
        m_downKeys[i] = false;
        m_upKeys[i] = false;
    }

    for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
    {
        m_downMouseButtons[i] = false;
        m_upMouseButtons[i] = false;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        int key = event.key.keysym.sym;
        int mouseButton = event.button.button;

        if (event.type == SDL_KEYDOWN)
        {
            if (!m_currentKeys[SDL_GetScancodeFromKey(key)])
            {
                m_downKeys[SDL_GetScancodeFromKey(key)] = true;
            }

            m_currentKeys[SDL_GetScancodeFromKey(key)] = true;
        }
        else if (event.type == SDL_KEYUP)
        {
            m_upKeys[SDL_GetScancodeFromKey(key)] = true;
            m_currentKeys[SDL_GetScancodeFromKey(key)] = false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (!m_currentMouseButtons[mouseButton])
            {
                m_downMouseButtons[mouseButton] = true;
            }

            m_currentMouseButtons[mouseButton] = true;
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            m_upMouseButtons[mouseButton] = true;
            m_currentMouseButtons[mouseButton] = false;
        }
        else if (event.type == SDL_QUIT)
        {
            if (m_quitCallback != nullptr)
            {
                //m_quitCallback();
            }
        }
    }
}

*/