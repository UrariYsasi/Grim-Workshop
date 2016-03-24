#include "PCH.hpp"
#include "PoissonDiskGenerator.hpp"

namespace grim
{

std::vector<glm::vec2> PoissonDiskGenerator::Generate(const glm::vec2& initialPoint, double innerRadius, double outerRadius, int precision, const grim::Rect& zone)
{
    std::vector<glm::vec2> processingList; // List of points that need to be processed
    std::vector<glm::vec2> outputList; // List of output points

                                       // Get an initial point, add it to processingList and outputList
    processingList.push_back(initialPoint);
    outputList.push_back(initialPoint);

    // While we still have points to process
    while (processingList.size() > 0)
    {
        // Pop a point from the processingList
        glm::vec2 point = processingList.back();
        processingList.pop_back();

        // For this point, generate k points from the annulus surrounding the point
        std::vector<glm::vec2> generatedPoints;
        for (int i = 0; i < precision; i++)
        {
            double angle = Random::Generate(0.0, 1.0) * M_PI * 2;
            double distance = innerRadius + (Random::Generate(0.0, 1.0) * outerRadius);
            glm::vec2 offset(distance * std::cos(angle), distance * std::sin(angle));
            glm::vec2 point(point + offset);
            generatedPoints.push_back(point);
        }

        // For every point that has been generated
        for (auto pointIt = generatedPoints.begin(); pointIt != generatedPoints.end(); pointIt++)
        {
            glm::vec2 point = (*pointIt);
            bool isValid = true;

            // Check for points that are too close to this point
            for (auto otherIt = outputList.begin(); otherIt != outputList.end(); otherIt++)
            {
                glm::vec2 other = (*otherIt);
                if (glm::distance(point, other) < innerRadius)
                {
                    isValid = false;
                    break;
                }
            }

            if (!zone.ContainsPoint(point))
            {
                isValid = false;
            }

            // If there are no points within the range of this point, add it to the outputList and processingList.
            if (isValid == true)
            {
                // If we have enough samples, we don't have to process anything anymore.
                //if (outputList.size() >= samples)
                //{
                //    break;
                //}

                processingList.push_back(point);
                outputList.push_back(point);
            }
        }
    }

    return outputList;
}

}