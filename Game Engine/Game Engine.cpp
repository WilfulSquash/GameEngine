#include "../Engine/Engine.h"

using namespace nu;
using namespace std;


int main()
{

    srand((unsigned int)time(nullptr));
    //INITIALIZATION
    Renderer renderer;
	renderer.Initialize("Game Engine", 1920, 1024);

	Input input;
	input.Initialize();

    nu::Time time;

    Actor player{ Transform{Vector2{ 640.0f, 512.0f }, 0.0f, 50.0f} };

	//std::cout << sizeof(Vector2) << std::endl;
    Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };
    float speed = 300.0f;

    std::vector<Vector2> points;
    
    

    //UPDATE
    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

		input.Update();
        time.Tick();

        
        
        //cout << seconds << "" << dt << endl;

        /*if (input.GetKeyPressed(SDL_SCANCODE_Q)) { cout << "pressed\n"; }
        if (input.GetKeyDown(SDL_SCANCODE_Q)) { cout << "down\n"; }
        if (input.GetKeyReleased(SDL_SCANCODE_Q)) { cout << "released\n"; }

        if (input.GetButtonPressed(Input::MouseButton::LEFT)) cout << "Button Pressed\n";*/

        /*if (input.GetButtonPressed(Input::MouseButton::LEFT)) {
            points.push_back(input.GetMousePosition());
        }*/
        if (input.GetMouseDown(Input::MouseButton::LEFT)) {
            if (points.empty()) {
                points.push_back(input.GetMousePosition());
            }
            else {
                Vector2 v = points.back() - input.GetMousePosition();
                if (v.Length() > 30.0f) {
                    points.push_back(input.GetMousePosition());
                }
            }
        }
        //undo
        if (input.GetButtonPressed(Input::MouseButton::RIGHT)) {
            if (!points.empty()) { points.pop_back(); }
        }

        Vector2 force{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;

		player.SetVelocity(force);
		player.Update(time.GetDeltaTime());
                
        /*velocity += (force * time.GetDeltaTime());
        position += (velocity * time.GetDeltaTime());

        position.x = Wrap(0.0f, 1920.0f, position.x);
        position.y = Wrap(0.0f, 1024.0f, position.y);*/
   

        //RENDER
        renderer.SetColorf(0.0f, 0.0f, 0.0f);
        renderer.Clear();

        for (int i = 0; i < (int)points.size() - 1; i++)
        {
            //renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
            renderer.SetColorf(1.0f, 1.0f, 1.0f);
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
            //renderer.DrawFillRect(points[i].x, points[i].y, 10, 10);
        }

        //character
        /*renderer.SetColorf(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);*/
		player.Draw(renderer);

        renderer.Present();
        /*
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
        */
    }
    //SHUTDOWN
	renderer.Shutdown();

    return 0;
}

//test