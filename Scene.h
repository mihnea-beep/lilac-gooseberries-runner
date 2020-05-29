#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL_mixer.h>
#include "Rect.h"
#include "Player.h"
//#include "GUI.h"
using namespace std;


class Scene
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

  int tick = 0;

  unsigned int timeA = 3000;

  string geraltImage = "Assets/geralt/geralt_pixel_running0.png";
  string lavenderImage = "Assets/geralt/lavender_pixel.png";
  string drownerImage = "Assets/geralt/drowner.png";
  string gryphonImage = "Assets/geralt/gryphon0.png";



  string resPath = "Assets/geralt/";

  bool pickedUp = false;
  bool damageTaken = false;


  Rect rectangle1;
  vector<Player> characters;
  vector<Player> powerups;
  vector<Player> enemies;

  string soundName = "Assets/geralt/ladder1.wav";
	Mix_Chunk* sound;

  // int result;


  // Player* geralt;




  public:

    Scene();

    virtual void loadRes(SDL_Renderer* Renderer);
    virtual void Init(SDL_Renderer* Renderer);
    virtual void checkInput();
    virtual void update();
    virtual void render(SDL_Renderer*);
    virtual void loop(SDL_Renderer* Renderer);
    virtual void loadScene(SDL_Renderer* Renderer);

    virtual void draw(Player& p, SDL_Renderer* Renderer);

    virtual void animate(Player&p, int frames_no, string frame_name, SDL_Renderer* Renderer);

    virtual void setRunning(bool);
    virtual bool getRunning();

    virtual void free();

    virtual ~Scene();


};
