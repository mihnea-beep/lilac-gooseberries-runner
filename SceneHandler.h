#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "GameScene.h"
#include "GUI.h"
#include "Scene.h"
using namespace std;


class SceneHandler: public GameScene
{
  GameScene* Menu;
  Scene* Game;

  bool SceneHandler_running = false;

  public:

    SceneHandler(); // interface maybe?

    void initialize();

    void loadScene(Scene*);
    void loadGameState(GameScene*);


    void loadRes(SDL_Renderer* Renderer);
    void Init(SDL_Renderer* Renderer);
    void checkInput();
    void update();
    void render(SDL_Renderer*);
    void loop(SDL_Renderer* Renderer);
    void loadSceneHandler(SDL_Renderer* Renderer);

    void setRunning(bool);
    bool getRunning();

    void free();

    ~SceneHandler();


};
