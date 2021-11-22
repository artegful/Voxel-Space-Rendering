#pragma once

#include "SFML/Graphics.hpp"
#include "PixelMap.h"

namespace Rendering
{
    class VoxelSpaceRenderer
    {
    public:
        explicit VoxelSpaceRenderer(const char* colorMapFile, const char* heightMapFile);
        void Draw(sf::RenderWindow& renderWindow, sf::Vector2f position, 
            sf::Vector2f rotation, float height, float fov);

    private:
        PixelMap<sf::Uint8, 4> colorMap;
        PixelMap<sf::Uint8, 4> heightMap;
    };
}