#include "../Engine/Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>

#include <iostream>
#include <vector>

using namespace nu;
using namespace std;

int main(){
    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    //Test FMOD
    /*void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    FMOD::Sound* sound = nullptr;
    audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);

    audio->playSound(sound, 0, false, nullptr);*/

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    std::vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;
    audio->createSound("whistle.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("mario.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    srand((unsigned int)time(nullptr));
    //INITIALIZATION
    engine.Initialize();
   
    //Mesh / Model
    Mesh mesh{ {Vector2{0, 0}, Vector2{1, 1}, Vector2{0, 2}, Vector2{3, 1}, Vector2{0, 0}}, Color{1.0f, 1.0f, 1.0f} };
    Mesh mesh2{ {Vector2{1, 1}, Vector2{-1, -1}, Vector2{-1, 3},Vector2{1, 1}}, Color{0.1333333333f, 0.2941176471f, 1.0f} };
    Model model = vector<Mesh>{ {mesh, mesh2}};
    Model model2 = vector<Mesh>{mesh};

    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = model;
    playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 15.0f };
    playerDesc.velocity = { 0.0f, 0.0f };
    playerDesc.speed = 2000.0f;

    Player* player = new Player{playerDesc};
	scene.AddActor(player);

    EnemyDesc enemyDesc;
    enemyDesc.name = "Enemy";
    enemyDesc.model = model2;
    enemyDesc.transform = Transform{ Vector2{RandomFloat((float)engine.GetRenderer().GetWidth()), RandomFloat((float)engine.GetRenderer().GetHeight())}, 0.0f, 15.0f};
    enemyDesc.velocity = { 0.0f, 0.0f };
    enemyDesc.speed = 2000.0f;

    for (size_t i = 0; i < 20; i++){
        enemyDesc.transform = Transform{ Vector2{RandomFloat((float)engine.GetRenderer().GetWidth()), RandomFloat((float)engine.GetRenderer().GetHeight())}, 0.0f, 15.0f };
        scene.AddActor(new Enemy{ enemyDesc });
    }
   
    Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };

    vector<Vector2> points;
    
    //UPDATE
    SDL_Event e;
    bool quit = false;

    while (!quit) {
        audio->update();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        //Engine
        engine.Update();
        
		scene.Update(engine.GetTime().GetDeltaTime());

        if (engine.GetInput().GetMouseDown(Input::MouseButton::LEFT)) {
            if (points.empty()) {
                points.push_back(engine.GetInput().GetMousePosition());
            }
            else {
                Vector2 v = points.back() - engine.GetInput().GetMousePosition();
                if (v.Length() > 30.0f) {
                    points.push_back(engine.GetInput().GetMousePosition());
                }
            }
        }

        //undo
        if (engine.GetInput().GetButtonPressed(Input::MouseButton::RIGHT)) {
            if (!points.empty()) { points.pop_back(); }
        }

        //SOUNDS
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }

        //RENDER
        engine.GetRenderer().SetColorf(0.0f, 0.0f, 0.0f);
        engine.GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++)
        {
            engine.GetRenderer().SetColorf(1.0f, 1.0f, 1.0f);
            engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        //character
		
        scene.Draw(engine.GetRenderer());

        engine.GetRenderer().Present();
    
    }
    //SHUTDOWN

    return 0;
}