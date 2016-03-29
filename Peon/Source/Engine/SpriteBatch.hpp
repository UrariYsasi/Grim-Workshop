#pragma once

namespace grim
{

/*
    A batching utility which collects the data for many sprites at once before uploading them to the
    GPU and rendering them as one Mesh.
*/
class SpriteBatch
{
public:
    SpriteBatch();
    ~SpriteBatch();

    /*
        Add a sprite to this batch to await an upload. 
    */
    void AddSprite(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, grim::Sprite* sprite);

    /*
        Begin the batching process.

        This is the first step in batching, as it clears all buffers and prepares this SpriteBatch
        to recieve new sprites.
    */
    void Begin();

    /*
        End the batching process.

        This is the final step in batching. This function will upload and then render the sprites
        that it currently has stored in the batch.
    */
    void End();

private:

    /*
        Add a vertex to the vertex data buffer to await an upload.
    */
    void AddVertex(const grim::Vertex& vertex);

    /*
        Add an element index to the element data buffer to await an upload.
    */
    void AddElementIndex(int index);

    /*
        Clear the Texture, ShaderProgram, and all vertices from this batch.
    */
    void Clear();

    /*
        Upload the raw vertex and element data to OpenGL to await rendering.
    */
    void Upload();

    /*
        Render the SpriteBatch.
    */
    void Render();

private:
    /*
        The current ShaderProgram for this batch.
    */
    grim::ShaderProgram* m_shaderProgram;

    /*
        The current Texture for this batch.
    */
    grim::Texture* m_texture;

    /*
        The data buffer that holds the raw vertex data before uploading it to OpenGL.
    */
    std::vector<grim::Vertex> m_vertexDataBuffer;

    /*
        The data buffer that holds the raw element data before uploading it to OpenGL.
    */
    std::vector<int> m_elementDataBuffer;

    /*
        The amount of sprites currently in the batch, that are waiting to be rendered.
    */
    uint16_t m_spriteCount;

    /*
        The amount of vertices currently in the batch, that are waiting to be rendered.
    */
    uint32_t m_vertexCount;

    /*
        The model matrix for this batch.
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
        The OpenGL primitive type that the batch will be rendered with.
    */
    GLuint m_primitiveType;
};

}