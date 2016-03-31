#pragma once

namespace grim
{

namespace utility
{

class PoissonDiskGenerator
{
public:

    /*
        Generates, using the given parameters, and returns a vector of Poisson sample points within the given zone.
    */
    static std::vector<glm::vec2> Generate(const glm::vec2& initialPoint, double innerRadius, double outerRadius, int precision, const grim::graphics::Rect& zone);
};

}

}