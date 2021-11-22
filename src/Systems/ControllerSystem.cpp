#include "ControllerSystem.h"

#include "SFML/Graphics.hpp"
#include "Configuration.h"
#include "Components/TransformComponent.h"

#include "cmath"

namespace Systems
{
    ControllerSystem::ControllerSystem(entt::registry& registry) :
    gameRegistry{registry} 
    { 
        previousMousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
    }

    void ControllerSystem::Update(float deltaTime)
    {
        HandleMovement(deltaTime);

        HandleRotation(deltaTime);
    }

    void ControllerSystem::HandleMovement(float deltaTime)
    {
        for (const auto& pair : Configuration::KEY_TO_MOVEMENT)
        {
            if (sf::Keyboard::isKeyPressed(pair.first))
            {
                MoveAllCameras(pair.second * deltaTime);
            }
        }
    }

    void ControllerSystem::HandleRotation(float deltaTime)
    {
        sf::Vector2f currentMousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition());

        sf::Vector2f delta = currentMousePosition - previousMousePosition;
        float sqrMagnitude = delta.x * delta.x + delta.y * delta.y;

        if (sqrMagnitude > Configuration::EPSILON)
        {
            RotateAllCameras(delta * deltaTime);
        }

        previousMousePosition = currentMousePosition;
    }

    void ControllerSystem::MoveAllCameras(const sf::Vector3f& movement)
    {
        auto view = gameRegistry.view<Components::TransformComponent>();

        for (auto entity : view)
        {
            gameRegistry.patch<Components::TransformComponent>(entity, [&movement](auto& transform)
            {
                float angleSin = sin(transform.rotation.y);
                float angleCos = cos(transform.rotation.y);

                sf::Vector2f worldMovement(-movement.x * angleSin + movement.y * angleCos,
                    movement.x * angleCos + movement.y * angleSin);

                transform.position += worldMovement;
                transform.height += movement.z;
            });
        }
    }

    void ControllerSystem::RotateAllCameras(const sf::Vector2f& rotation)
    {
        auto view = gameRegistry.view<Components::TransformComponent>();

        for (auto entity : view)
        {
            gameRegistry.patch<Components::TransformComponent>(entity, [&rotation](auto& transform)
            {
                transform.rotation += sf::Vector2f(
                    -Configuration::VERTICAL_SENSETIVITY * rotation.y, 
                     Configuration::HORIZONTAL_SENSETIVITY * rotation.x);

                transform.rotation.x = std::clamp(transform.rotation.x, 
                    -Configuration::MAX_PITCH_ANGLE, Configuration::MAX_PITCH_ANGLE);
            });
        }
    }
}