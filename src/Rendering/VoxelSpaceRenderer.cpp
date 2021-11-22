#include "VoxelSpaceRenderer.h"

#include <algorithm>
#include <vector>
#include <cmath>
#include "Configuration.h"

namespace Rendering
{
    VoxelSpaceRenderer::VoxelSpaceRenderer(const char* colorMapFile, const char* heightMapFile)
    {
        sf::Image coloredImage;
        if (!coloredImage.loadFromFile(colorMapFile))
        {
            throw std::invalid_argument("Color image missing");
        }

        sf::Vector2u size = coloredImage.getSize();

        colorMap = PixelMap<sf::Uint8, 4>(size.x, size.y, coloredImage.getPixelsPtr());

        sf::Image heightImage;
        if (!heightImage.loadFromFile(heightMapFile))
        {
            throw std::invalid_argument("Height image missing");
        }

        heightMap = PixelMap<sf::Uint8, 4>(size.x, size.y, heightImage.getPixelsPtr());
    }

    void VoxelSpaceRenderer::Draw(sf::RenderWindow& renderWindow, sf::Vector2f position, 
            sf::Vector2f rotation, float height, float fov)
    {
        sf::Vector2u screenSize = renderWindow.getSize();
        float screenDistance = screenSize.x / 2 / tan(fov / 2);

        PixelMap<sf::Uint8, 4> pixelMap(screenSize.x, screenSize.y);
        pixelMap.Fill(0);

        std::vector<int> rayBuffer(screenSize.x, screenSize.y);

        float rayAngle = rotation.y - fov / 2;
        float deltaAngle = fov / screenSize.x;

        for (unsigned int i = 0; i < screenSize.x; i++, rayAngle += deltaAngle)
        {
            float rayCos = cos(rayAngle);
            float raySin = sin(rayAngle);

            for (int depth = 1; depth < Configuration::DRAW_DISTANCE; depth++)
            {
                int x = static_cast<int>(position.x + depth * rayCos);
                int y = static_cast<int>(position.y + depth * raySin);

                float NoFishEyeDepth = depth * cos(rotation.y - rayAngle);
                float projectedDeltaHeight = (height - heightMap.GetPixel(x, y))
                    / NoFishEyeDepth * screenDistance * Configuration::MOUNTAIN_HEIGHT_SCALE;

                float projectedHeight = screenSize.y / 2 + projectedDeltaHeight;
                float projectedHeightWithPitch = projectedHeight + 100 * rotation.x;

                int screenHeight = static_cast<int>(projectedHeightWithPitch);

                if (screenHeight < rayBuffer[i])
                {
                    screenHeight = std::max(screenHeight, 0);

                    for (int j = screenHeight; j < rayBuffer[i]; j++)
                    {
                        for (int channel = 0; channel < 4; channel++)
                        {
                            sf::Uint8 value = colorMap.GetPixel(x, y, channel);
                            pixelMap.SetPixel(i, j, value, channel);    
                        }
                    }

                    if (screenHeight == 0)
                    {
                        break;
                    }

                    rayBuffer[i] = screenHeight;
                }
            }
        }

        sf::Image resultImage;
        resultImage.create(screenSize.x, screenSize.y, pixelMap.GetArray());

        sf::Texture texture;
        texture.loadFromImage(resultImage);

        sf::Sprite resultSprite(texture);

        renderWindow.draw(resultSprite);
    }
}