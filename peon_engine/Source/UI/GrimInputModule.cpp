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