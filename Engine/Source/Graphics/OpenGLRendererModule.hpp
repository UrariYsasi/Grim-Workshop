/*
    OpenGLRendererModule.hpp
    Peon Engine

    Declan Hopkins
    8/5/2016

    A Renderer Module that renders using the OpenGL API. Using this Module requires that the Window
    Module is capable of supporting an OpenGL context.
*/

#pragma once

#define OPENGL_VERSION_MAJOR 3
#define OPENGL_VERSION_MINOR 2
#define OPENGL_VERSION OPENGL_VERSION_MAJOR.OPENGL_VERSION_MINOR

namespace grim
{

class OpenGLRendererModule : public IRendererModule
{
public:
    OpenGLRendererModule();
    ~OpenGLRendererModule();

    /*
        IModule Interface
    */

    virtual bool Initialize() override;
    virtual void Terminate() override;

    /*
        IRendererModule Interface
    */
    virtual void Clear() override;
    virtual void Render() override;
    virtual void Submit() override;
};

}