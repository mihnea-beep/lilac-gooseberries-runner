#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "GUI.h"
#include "GameScene.h"
using namespace std;


class OptionsScene: public GameScene
{
  bool OptionsScene_running = false;
  Message pauseMessage;
  bool pauseMessageSet = false;
  Message randomFactMessage;
  string typeRandomFactMessage;
  int typePos = 0;

  bool fullscreenMode = false;
  bool fullscreenToggle = false;


  Message* messagesList;
  int messagesNo;

  public:

    OptionsScene(); // interface maybe?

    virtual void loadRes(SDL_Renderer* Renderer);
    virtual void Init(SDL_Renderer* Renderer);
    virtual void checkInput();
    virtual void update();
    virtual void render(SDL_Renderer*);
    virtual void loop(SDL_Renderer* Renderer);
    virtual void loadOptionsScene(SDL_Renderer* Renderer);
    virtual void loadElement(SDL_Renderer* Renderer, string messageText, int x, int y, int w, int h, string font, int fontSize, int elementIndex);
    virtual void setMessagesNumber(int messagesNo);


    virtual void setRunning(bool);
    virtual bool getRunning();

    virtual void free();

    virtual ~OptionsScene();


};
