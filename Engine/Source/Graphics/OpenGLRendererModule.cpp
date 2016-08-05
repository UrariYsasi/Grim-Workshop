/*
    OpenGLRendererModule.cpp
    Peon Engine

    Declan Hopkins
    8/5/2016
*/

#include "PCH.hpp"
#include "OpenGLRendererModule.hpp"

namespace grim
{

// Shader sources
const GLchar* vertexSource =
    "#version 150 core\n"
    "in vec2 position;"
    "in vec3 color;"
    "out vec3 Color;"
    "void main()"
    "{"
    "    Color = color;"
    "    gl_Position = vec4(position, 0.0, 1.0);"
    "}";

const GLchar* fragmentSource =
    "#version 150 core\n"
    "in vec3 Color;"
    "out vec4 outColor;"
    "void main()"
    "{"
    "    outColor = vec4(Color, 1.0);"
    "}";

OpenGLRendererModule::OpenGLRendererModule() :
    m_VAOHandle(0),
    m_VBOHandle(0),
    m_EBOHandle(0)
{
}

OpenGLRendererModule::~OpenGLRendererModule()
{
}

bool OpenGLRendererModule::Initialize()
{
    LOG() << "Renderer Module OpenGLRendererModule initializing...";

    if (gl3wInit())
    {
        LOG_ERROR() << "GL3W failed to initialize!";
        return false;
    }

    LOG() << "Supported OpenGL version: " << glGetString(GL_VERSION);
    LOG() << "Supported GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION);
    LOG() << "Using OpenGL version: " << OPENGL_VERSION;

    if (!gl3wIsSupported(OPENGL_VERSION_MAJOR, OPENGL_VERSION_MINOR))
    {
        LOG_ERROR() << "OpenGL version " << OPENGL_VERSION << " is not supported!";
        return false;
    }

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set default clear color
    glClearColor((100.0f / 255.0f), (255.0f / 255.0f), (218.0f / 255.0f), 1.0f);

    // Create VAO
    glGenVertexArrays(1, &m_VAOHandle);

    // Create VBO
    glGenBuffers(1, &m_VBOHandle);

    // Create EBO
    glGenBuffers(1, &m_EBOHandle);

    // BEGIN TEST STUFF

    glBindVertexArray(m_VAOHandle);

    GLfloat vertices[] = {
       -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
       -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_VBOHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

    // END TEST STUFF

    LOG() << "Renderer Module OpenGLRendererModule initialized.";
    return true;
}

void OpenGLRendererModule::Terminate()
{
    LOG() << "Renderer Module OpenGLRendererModule terminating...";

    // Delete EBO
    glDeleteBuffers(1, &m_EBOHandle);

    // Delete VBO
    glDeleteBuffers(1, &m_VBOHandle);

    // Delete VAO
    glDeleteVertexArrays(1, &m_VAOHandle);

    LOG() << "Renderer Module OpenGLRendererModule terminated.";
}

void OpenGLRendererModule::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererModule::Render()
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenGLRendererModule::Submit()
{
}

}