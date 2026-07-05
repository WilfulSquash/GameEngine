#include "../Engine/Engine.h"
#include "SDL3/SDL.h"
#include <iostream>


int main()
{
    srand((unsigned int)time(nullptr));

    nu::Renderer renderer;
	renderer.Initialize("Game Engine", 1920, 1024);

    SDL_Event e;
    bool quit = false;


    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.SetColor(0, 0, 0);
        renderer.Clear();

        for (int i = 0; i < 20; i++)
        {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawPoint(rand() % 1920, rand() % 1024);
        }

        for (int i = 0; i < 10; i++) 
        {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);

            renderer.DrawPoint(
                rand() % 1920,
                rand() % 1024
            );
        }

        for (int i = 0; i < 10; i++)
        {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);

            int x = rand() % 1920;
            int y = rand() % 1024;
            int w = rand() % 200 + 20;
            int h = rand() % 200 + 20;

            renderer.DrawRect(x, y, w, h);
        }

        for (int i = 0; i < 1000; i++) {
			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
			renderer.DrawPoint(rand() % 1280, rand() % 1024);
        }
 
		renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
        renderer.DrawFillRect(40, 40, 50, 50);
       
		renderer.Present();
    }

	renderer.Shutdown();

    return 0;
}

//test