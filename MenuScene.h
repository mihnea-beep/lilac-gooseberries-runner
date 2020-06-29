#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "GUI.h"
#include "Player.h"
#include "TextScene.h"
#include "GameScene.h"
#include "OptionsScene.h"
using namespace std;


class MenuScene: public GameScene
{
  bool MenuScene_running = false;
  bool isOpen = false;
  bool invSet = false;
  Message invMessage;
  Message* optionsMessage;
  string typeInvMessage;
  vector<string> menuMessages;
  
  OptionsScene Options;


  vector<string> words;
  vector<string> letters;

  int typePos = 0;
  int fontSize = 30;
  int typeRowPos = 0;
  int inventorySelected = 0;
  int optionsNo = 2;
  bool selectOption = false;
  bool exitGame = false;

  enum menuOptions
  {
    inventoryOption,
    statsOption
  };

  menuOptions menuOptions;

  Player* geralt;
  
  int maxItemsNo = 5;

  vector<Player> items[5];

  public:

    MenuScene(); // interface maybe?

    virtual void loadRes(SDL_Renderer* Renderer);
    virtual void Init(SDL_Renderer* Renderer);
    virtual void checkInput();
    virtual void update();
    virtual void render(SDL_Renderer*);
    virtual void loop(SDL_Renderer* Renderer);
    virtual void loadMenuScene(SDL_Renderer* Renderer);
    virtual void checkMenu(SDL_Renderer* Renderer);
    virtual bool getExit();


    virtual void setRunning(bool);
    virtual bool getRunning();

    virtual void free();

    virtual ~MenuScene();


};
