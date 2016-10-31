#include "PCH.hpp"
#include "OpenGLRenderer.hpp"
#include "OpenGL/OpenGLTexture.hpp"

namespace grim
{

namespace graphics
{

OpenGLRenderer::OpenGLRenderer() :
    m_activeCamera(nullptr),
    m_VAOHandle(0),
    m_VBOHandle(0),
    m_EBOHandle(0),
    m_currentPrimitive(PrimitiveType::TRIANGLES),
    m_currentMaterial(nullptr),
    m_cameraScene(nullptr),
    m_cameraUI(nullptr),
    m_currentLayer(0)
{
}

OpenGLRenderer::~OpenGLRenderer()
{
}

void APIENTRY debugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    // Some debug messages are just annoying informational messages
    switch (id)
    {
    case 131169: // The driver allocated storage for renderbuffer
    case 131185: // glBufferData
        return;
    }

    printf("Message: %s\n", message);
    printf("Source: ");

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        printf("API");
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        printf("Window System");
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        printf("Shader Compiler");
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        printf("Third Party");
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        printf("Application");
        break;
    case GL_DEBUG_SOURCE_OTHER:
        printf("Other");
        break;
    }

    printf("\n");
    printf("Type: ");

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        printf("Error");
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        printf("Deprecated Behaviour");
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        printf("Undefined Behaviour");
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        printf("Portability");
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        printf("Performance");
        break;
    case GL_DEBUG_TYPE_MARKER:
        printf("Marker");
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        printf("Push Group");
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        printf("Pop Group");
        break;
    case GL_DEBUG_TYPE_OTHER:
        printf("Other");
        break;
    }

    printf("\n");
    printf("ID: %d\n", id);
    printf("Severity: ");

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        printf("High");
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        printf("Medium");
        break;
    case GL_DEBUG_SEVERITY_LOW:
        printf("Low");
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        printf("Notification");
        break;
    }

    printf("\n\n");
}

bool OpenGLRenderer::Initialize()
{
    // Initialize GL3W
    if (gl3wInit())
    {
        //grim::utility::Debug::LogError("GL3W failed to initialize!");
        return false;
    }

    if (!gl3wIsSupported(3, 2))
    {
        //grim::utility::Debug::LogError("OpenGL 3.2 not supported!");
        return false;
    }

    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        //grim::utility::Debug::Log("Debug output available.");
    }

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set default clear color
    SetClearColor(Color(0.2f, 0.2f, 0.2f));

    // Create VAO
    glGenVertexArrays(1, &m_VAOHandle);

    // Create VBO
    glGenBuffers(1, &m_VBOHandle);

    // Create EBO
    glGenBuffers(1, &m_EBOHandle);

    //glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugMessage, nullptr);

    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    //grim::utility::Debug::LogError("Renderer module OpenGLRenderer initialized.");
    //grim::utility::Debug::Log("    - OpenGL version %s", glGetString(GL_VERSION));
    //grim::utility::Debug::Log("    - GLSL version %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    return true;
}

void OpenGLRenderer::Terminate()
{
    // Delete EBO
    glDeleteBuffers(1, &m_EBOHandle);

    // Delete VBO
    glDeleteBuffers(1, &m_VBOHandle);

    // Delete VAO
    glDeleteVertexArrays(1, &m_VAOHandle);

    //grim::utility::Debug::LogError("Renderer module OpenGLRenderer terminated.");
}

void OpenGLRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::Render()
{
    if (m_renderQueue.size() == 0)
    {
        return;
    }

    // Batch Sort
    std::sort(m_renderQueue.begin(), m_renderQueue.end());

    PaintersSort();

    for (auto it = m_renderQueue.begin(); it != m_renderQueue.end(); it++)
    {
        Process(*it);

        m_renderCommandCount++;
    }

    m_renderQueue.clear();

    UploadBatch();
    RenderBatch();
    ClearBatch();

    ////grim::utility::Debug::Log("Processed %d commands in %d render batches", m_renderCommandCount, m_renderBatchCount);
    m_renderCommandCount = 0;
    m_renderBatchCount = 0;
}

void OpenGLRenderer::Submit(const RenderCommand& command)
{
    m_renderQueue.push_back(command);
}

void OpenGLRenderer::SetLayerCamera(const uint8_t layer, Camera* camera)
{
    if (layer == 0)
    {
        m_cameraScene = camera;
    }
    else if (layer == 1)
    {
        m_cameraUI = camera;
    }
}

std::unique_ptr<assets::Texture> OpenGLRenderer::CreateTexture(std::string const& id, uint32_t const& width, uint32_t const& height, unsigned char const* data) const
{
    return std::make_unique<OpenGLTexture>(id, width, height, data);
}

void OpenGLRenderer::Process(const RenderCommand& command)
{
    Mesh* mesh = command.mesh;
    assets::Material* material = command.material;
    Transform transform = command.transform;
    uint8_t layer = command.layer;

    if ((mesh == nullptr) || (material == nullptr))
    {
        return;
    }

    if (m_currentMaterial == nullptr)
    {
        m_currentMaterial = material;
    }

    if ((m_currentPrimitive != mesh->GetPrimitiveType()) || (m_currentMaterial != material) || (m_currentLayer != layer))
    {
        UploadBatch();
        RenderBatch();
        ClearBatch();
    }

    m_currentPrimitive = mesh->GetPrimitiveType();
    m_currentMaterial = material;
    m_currentLayer = layer;

    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::scale(modelMatrix, transform.scale);
    modelMatrix = glm::rotate(modelMatrix, transform.rotation.x, glm::vec3(1.0, 0.0, 0.0));
    modelMatrix = glm::rotate(modelMatrix, transform.rotation.y, glm::vec3(0.0, 1.0, 0.0));
    modelMatrix = glm::rotate(modelMatrix, transform.rotation.z, glm::vec3(0.0, 0.0, 1.0));

    // Add vertices to buffer
    uint32_t originalVertexCount = m_vertexData.size();
    std::vector<Vertex> newVertices = mesh->GetVertexData();
    for (Vertex vertex : newVertices)
    {
        // Transform vertex
        glm::vec4 position = modelMatrix * glm::vec4(vertex.x, vertex.y, vertex.z, 1.0f);

        vertex.x = position.x;
        vertex.y = position.y;
        vertex.z = position.z;

        // Save new vertex
        m_vertexData.push_back(vertex);
    }

    // Add indices to buffer
    std::vector<uint32_t> newIndices = mesh->GetIndexData();
    for (uint32_t index : newIndices)
    {
        m_indexData.push_back(originalVertexCount + index);
    }
}

void OpenGLRenderer::UploadBatch()
{
    if (m_vertexData.size() == 0)
    {
        return;
    }

    // Get raw vertex data
    GLfloat* vertices = reinterpret_cast<GLfloat*>(m_vertexData.data());

    // Get raw index data
    uint32_t* indices = m_indexData.data();

    // Bind the VAO
    glBindVertexArray(m_VAOHandle);

    // Bind the VBO and upload the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * (m_vertexData.size() * Vertex::SIZE), vertices, GL_DYNAMIC_DRAW);

    // Bind the EBO and upload the element data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * m_indexData.size(), indices, GL_DYNAMIC_DRAW);

    GLuint shaderHandle = m_currentMaterial->GetShaderProgram()->GetHandle();

    GLint positionAttribute = glGetAttribLocation(shaderHandle, "inPosition");
    if (positionAttribute != -1)
    {
        glEnableVertexAttribArray(positionAttribute);
        glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * sizeof(GLfloat), 0);
    }

    GLint colorAttribute = glGetAttribLocation(shaderHandle, "inColor");
    if (colorAttribute != -1)
    {
        glEnableVertexAttribArray(colorAttribute);
        glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, GL_FALSE, Vertex::SIZE * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    }

    GLint uvAttribute = glGetAttribLocation(shaderHandle, "inTexCoord");
    if (uvAttribute != -1)
    {
        glEnableVertexAttribArray(uvAttribute);
        glVertexAttribPointer(uvAttribute, 2, GL_FLOAT, GL_FALSE, Vertex::SIZE * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));
    }

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind the VAO
    glBindVertexArray(0);
}

void OpenGLRenderer::RenderBatch()
{
    m_renderBatchCount++;

    // Bind the VAO
    glBindVertexArray(m_VAOHandle);

    // Bind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOHandle);

    // Bind the correct camera for this layer   
    if (m_currentLayer == 0)
    {
        if (m_cameraScene == nullptr)
        {
            return;
        }

        if (m_cameraScene != m_activeCamera)
        {
            //glEnable(GL_DEPTH_TEST);
            m_cameraScene->Activate();
        }
    }
    else if (m_currentLayer = 1)
    {
        if (m_cameraUI == nullptr)
        {
            return;
        }

        if (m_cameraUI != m_activeCamera)
        {
            //glDisable(GL_DEPTH_TEST);
            m_cameraUI->Activate();
        }
    }

    // Bind our ShaderProgram
    m_currentMaterial->GetShaderProgram()->Bind();

    OpenGLTexture* texture = dynamic_cast<OpenGLTexture*>(m_currentMaterial->GetTexture());
    assert(texture != nullptr && "Texture wasn't an OpenGLTexture!");

    // Upload our model matrix
    glm::mat4 modelMatrix(1.0f);
    GLuint uniModel = glGetUniformLocation(m_currentMaterial->GetShaderProgram()->GetHandle(), "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind our Texture
    if (m_currentMaterial->GetTexture() != nullptr)
    {
        glBindTexture(GL_TEXTURE_2D, texture->GetHandle());
    }

    // Get OpenGL primitive type
    GLenum primitiveType;
    if (m_currentPrimitive == PrimitiveType::TRIANGLES)
    {
        primitiveType = GL_TRIANGLES;
    }
    else if (m_currentPrimitive == PrimitiveType::LINE_LOOP)
    {
        primitiveType = GL_LINE_LOOP;
    }
    else if (m_currentPrimitive == PrimitiveType::LINES)
    {
        primitiveType = GL_LINES;
    }

    // Render
    glDrawElements(primitiveType, m_indexData.size(), GL_UNSIGNED_INT, 0);

    // Unbind our Texture
    if (m_currentMaterial->GetTexture() != nullptr)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // Unbind our ShaderProgram
    m_currentMaterial->GetShaderProgram()->Unbind();

    // Unbind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Unbind the vertex array
    glBindVertexArray(0);
}

void OpenGLRenderer::ClearBatch()
{
    m_vertexData.clear();
    m_indexData.clear();
    m_currentMaterial = nullptr;
    m_currentPrimitive = PrimitiveType::TRIANGLES;
    m_currentLayer = 0;
}

void OpenGLRenderer::PaintersSort()
{
    std::sort(m_renderQueue.begin(), m_renderQueue.end(), [](const RenderCommand& a, const RenderCommand& b)
    {
        if ((a.material->GetTexture() != nullptr) && (a.material->GetTextureTransparencyMode() == assets::Texture::TransparencyMode::Opaque))
        {
            return true;
        }

        return a.transform.position.z < b.transform.position.z;
    });
}
void OpenGLRenderer::SetClearColor(const Color& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRenderer::SetActiveCamera(Camera* camera)
{
    m_activeCamera = camera;
}

Camera* OpenGLRenderer::GetActiveCamera()
{
    return m_activeCamera;
}

}

}