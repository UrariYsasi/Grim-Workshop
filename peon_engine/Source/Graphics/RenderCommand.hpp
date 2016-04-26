#pragma once

namespace grim
{

namespace graphics
{

struct RenderCommand
{
    Mesh* mesh;
    Material* material;
    Transform transform;

    RenderCommand(Mesh* const mesh, Material* const material, const Transform& transform) :
        mesh(mesh),
        material(material),
        transform(transform)
    {
    }

    RenderCommand(Sprite* const sprite, const Transform& transform) :
        mesh(sprite->GetMesh()),
        material(sprite->GetMaterial()),
        transform(transform)
    {
    }

    bool RenderCommand::operator<(const RenderCommand& other) {
        return (mesh->GetPrimitiveType() < other.mesh->GetPrimitiveType()) ||
               ((mesh->GetPrimitiveType() == other.mesh->GetPrimitiveType()) && (material < other.material));
    }
};

}

}