#include "../Engine/Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>
#include "Assets.h"

#include <iostream>
#include <vector>

using namespace nu;
using namespace std;

int main(){

    ////WORKING DIRECTORY TEST
    //// get current working directory
    //std::cout << "Directory Operations:\n";
    //std::cout << "Working directory: " << nu::GetWorkingDirectory() << "\n";

    //// set working directory (current working directory + "Assets")
    //std::cout << "Setting directory to 'Assets'...\n";
    //nu::SetWorkingDirectory("Assets");
    //std::cout << "New directory: " << nu::GetWorkingDirectory() << "\n\n";

    //// get filenames in the working directory
    //std::cout << "Files in Directory:\n";
    //auto filenames = nu::GetFilesInDirectory(nu::GetWorkingDirectory());
    //for (const auto& filename : filenames)
    //{
    //    std::cout << filename << "\n";
    //}
    //std::cout << "\n";

    //// get filename info
    //if (!filenames.empty())
    //{
    //    // get filename
    //    std::string str = nu::GetFilename(filenames[0]);
    //    std::cout << "Filename: " << str << "\n";

    //    // get extension
    //    str = nu::GetFileExtension(filenames[0]);
    //    std::cout << "Extension: " << str << "\n";

    //    // get filename no extension
    //    str = nu::GetFilenameNoExtension(filenames[0]);
    //    std::cout << "Filename No Extension: " << str << "\n\n";
    //}

    //// read and display text file
    //std::cout << "Text File Reading:\n";
    //std::string str;
    //if (nu::ReadTextFile("test.txt", str))
    //{
    //    std::cout << str << "\n";
    //}

    //// write to text file
    //std::cout << "Text File Writing:\n";
    //nu::WriteTextFile("test.txt", "Hello, World!", true);
    //if (nu::ReadTextFile("test.txt", str))
    //{
    //    std::cout << str << "\n";
    //}


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
    Engine::Get().Initialize();
   
    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = assets::playerModel;
    playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 15.0f };
    playerDesc.velocity = { 0.0f, 0.0f };
    playerDesc.speed = 2000.0f;

    Player* player = new Player{playerDesc};
	scene.AddActor(player);

    EnemyDesc enemyDesc;
    enemyDesc.name = "Enemy";
    enemyDesc.model = assets::enemyModel;
    enemyDesc.transform = Transform{ Vector2{RandomFloat((float)Engine::Get().GetRenderer().GetWidth()), RandomFloat((float)Engine::Get().GetRenderer().GetHeight())}, 0.0f, 15.0f};
    enemyDesc.velocity = { 0.0f, 0.0f };
    enemyDesc.speed = 2000.0f;

    for (size_t i = 0; i < 20; i++){
        enemyDesc.transform = Transform{ Vector2{RandomFloat((float)Engine::Get().GetRenderer().GetWidth()), RandomFloat((float)Engine::Get().GetRenderer().GetHeight())}, 0.0f, 15.0f};
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
    Engine::Get().Update();
        
		scene.Update(Engine::Get().GetTime().GetDeltaTime());

        if (Engine::Get().GetInput().GetMouseDown(Input::MouseButton::LEFT)) {
            if (points.empty()) {
                points.push_back(Engine::Get().GetInput().GetMousePosition());
            }
            else {
                Vector2 v = points.back() - Engine::Get().GetInput().GetMousePosition();
                if (v.Length() > 30.0f) {
                    points.push_back(Engine::Get().GetInput().GetMousePosition());
                }
            }
        }

        //undo
        if (Engine::Get().GetInput().GetButtonPressed(Input::MouseButton::RIGHT)) {
            if (!points.empty()) { points.pop_back(); }
        }

        //SOUNDS
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }

        //RENDER
        Engine::Get().GetRenderer().SetColorf(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++)
        {
            Engine::Get().GetRenderer().SetColorf(1.0f, 1.0f, 1.0f);
            Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        //character
		
        scene.Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present();
    
    }
    //SHUTDOWN

    return 0;
}