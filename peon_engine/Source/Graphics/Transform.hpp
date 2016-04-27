#pragma once

namespace grim
{

namespace graphics
{

struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) :
        position(position),
        rotation(rotation),
        scale(scale)
    {
    }

    Transform() :
        position(glm::vec3(0.0f)),
        rotation(glm::vec3(0.0f)),
        scale(glm::vec3(1.0f))
    {
    }
};

}

}