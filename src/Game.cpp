#include "Game.h"

#include <iostream>
#include "Configuration.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"

namespace Voxel
{
    Game::Game() : 
        renderer{registry, Configuration::SCREEN_WIDTH, Configuration::SCREEN_HEIGHT},
        controller{registry}
    {
        PopulateEntities();
    }

    void Game::Update()
    {
        float deltaTime = CalculateDeltaTime();
        deltaTime = WaitForTargetFpsIfNeeded(deltaTime);

        controller.Update(deltaTime);
        renderer.Update(deltaTime);
    }

    void Game::PopulateEntities()
    {
        registry.on_construct<Components::CameraComponent>()
            .connect<&Systems::RendererSystem::OnAddCamera>(renderer);

        entt::entity cameraEntity = registry.create();
        registry.emplace<Components::TransformComponent>(cameraEntity, 
        Configuration::START_POSITION, Configuration::START_ROTATION, Configuration::START_HEIGHT);
        registry.emplace<Components::CameraComponent>(cameraEntity, Configuration::FOV);
    }

    float Game::CalculateDeltaTime()
    {
        sf::Time passedTime = deltaClock.restart();

        float delta = passedTime.asSeconds();

        return std::min(delta, 1.0f / Configuration::LOWEST_SIMULATION_FPS);
    }

    float Game::WaitForTargetFpsIfNeeded(float deltaTime)
    {
        float targetDelta = 1.0f / Configuration::TARGET_FPS;

        if (deltaTime < targetDelta)
        {
            sf::sleep(sf::seconds(targetDelta - deltaTime));
            deltaTime += deltaClock.restart().asSeconds();
        }

        return deltaTime;
    }
}