#pragma once

/*
    A Texture that can be used in Mesh rendering.
*/
class Texture
{
public:
    Texture();
    ~Texture();

private:
    /*
        The OpenGL ID for the texture.
    */
    GLuint m_ID;
};