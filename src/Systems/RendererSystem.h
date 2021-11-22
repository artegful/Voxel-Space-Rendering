#pragma once

#include <vector>

#include "entt.hpp"
#include "SFML/Graphics.hpp"
#include "Rendering/VoxelSpaceRenderer.h"

namespace Systems
{
    class RendererSystem
    {
    public:
        explicit RendererSystem(entt::registry& registry, int width, int height);

        void Update(float deltaTime);
        void OnAddCamera(entt::registry& registry, entt::entity entity);
        bool IsOpen() { return window.isOpen(); }

    private:
        entt::registry& gameRegistry;
        sf::RenderWindow window;
        entt::observer observer;
        Rendering::VoxelSpaceRenderer voxelSpaceRenderer;

        void PollEvents();
        void InitialDraw();
        void Draw(const entt::entity& entity);
        void UpdateFPSCounter(float deltaTime);
    };
}