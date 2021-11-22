#include "Game.h"

int main()
{
    Voxel::Game game;

    while (game.IsRunning())
    {
        game.Update();
    } 
}
