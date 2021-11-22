#pragma once

#include "SFML/Graphics.hpp"
#include "entt.hpp"
#include "Configuration.h"

namespace Systems
{
    class ControllerSystem
    {
    public:
        explicit ControllerSystem(entt::registry& registry);
        void Update(float deltaTime);

    private:
        entt::registry& gameRegistry;
        sf::Vector2f previousMousePosition;

        void HandleMovement(float deltaTime);
        void HandleRotation(float deltaTime);
        void MoveAllCameras(const sf::Vector3f& movement);
        void RotateAllCameras(const sf::Vector2f& rotation);
    };
}