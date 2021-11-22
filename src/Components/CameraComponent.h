#pragma once
#include "SFML/System.hpp"

namespace Components
{
    struct CameraComponent
    {
        explicit CameraComponent(float fov) :
        fov{fov} { }

        float fov;
    };
}