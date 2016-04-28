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
    uint8_t layer;

    RenderCommand(Mesh* const mesh, Material* const material, const Transform& transform, const uint8_t layer = 0) :
        mesh(mesh),
        material(material),
        transform(transform),
        layer(layer)
    {
    }

    RenderCommand(Sprite* const sprite, const Transform& transform, const uint8_t layer = 0) :
        mesh(sprite->GetMesh()),
        material(sprite->GetMaterial()),
        transform(transform),
        layer(layer)
    {
    }

    bool RenderCommand::operator<(const RenderCommand& other) {
        return (mesh->GetPrimitiveType() < other.mesh->GetPrimitiveType()) ||
               ((mesh->GetPrimitiveType() == other.mesh->GetPrimitiveType()) && (material < other.material)) ||
               ((mesh->GetPrimitiveType() == other.mesh->GetPrimitiveType()) && (material == other.material) && (layer < other.layer));
    }
};

}

}