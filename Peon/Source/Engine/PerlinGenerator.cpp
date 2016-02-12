#include "PCH.hpp"
#include "PerlinGenerator.hpp"

PerlinGenerator::PerlinGenerator()
{
}

PerlinGenerator::~PerlinGenerator()
{
}

double PerlinGenerator::GeneratePerlin2D(const double& x, const double& y)
{
    double total = 0;

    for (int i = 0; i < octaves; i++)
    {
        double frequency = pow(2, i);
        double amplitude = pow(persistence, i);

        total += InterpolatedNoise(x * frequency, y * frequency) * amplitude;
    }

    return total;
}

double PerlinGenerator::InterpolatedNoise(const double& x, const double& y)
{
    int intX = (int)x;
    double fractionX = x - intX;

    int intY = (int)y;
    double fractionY = y - intY;

    // Get the smoothed noise values for each corner
    double s = SmoothNoise(intX, intY);         // Bottom left
    double t = SmoothNoise(intX + 1, intY);     // Bottom right
    double u = SmoothNoise(intX, intY + 1);     // Top left
    double v = SmoothNoise(intX + 1, intY + 1); // Top right

                                                // Interpolate the corner values to get the middle values
    double i = Interpolate(s, t, fractionX);    // Bottom middle
    double ii = Interpolate(u, v, fractionX);   // Top middle

                                                // Interpolate the middle values to get the center value
    return Interpolate(i, ii, fractionY);
}

double PerlinGenerator::SmoothNoise(const int& x, const int& y)
{
    double corners = (Noise(x - 1, y - 1) + Noise(x + 1, y - 1) + Noise(x - 1, y + 1) + Noise(x + 1, y + 1)) / 16;
    double sides = (Noise(x - 1, y) + Noise(x + 1, y) + Noise(x, y - 1) + Noise(x, y + 1)) / 8;
    double center = Noise(x, y) / 4;

    return corners + sides + center;
}

double PerlinGenerator::Interpolate(const double& a, const double& b, const double& w)
{
    // Cosine interpolation
    double ft = w * M_PI;
    double f = (1 - cos(ft)) * 0.5;

    return a * (1 - f) + b * f;
}

double PerlinGenerator::Noise(const int& x, const int& y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    return (double)(1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

/*
heightmap = new double[512 * 512];
for (int y = 0; y < 512; y++)
{
for (int x = 0; x < 512; x++)
{
double val = GeneratePerlin2D((double)(x + offsetX) / 512.0 * scale, (double)(y + offsetY) / 512.0 * scale);
val = (val + 1) / 2.0;

if (val > 1.0)
{
val = 1.0;
}
else if (val < 0.0)
{
val = 0.0;
}

heightmap[(y * 512) + x] = val;
}
*/