#pragma once

#include <unordered_map>
#include "SFML/System.hpp"

namespace Configuration
{
    constexpr const char* WINDOW_NAME = "Voxel Mountains";

    constexpr const char* COLOR_MAP_FILE_PATH = "assets/color_map.png";
    constexpr const char* HEIGHT_MAP_FILE_PATH = "assets/height_map.png";

    inline static sf::Vector2f START_POSITION = sf::Vector2f(100, 100);
    inline static sf::Vector2f START_ROTATION = sf::Vector2f(0, 0);
    constexpr float START_HEIGHT = 100;
    constexpr float MOVEMENT_SPEED = 60;
    constexpr float HORIZONTAL_SENSETIVITY = 1.0f / 6;
    constexpr float VERTICAL_SENSETIVITY = 0.7f;
    constexpr float MAX_PITCH_ANGLE = 6;

    inline static sf::Color SKY_COLOR = sf::Color(135, 206, 235, 255);
    constexpr float FOV = 3.1416 / 3;
    constexpr int DRAW_DISTANCE = 600;
    constexpr float MOUNTAIN_HEIGHT_SCALE = 1;

    constexpr int SCREEN_WIDTH = 800;
    constexpr int SCREEN_HEIGHT = 600;

    constexpr int LOWEST_SIMULATION_FPS = 20;
    constexpr int TARGET_FPS = 60;
    constexpr float EPSILON = 0.000001f;

    inline static std::unordered_map<sf::Keyboard::Key, sf::Vector3f> KEY_TO_MOVEMENT = 
        {
            {sf::Keyboard::W, sf::Vector3f(0,  Configuration::MOVEMENT_SPEED, 0)},
            {sf::Keyboard::A, sf::Vector3f(-Configuration::MOVEMENT_SPEED, 0, 0)},
            {sf::Keyboard::S, sf::Vector3f(0, -Configuration::MOVEMENT_SPEED, 0)},
            {sf::Keyboard::D, sf::Vector3f(Configuration::MOVEMENT_SPEED,  0, 0)},
            {sf::Keyboard::E, sf::Vector3f(0,  0, Configuration::MOVEMENT_SPEED)},
            {sf::Keyboard::Q, sf::Vector3f(0,  0,-Configuration::MOVEMENT_SPEED)}
        };
}