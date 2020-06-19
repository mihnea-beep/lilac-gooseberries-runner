#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "GUI.h"
#include "Player.h"
using namespace std;


class InventoryScene
{
  bool InventoryScene_running = false;
  bool isOpen = false;
  bool invSet = false;
  Message invMessage;
  Message* optionsMessage;
  string typeInvMessage;
  vector<string> menuMessages;

  vector<string> words;
  vector<string> letters;

  int typePos = 0;
  int fontSize = 30;
  int typeRowPos = 0;
  int inventorySelected = 0;
  int optionsNo = 2;

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

    InventoryScene(); // interface maybe?

    virtual void loadRes(SDL_Renderer* Renderer);
    virtual void Init(SDL_Renderer* Renderer);
    virtual void checkInput();
    virtual void update();
    virtual void render(SDL_Renderer*);
    virtual void loop(SDL_Renderer* Renderer);
    virtual void loadInventoryScene(SDL_Renderer* Renderer);

    virtual void setRunning(bool);
    virtual bool getRunning();

    virtual void free();

    virtual ~InventoryScene();


};
