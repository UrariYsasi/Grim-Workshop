#pragma once

namespace grim
{

class SpriteBatch
{
    public:
        SpriteBatch();
        ~SpriteBatch();

        void AddSprite(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, grim::Sprite* sprite);
        void Begin();
        void End();

    private:
        void AddVertex(const grim::Vertex& vertex);
        void AddElementIndex(int index);
        void Clear();
        void Upload();
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