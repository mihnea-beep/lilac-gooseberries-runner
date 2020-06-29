#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL_mixer.h>
#include "Rect.h"
#include "Player.h"
#include "Message.h"
#include "Bullet.h"
#include "PauseScene.h"
#include "InventoryScene.h"
#include "TextScene.h"
#include "MenuScene.h"
#include "GameScene.h"
//#include "GUI.h"
using namespace std;

class Scene: public GameScene
{
  bool scene_running = false;
  bool flags[10];
  int result;
  int speed;
  float extraSpeed;

  bool jumping = false;
  int jumpHeight;
  bool jumpHeightSet;
  bool jumpDecrease = false;

  vector<Rect>obstacles;
  Rect healthBar;

  int tick = 0;

  unsigned int timeA = 3000;
  
  uint32_t cloudTimer;

  bool cloudTimerActivated = true;
  
  uint32_t signTimer1;
  uint32_t signTimer2;

  bool signTimerActivated = false;

  enum signType
  {
    Yrden,
    Quen,
    Igni,
    Aard,
    Axii,
    noSign
  };

  signType selectedSign;
  signType activeSign = noSign;

  uint32_t time1;
  uint32_t time2;
  uint32_t delay;

  // unsigned int selectedSign = 0;

  string geraltImage = "Assets/geralt/geralt_pixel_running0.png";

  string lavenderImage = "Assets/geralt/lavender_pixel.png";
  string lavenderImage2 = "Assets/geralt/lavender_pixel2.png";
  
  string drownerImage = "Assets/geralt/drowner.png";
  string gryphonImage = "Assets/geralt/gryphon0.png";

  string signsImage = "Assets/geralt/Yrden.png";

  string moonImage = "Assets/geralt/moon02.png";

  // string signsImage2 = "Assets/geralt/Quen.png";

  string resPath = "Assets/geralt/";

  bool pickedUp = false;
  bool damageTaken = false;
  bool isMelee = false;
  bool screenShake = false;
  bool landed = false;
  bool gwentCardSpawned = false;
  bool gwentCardSet = false;
  bool menuActive = false;

  Rect quenShield;
  vector<Player> characters;

  //GUI
  vector<Player> signs;
  
  int powerupsNo;
  int signsNo;
  int enemiesNo;
  int starsNo;
  int bgElementsNo;
  int igniBulletsNo;
  int gwentCardsNo;
  int currentCardNo;
  
  Player* sign;
  Player* powerups;
  Player* enemies;
  Player* background;
  Player* gwentCards;
  SDL_Point* stars;
  Bullet* igniBullets;

  vector<string> soundNames; // = "Assets/geralt/ladder1.wav";
	// Mix_Chunk* sound;

  vector<Mix_Chunk*> sounds;

  int score = 0; // temporary no GUI
  int monsterScore = 0;
  int HP = 99;

  Message lilac;
  Message lilacAmount;

  PauseScene Pause;
  // PauseScene regularPause;
  
  InventoryScene Inventory;

  MenuScene Menu;


  public:

    Scene();

    virtual void loadRes(SDL_Renderer* Renderer);
    virtual void Init(SDL_Renderer* Renderer);
    virtual void checkInput();
    virtual void update();
    virtual void render(SDL_Renderer*);
    virtual void loop(SDL_Renderer* Renderer);
    virtual void loadScene(SDL_Renderer* Renderer);
    virtual void checkPause(SDL_Renderer* Renderer);
    virtual void checkInventory(SDL_Renderer* Renderer);
    virtual void checkMenu(SDL_Renderer* Renderer);
    virtual void draw(Player& p, SDL_Renderer* Renderer);

    virtual void animate(Player&p, int frames_no, string frame_name, SDL_Renderer* Renderer);

    virtual void setRunning(bool);
    virtual bool getRunning();

    virtual void free();

    virtual ~Scene();


};