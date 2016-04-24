#pragma once

namespace grim
{

namespace graphics
{

struct RenderCommand
{
    Mesh* mesh;
    Material* material;

    RenderCommand(Mesh* mesh, Material* material) :
        mesh(mesh),
        material(material)
    {
    }
};

}

}