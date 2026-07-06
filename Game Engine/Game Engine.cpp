#include "../Engine/Engine.h"
#include <iostream>
#include <vector>

using namespace nu;

int main()
{

    srand((unsigned int)time(nullptr));
    //INITIALIZATION
    Renderer renderer;
	renderer.Initialize("Game Engine", 1920, 1024);

	//std::cout << sizeof(Vector2) << std::endl;
    Vector2 vel{ 0.5f, 0.0f };
    std::vector<Vector2> v;

    for (unsigned int i = 0; i < 300; i++) {
		v.push_back(Vector2{ RandomFloat(1280, RandomFloat(1024)) });
    }

    //UPDATE
    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        //RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();

        for (int i = 0; i < v.size(); i++)
        {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
            v[i] = v[i] + vel;
            renderer.DrawPoint(v[i].x, v[i].y);
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
    //SHUTDOWN
	renderer.Shutdown();

    return 0;
}

//test