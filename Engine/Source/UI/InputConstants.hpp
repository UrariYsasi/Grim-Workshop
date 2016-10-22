/*
    InputConstants.hpp
    Engine

    Declan Hopkins
    9/9/2016

    Contains definitions for input constants, such as mouse buttons and keyboard scancodes.
*/

#pragma once

namespace grim::ui
{

enum class MouseButton
{
    Unknown = 0,

    Left = 1,
    Middle = 2,
    Right = 3,

    TotalButtons = 255
};

enum class KeyScancode
{
    Unknown = 0,

    /*
        Alphabetic Keys
    */

    A = 4,
    B = 5,
    C = 6,
    D = 7,
    E = 8,
    F = 9,
    G = 10,
    H = 11,
    I = 12,
    J = 13,
    K = 14,
    L = 15,
    M = 16,
    N = 17,
    O = 18,
    P = 19,
    Q = 20,
    R = 21,
    S = 22,
    T = 23,
    U = 24,
    V = 25,
    W = 26,
    X = 27,
    Y = 28,
    Z = 29,

    /*
        Numeric Keys
    */

    One = 30,
    Two = 31,
    Three = 32,
    Four = 33,
    Five = 34,
    Six = 35,
    Seven = 36,
    Eight = 37,
    Nine = 38,
    Zero = 39,

    /*
        Arrow Keys
    */

    Up = 82,
    Down = 81,
    Left = 80,
    Right = 79,

    /*
        Function Keys
    */

    F1 = 58,
    F2 = 59,
    F3 = 60,
    F4 = 61,
    F5 = 62,
    F6 = 63,
    F7 = 64,
    F8 = 65,
    F9 = 66,
    F10 = 67,
    F11 = 68,
    F12 = 69,

    /*
        Keypad keys
    */

    KeypadOne = 89,
    KeypadTwo = 90,
    KeypadThree = 91,
    KeypadFour = 92,
    KeypadFive = 93,
    KeypadSix = 94,
    KeypadSeven = 95,
    KeypadEight = 96,
    KeypadNine = 97,

    /*
        Modifier Keys
    */

    AltLeft = 226,
    AltRight = 230,
    CtrlLeft = 224,
    CtrlRight = 228,
    ShiftLeft = 225,
    ShiftRight = 229,

    /*
        Misc Keys
    */

    Spacebar = 44,
    Escape = 41,
    Enter = 40,

    TotalKeys = 255
};

}