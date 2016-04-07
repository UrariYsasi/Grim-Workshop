#pragma once

namespace grim
{

namespace utility
{

enum DebugFlags
{
    LOGGING                 = 1 << 0,
    SHOW_MENU               = 1 << 1,
    CHEAT                   = 1 << 2,
    RENDER_HITBOXES         = 1 << 3,
    RENDER_TILE_OUTLINES    = 1 << 4,
    RENDER_ORIGINS          = 1 << 5,
    MIX_AUDIO               = 1 << 6
};

class Debug
{
public:
    static void Log(const char* format, ...);
    static void LogError(const char* format, ...);
    static void EnableFlag(uint8_t flag);
    static void DisableFlag(uint8_t flag);
    static void ToggleFlag(uint8_t flag);
    static bool IsFlagEnabled(uint8_t flag);

private:
    static uint8_t m_flags;
};

}

}