#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "GUI.h"
#include "GameScene.h"
using namespace std;


class PauseScene: public GameScene
{
  bool PauseScene_running = false;
  Message pauseMessage;
  bool pauseMessageSet = false;
  Message randomFactMessage;
  string typeRandomFactMessage;
  int typePos = 0;

  public:

    PauseScene(); // interface maybe?

    virtual void loadRes(SDL_Renderer* Renderer);
    virtual void Init(SDL_Renderer* Renderer);
    virtual void checkInput();
    virtual void update();
    virtual void render(SDL_Renderer*);
    virtual void loop(SDL_Renderer* Renderer);
    virtual void loadPauseScene(SDL_Renderer* Renderer);

    virtual void setRunning(bool);
    virtual bool getRunning();

    virtual void free();

    virtual ~PauseScene();


};
