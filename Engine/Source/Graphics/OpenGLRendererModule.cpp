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

OpenGLRendererModule::OpenGLRendererModule()
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

    LOG() << "Supported OpenGL version: " << glGetString(GL_VERSION);
    LOG() << "Supported GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION);
    LOG() << "Using OpenGL version: " << OPENGL_VERSION;

    LOG() << "Renderer Module OpenGLRendererModule initialized.";
    return true;
}

void OpenGLRendererModule::Terminate()
{
    LOG() << "Renderer Module OpenGLRendererModule terminating...";
    LOG() << "Renderer Module OpenGLRendererModule terminated.";
}

void OpenGLRendererModule::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererModule::Render()
{
}

void OpenGLRendererModule::Submit()
{
}

}