#pragma once

static const uint8_t LOGGING = 0x01;              // Log messages to the console
static const uint8_t SHOW_MENU = 0x02;            // Display the debug menu in the game
static const uint8_t CHEAT = 0x04;                // Enable cheat keys
static const uint8_t RENDER_HITBOXES = 0x08;      // Render hit boxes
static const uint8_t RENDER_TILE_OUTLINES = 0x10; // Render TerrainTile outlines
static const uint8_t RENDER_ORIGINS = 0x20;       // Render origin points

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