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

private:
    /*
        The OpenGL handle for the vertex array object.

        A VAO is an OpenGL object that stores all the state needed to supply vertex data to the
        GPU. It stores the format of the vertex data, as well as the buffer objects.
    */
    GLuint m_VAOHandle;

    /*
        The OpenGL handle for the vertex buffer object.

        A VBO is a buffer object which is used as the source for vertex array data. 
    */
    GLuint m_VBOHandle;

    /*
        The OpenGL handle for the element buffer object.

        An EBO is a buffer object which is used as the source for vertex indices. This is used in 
        conjunction with the VBO to ensure that vertices are drawn in the correct order.
    */
    GLuint m_EBOHandle;
};

}