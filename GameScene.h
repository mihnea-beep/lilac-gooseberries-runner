#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "GUI.h"
using namespace std;


class GameScene
{
  bool GameScene_running = false;
  SDL_Window* sceneWindow = NULL;


  public:

    GameScene(); // interface maybe?

    virtual void loadRes(SDL_Renderer* Renderer);
    virtual void Init(SDL_Renderer* Renderer);
    virtual void checkInput();
    virtual void update();
    virtual void render(SDL_Renderer*);
    virtual void loop(SDL_Renderer* Renderer);
    virtual void loadGameScene(SDL_Renderer* Renderer);
    
    virtual SDL_Window* getWindow();
    virtual void setWindow(SDL_Window* window);



    virtual void setRunning(bool);
    virtual bool getRunning();

    virtual void free();

    virtual ~GameScene();


};
