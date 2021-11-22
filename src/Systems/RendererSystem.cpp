#include "RendererSystem.h"

#include <cmath>
#include "Configuration.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"

namespace Systems
{
    RendererSystem::RendererSystem(entt::registry& registry, int width, int height) :
        gameRegistry{registry},
        window {sf::VideoMode(width, height), Configuration::WINDOW_NAME},
        observer{registry, entt::collector.update<Components::TransformComponent>()},
        voxelSpaceRenderer{Configuration::COLOR_MAP_FILE_PATH, Configuration::HEIGHT_MAP_FILE_PATH}
    {
        window.setVerticalSyncEnabled(true);
        window.setMouseCursorVisible(false);
    }

    void RendererSystem::Update(float deltaTime)
    {
        PollEvents();
        UpdateFPSCounter(deltaTime);

        observer.each([&](auto& entity)
        {
            Draw(entity);
        });
    }

    void RendererSystem::PollEvents()
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }
    }

    void RendererSystem::UpdateFPSCounter(float deltaTime)
    {
        int fpsCount = std::round(1.0f / deltaTime);

        std::string windowName(Configuration::WINDOW_NAME);
        windowName += "(" + std::to_string(fpsCount) + " fps)";

        window.setTitle(windowName);
    }

    void RendererSystem::OnAddCamera(entt::registry& registry, entt::entity entity)
    {
        Draw(entity);
    }

    void RendererSystem::Draw(const entt::entity& entity)
    {  
        window.clear(Configuration::SKY_COLOR);

        auto [transform, camera] = gameRegistry.get
            <Components::TransformComponent, Components::CameraComponent>(entity);
        voxelSpaceRenderer.Draw(window, transform.position, transform.rotation, transform.height, camera.fov);

        window.display();
    }
}