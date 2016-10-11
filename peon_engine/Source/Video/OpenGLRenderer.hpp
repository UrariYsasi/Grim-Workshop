#pragma once

namespace grim
{

namespace graphics
{

class OpenGLRenderer : public IRenderer
{
public:
    OpenGLRenderer();
    ~OpenGLRenderer();

    virtual bool Initialize();
    virtual void Terminate();
    virtual void Clear();
    virtual void Render();
    virtual void Submit(const RenderCommand& command);

    virtual void SetLayerCamera(const uint8_t layer, Camera* camera);
    virtual void SetClearColor(const Color& color);
    virtual void SetActiveCamera(Camera* camera);

    virtual Camera* GetActiveCamera();

private:
    virtual void Process(const RenderCommand& command);
    virtual void UploadBatch();
    virtual void RenderBatch();
    virtual void ClearBatch();
    void PaintersSort();

private:
    Camera* m_activeCamera;
    std::vector<RenderCommand> m_renderQueue;
    uint32_t m_renderCommandCount;
    uint32_t m_renderBatchCount;
    GLuint m_VAOHandle;
    GLuint m_VBOHandle;
    GLuint m_EBOHandle;
    PrimitiveType m_currentPrimitive;
    assets::Material* m_currentMaterial;
    uint8_t m_currentLayer;
    std::vector<Vertex> m_vertexData;
    std::vector<uint32_t> m_indexData;

    Camera* m_cameraScene;
    Camera* m_cameraUI;
};

}

}