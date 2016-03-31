#pragma once

namespace grim
{

namespace graphics
{

/*
    A renderable Mesh.
*/
class Mesh
{
public:
    Mesh(grim::graphics::ShaderProgram* shaderProgram, grim::graphics::Texture* texture);
    ~Mesh();

    /*
        Render the sprite at the given position, with the given rotation and scale.
    */
    void Render(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

    /*
        Upload a new vertex array to the Mesh.
    */
    void UploadVertexData(GLfloat* vertices, unsigned int verticesSize);

    /*
        Upload a new element array to the Mesh.
    */
    void UploadElementData(GLuint* elements, unsigned int elementsSize);

    /*
        Set the OpenGL render mode of the Mesh.
    */
    void SetRenderMode(GLenum mode);

private:

    /*
        The ShaderProgram for this Mesh.
    */
    grim::graphics::ShaderProgram* m_shaderProgram;

    /*
        The Texture for this Mesh.
    */
    grim::graphics::Texture* m_texture;

    /*
        The model matrix for this Mesh.
    */
    glm::mat4 m_modelMatrix;

    /*
        The OpenGL handle for the VAO.
    */
    GLuint m_VAOHandle;

    /*
        The OpenGL handle for the VBO.
    */
    GLuint m_VBOHandle;

    /*
        The OpenGL handle for the EBO.
    */
    GLuint m_EBOHandle;

    /*
        The OpenGL render mode that this Mesh will be rendered with.
    */
    GLenum m_mode;
};

}

}