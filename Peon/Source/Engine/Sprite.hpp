#pragma once

namespace grim
{

/*
    A 2D, renderable sprite.
*/
class Sprite
{
public:
    Sprite(grim::Texture* spriteSheet, grim::ShaderProgram* shaderProgram, int frame);
    ~Sprite();

    /*
        Render the sprite at the given position, with the given rotation and scale.
    */
    void Render(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

private:
    /*
        Create and upload the mesh data that will be used to render this Sprite.
    */
    void CreateMesh();

private:
    grim::Texture* m_spriteSheet;
    grim::ShaderProgram* m_shaderProgram;
    int m_frame;
    glm::mat4 m_modelMatrix;
    GLuint m_VAOHandle;
    GLuint m_VBOHandle;
    GLuint m_EBOHandle;
};

}