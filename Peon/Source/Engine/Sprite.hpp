#pragma once

namespace grim
{

/*
    A 2D, renderable texture.
*/
class Sprite
{
public:
    Sprite(grim::Texture* texture, grim::ShaderProgram* shaderProgram);
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
    grim::Texture* m_texture;
    grim::ShaderProgram* m_shaderProgram;
    glm::mat4 m_modelMatrix;
    GLuint m_VAOHandle;
    GLuint m_VBOHandle;
    GLuint m_EBOHandle;
};

}