#pragma once
#include "SFML/System.hpp"

namespace Components
{
    struct TransformComponent
    {
        explicit TransformComponent(sf::Vector2f pos, sf::Vector2f rot, float height) :
        position{pos}, rotation{rot}, height{height} { }

        sf::Vector2f position;
        sf::Vector2f rotation;

        float height;
    };
}