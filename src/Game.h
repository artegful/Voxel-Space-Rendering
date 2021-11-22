#pragma once

#include "entt.hpp"
#include "Systems/RendererSystem.h"
#include "Systems/ControllerSystem.h"

namespace Voxel
{
    class Game
    {
    public:
        explicit Game();

        void Update();
        bool IsRunning() { return renderer.IsOpen(); }

    private:
        entt::registry registry;
        sf::Clock deltaClock;
        Systems::RendererSystem renderer;
        Systems::ControllerSystem controller;
        
        void ProcessInput();
        void PopulateEntities();
        float CalculateDeltaTime();
        float WaitForTargetFpsIfNeeded(float deltaTime);
    };
}