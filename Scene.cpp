#include "Scene.h"
//#include "GUI.h"
#include "Message.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>
#include <fstream>
using namespace std;

Scene::Scene()
{

}

void Scene::loadRes(SDL_Renderer* Renderer)
{
  IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
  TTF_Init();
  // Mix_Init(MIX_INIT_FLAC);
  
  // quenShield.setDim(320, 240, 20, 20);

  Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
	Mix_AllocateChannels(6);

  soundNames.push_back("Assets/geralt/ladder1.wav");
  soundNames.push_back("Assets/geralt/damage1.wav"); //witcher-fck.wav"); // too NSFW? or boring?
  soundNames.push_back("Assets/geralt/witcher_levelup.wav");
  soundNames.push_back("Assets/geralt/witcher-fck.wav");
  soundNames.push_back("Assets/geralt/sword1.wav");
  soundNames.push_back("Assets/geralt/steam.wav");
  soundNames.push_back("Assets/geralt/sand.wav");
  soundNames.push_back("Assets/geralt/geralt_taunt01.wav");

	sounds.push_back(Mix_LoadWAV(soundNames[0].c_str()));
	sounds.push_back(Mix_LoadWAV(soundNames[1].c_str()));
	sounds.push_back(Mix_LoadWAV(soundNames[2].c_str()));
	sounds.push_back(Mix_LoadWAV(soundNames[3].c_str()));
	sounds.push_back(Mix_LoadWAV(soundNames[4].c_str()));
	sounds.push_back(Mix_LoadWAV(soundNames[5].c_str()));
	sounds.push_back(Mix_LoadWAV(soundNames[6].c_str()));
	sounds.push_back(Mix_LoadWAV(soundNames[7].c_str()));

  lilacAmount.setColor(100, 100, 100);
  lilacAmount.setText(to_string(score), "fonts/witcherfont.ttf", 30, Renderer);

  lilac.setColor(100, 100, 100);
  lilac.setText("Lilac", "fonts/witcherfont.ttf", 30, Renderer);

  speed = 4;

  signsNo = 3;
  powerupsNo = 3;
  enemiesNo = 2;
  starsNo = 500; // burn effect instead of stars 
  bgElementsNo = 5; // TODO: add clouds (moving)
  igniBulletsNo = 3;
  gwentCardsNo = 2;

  sign = new Player[signsNo];
  powerups = new Player[powerupsNo];
  enemies = new Player[enemiesNo];
  background = new Player[bgElementsNo];
  stars = new SDL_Point[starsNo];
  igniBullets = new Bullet[igniBulletsNo];
  gwentCards = new Player[gwentCardsNo];

  for(int i = 0; i < bgElementsNo; i++)
  {
    background[i].setH(84);
    background[i].setW(84);
    background[i].setPos(rand() % 600, rand() % 100);
    background[i].setImage("Assets/geralt/cloud01.png", Renderer);
  }

  background[0].setImage("Assets/geralt/cloud01.png", Renderer);

  for(int i = 0; i < gwentCardsNo; i++)
  {
    gwentCards[i].setH(84);
    gwentCards[i].setW(84);
    gwentCards[i].setImage("Assets/geralt/gwent_cards/gwent_yen" + to_string(i) + ".png", Renderer);
    cout << SDL_GetError() << endl;
    // cout << "Assets/geralt/gwent_cards/gwent_yen" + to_string(i) + ".png" << endl;
  }

  gwentCardSet = false;
  gwentCardSpawned = false;
  currentCardNo = 0;

  // signs

  for(int i = 0; i < signsNo; i++)
  {
    sign[i].setH(84);
    sign[i].setW(84);
    sign[i].setPos(20, 20);
  }

  sign[2].setH(100);
  sign[2].setW(80);


  sign[0].setImage(signsImage, Renderer);
  sign[1].setImage(resPath + "Quen.png", Renderer);
  sign[2].setImage(resPath + "Igni.png", Renderer);

  selectedSign = Yrden;

  for(int i = 0; i < igniBulletsNo; i++)
  {
    igniBullets[i].setH(25);
    igniBullets[i].setW(50);
    // igniBullets[i].setX(50);
    // igniBullets[i].setY(50);
    igniBullets[i].setLife(false);
    igniBullets[i].setLaunch(false);
  }

  igniBullets[0].setImage("Assets/geralt/fire/fire0.png", Renderer);
  //  igniBullets[0].setH(20);
  //  igniBullets[0].setW(20);

  // powerups

  for(int i = 0; i < powerupsNo; i++)
  {
    powerups[i].setH(84);
    powerups[i].setW(84);
    powerups[i].setPos(200, 200);
  }

  powerups[0].setImage(lavenderImage, Renderer);
  powerups[1].setImage(lavenderImage2, Renderer);   
  powerups[2].setImage(lavenderImage, Renderer);

  for(int i = 0; i < enemiesNo; i++)
  {
  }

  enemies[0].setH(100);
  enemies[0].setW(100);
  enemies[0].setPos(100, 100);
  enemies[0].setImage(drownerImage, Renderer);

  enemies[1].setH(120);
  enemies[1].setW(100);
  enemies[1].setPos(100, 100);
  enemies[1].setImage(gryphonImage, Renderer);
  enemies[1].setName("gryphon");

  characters.push_back(Player("Geralt", geraltImage, 100, 200, 84, 84, Renderer));

  characters[0].setPos(300, 480 - 84);
  // characters[0].setImage(geraltImage, Renderer);

  if(characters[0].getTexture() == NULL) // doesn't print out anything
    cout << "AAAAAAA";


  for(int i = 0; i < 2; i++)
  {
    obstacles.push_back(Rect(rand() % 640, 480 - 200, 80, 200)); 
  }

  // for(int i = 0; i < powerups.size(); i++)
  // {
  //   powerups[i].setPos(500, 200);

  //   if(powerups[i].getName() == "Lavender")
  //     powerups[i].setImage(lavenderImage, Renderer);

  //   if(powerups[i].getName() == "Lavender2")
  //    powerups[i].setImage("Assets/geralt/lavender_pixel2.png", Renderer); // if replaced by lavenderImage2 or gryphonImage, it bugs out
  //                                                                         // the bug has something to do with signs -- not sure? vectors
  // }

  ofstream outputFile;
  outputFile.open("SDL_IMG_error_log.txt");

  for(int i = 0; i < enemiesNo; i++)
  {
    cout << enemies[i].getName() << endl;
    
     if(enemies[i].getName() == "drowner")
      enemies[i].setImage(drownerImage, Renderer);
    
     if(enemies[i].getName() == "gryphon")
      enemies[i].setImage(gryphonImage, Renderer);

  }

  for(int i = 0; i < starsNo; i++)
  {
    stars[i].x = rand() % 640;
    stars[i].y = rand() % 300; 
  }

  healthBar.setDim(20, 50, 100, 30);


  outputFile << IMG_GetError() << endl;


}

void Scene::draw(Player &p, SDL_Renderer* Renderer)
{

  SDL_Rect dest;

  dest.x = p.getX();
  dest.y = p.getY();

  dest.w = p.getW();// player tile size
  dest.h = p.getH(); //

  SDL_RenderCopy(Renderer, p.getTexture(), NULL, &dest);
}


void Scene::Init(SDL_Renderer* Renderer)
{
    loadRes(Renderer);
}


void Scene::checkInput()
{

  SDL_Event ev;

  while(SDL_PollEvent(&ev))
      {
          if(ev.type == SDL_QUIT)
             {
                 cout<< "User pressed 'exit'!";
                 scene_running = false;
             }

            if(ev.type == SDL_KEYDOWN)
            {
              switch(ev.key.keysym.sym)
              {

                case SDLK_q:

                flags[0] = true;

                break;

                case SDLK_SPACE:

                case SDLK_UP:

                cout << "JUMP" << endl;

                jumping = true;

                jumpHeightSet = false;

                break;
                
                case SDLK_o:

                cout << "Paused" << endl;

                regularPause.setRunning(true);

                break;

                case SDLK_p:

                cout << "Paused" << endl;

                Pause.setRunning(true);

                break;

               case SDLK_i:

               cout << "Inventory" << endl;

               Inventory.setRunning(true);

               break; 
               
               
                case SDLK_s:

                score++;

                break;

                case SDLK_1:

                selectedSign = Yrden;
                  // cout <<  signs[selectedSign].getName() << endl;

                break;

                case SDLK_2:

                selectedSign = Quen;
                // cout << signs[selectedSign].getName() << endl;
                
                break;

                case SDLK_3:

                selectedSign = Igni;

                break;

                case SDLK_4:

                // selectedSign = Aard;

                break;
                
                case SDLK_5:

                // selectedSign = 5;

                break;
                
                case SDLK_6:

                // selectedSign = 6;

                break;
                                
                case SDLK_a:

                isMelee = true;
                signTimerActivated = true;

                break;

                case SDLK_ESCAPE:

                cout << "User pressed 'escape'!";

                scene_running = false;

                break;

                default:
                break;

              }
            }
          }

}

void Scene::update()
{

  tick++;

  pickedUp = false;

  // character movement

  if(jumping)
  {
    if(!jumpHeightSet)
      {
        jumpHeight = characters[0].getY() - 180;//quenShield.getY() - 180;
        jumpHeightSet = true;
        jumpDecrease = false;
        speed = 18;
      }

    characters[0].setY(characters[0].getY() - speed);

    if((characters[0].getY() - jumpHeight) < 60)
      {
        if(!jumpDecrease)
          {
            speed = speed - 2;
            jumpDecrease = true;
          } 
      }

      speed --;

    if(characters[0].getY() <= jumpHeight)
    {
      jumpHeightSet = false;
      jumping = false;
    } 
  }

  
  if(characters[0].getY() >= 480 - characters[0].getH())
  {
    characters[0].setY(480 - characters[0].getH());
    landed = true;
    
  }
  else
  {
    characters[0].setY(characters[0].getY() + 1);
    landed = false;
  }

  if(characters[0].getY() <= 0)
  {
    
  }

  // powerups collisions

  for(int i = 0; i < powerupsNo; i++)
  {
    if(characters[0].isColliding(powerups[i]))
      {
        pickedUp = true;
        cout << "Collected powerup!\n";
        Mix_PlayChannel(-1, sounds[0], 0);
        score++;
        cout << "Lilac: " << score << endl;

        if(score % 10 == 0)
          Mix_PlayChannel(-1, sounds[2], 0);
      }
      

    if(powerups[i].getX() <= -100 || characters[0].isColliding(powerups[i]) ) // type
      powerups[i].setPos(rand() % characters[0].getX() + 640 + 100 + 20, rand() % 400 + 50);
    

      powerups[i].setX(powerups[i].getX() - 3);

  }

  if(gwentCardSpawned)
   {
     gwentCards[currentCardNo].setX(gwentCards[currentCardNo].getX() - 3);

     if(characters[0].isColliding(characters[0].getW() / 2 - 20, characters[0].getH() / 2 + 40, gwentCards[currentCardNo].getX() + gwentCards[currentCardNo].getW() / 2, gwentCards[currentCardNo].getY() + gwentCards[currentCardNo].getH() / 2, 70))
       {
         gwentCardSpawned = false;
         Mix_PlayChannel(-1, sounds[7], 0);
        //  currentCardNo++;
       }

     if(gwentCards[currentCardNo].getX() <= -200)
      gwentCardSpawned = false;
   }

    // enemies collision
    for(int i = 0; i < enemiesNo; i++)
    {
        if(characters[0].isColliding(enemies[i]))
        { 
          // if(characters[0].getY() - characters[0].getH() == enemies[i].getY())
          // if(speed < 0)
          if(jumpHeightSet)
            {
              // jumping = true;
              // jumpHeightSet = false;
            }

          if(!landed)
          {
            jumping = true;
            jumpHeightSet = false;
            monsterScore++;
            cout << "Silver boots are for monsters!" << endl;
            cout << "Slain monsters: " << monsterScore << endl;
            Mix_PlayChannel(-1, sounds[4], 0);
          }
          else
          { 
            
              damageTaken = true;
            
            cout << "Ouch!" << endl;
            HP --;
            cout << "Health points: " << HP << endl;
             if(HP % 10 == 0)
            {
              Mix_PlayChannel(-1, sounds[3], 0);
            }

            else
            {
              Mix_PlayChannel(-1, sounds[1], 0);
            }
          
          }

        }

        bool enemyHit = false;

      if(igniBullets[0].lifestatus())
      {
        SDL_Renderer* rnd = NULL;

      //  if(igniBullets[0].isColliding(enemies[i].getX() + 35, enemies[i].getY() + enemies[i].getH() / 2, 20))
        if(igniBullets[0].isColliding(0, 20, enemies[i].getX() + enemies[i].getW() / 2 + 20, enemies[i].getY() + enemies[i].getH() / 2, 50))
      
      // if(enemies[i].isColliding(igniBullets[i].getX(), igniBullets[i].getY()))
        {
          enemyHit = true;
          Mix_PlayChannel(-1, sounds[6], 0);
          monsterScore++;
          cout << "Monster burnt!" << endl;
          cout << "Slain monsters: " << monsterScore << endl;
          // igniBullets[0].setLife(false);
          // SDL_Delay(1000);
        }
      }

      if(landed)
        // if(isMelee)
          if(activeSign == Quen)
            // if(!signTimerActivated)
              {
                // if(enemies[i].getX() -  quenShield.getX() <= quenShield.getW())
                if(enemies[i].isColliding(quenShield.getX(), quenShield.getY(), 150))
                    {
                      if(enemies[i].getX() >= quenShield.getX())
                        enemies[i].setX(enemies[i].getX() + 4);
                      else
                      {
                        enemies[i].setX(enemies[i].getX() - 1);
                      }
                      // cout << "DISTANCE" << endl;
                    }
                    
              }

      if(enemies[i].getX() <= -120 || characters[0].isColliding(enemies[i]) || enemyHit) // type
        if(i % 2)
          enemies[i].setPos(rand() % characters[0].getX() + 640 + 100, 480 - enemies[i].getH());
        else
        {
          enemies[i].setPos(rand() % characters[0].getX() + 1440 + 100, 480 - enemies[i].getH());
        }   

        enemies[i].setX(enemies[i].getX() - 3);
    }

    if(cloudTimerActivated == true) // clouds movement

     for(int i = 0; i < bgElementsNo; i++)
  {
    {

      background[i].setX(background[i].getX() - 2);
      cloudTimer = SDL_GetTicks();
      cloudTimerActivated = false;
    }
    
    if(background[i].getX() + 200 <= 0)
      {
          background[i].setX(rand() % 640 + 640 + 30);
          background[i].setY(rand() % 100 + 20);
      }
  }

      if(SDL_GetTicks() - cloudTimer >= 10)
    {
      cloudTimerActivated = true;
    }

    // cout << "Gwent card spawned: " << gwentCardSpawned << endl;
    // cout << "Gwent card set: " << gwentCardSet << endl;


    if(!gwentCardSpawned)
      // if(!gwentCardSet)
        if(score != 0)
         if(score % 51 == 0)
      {
        currentCardNo = rand() % 2;
        // gwentCards[0].setImage 
        gwentCards[currentCardNo].setX(rand() % 640 + 640);
        gwentCards[currentCardNo].setY(rand() % 400 + 30);
        // gwentCardSet = true;
        gwentCardSpawned = true;

      }


  for(auto it = obstacles.begin(); it != obstacles.end(); it++)
  {

    if((it->getX() + 105) <= 0)
    {
      int xPos = rand() % 1000 + 640;

        it->setX(rand() % characters[0].getX() + characters[0].getW() + 5 + 640);
        it->setY(rand() % 100 - 480); 
       
    }
  }
  

  for(int i = 0; i < 6; i++)
  {
    flags[i] = false;
  }

} 

void Scene::render(SDL_Renderer* Renderer)
{

  SDL_SetRenderDrawColor(Renderer, 78, 64, 78, 1);
  SDL_RenderClear(Renderer); 

  SDL_SetRenderDrawColor(Renderer, 255, 255, 20, 0);

  // stars 

  for(int i = 0; i < starsNo; i++)
  {
    // SDL_RenderDrawPoint(Renderer, stars[i].x, stars[i].y);
  }

  // clouds + background elements

  for(int i = 0; i < bgElementsNo; i++)
   draw(background[i], Renderer);

  // lilac score text

  lilac.display(640 - 160, 20, 100, 30, Renderer);

  if(score >= 10)
    {
      lilacAmount.setText(to_string(score), "fonts/witcherfont.ttf", 30, Renderer);
      lilacAmount.display(640 - 160 + 100, 20, 50, 30, Renderer);

    }
    else
    {
      lilacAmount.setText(to_string(score), "fonts/witcherfont.ttf", 20, Renderer);
      lilacAmount.display(640 - 160 + 100, 20, 30, 30, Renderer);
    }

  lilac.setText("Lilac: ", "fonts/witcherfont.ttf", 30, Renderer);

  SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);

  // signs

  if(selectedSign == 1 || selectedSign == 0 || selectedSign == 2)
    draw(sign[selectedSign], Renderer);

  for(int i = 0; i < characters.size(); i++)
    draw(characters[i], Renderer);

  for(int i = 0; i < enemiesNo; i++)
    draw(enemies[i], Renderer);

  for(int i = 0; i < powerupsNo; i++)
    {
      draw(powerups[i], Renderer);
    }  

    if(gwentCardSpawned)
      {
        draw(gwentCards[currentCardNo], Renderer);
        // characters[0].isColliding(characters[0].getW() / 2 - 40, characters[0].getH() / 2 + 30, gwentCards[0].getX() + gwentCards[0].getW() / 2, gwentCards[0].getY() + gwentCards[0].getH() / 2, 75, Renderer);

        // gwentCardSpawned = false;
      }


  // for(int i = 0; i < obstacles.size(); i++) // parallaxing TODO: background
  // {
  //   obstacles[i].setX(obstacles[i].getX() - 3); 
  //   obstacles[i].show(Renderer);
  // }

  // Melee state (activating signs) 

    if(isMelee)
  {
    // Yrden
    if(selectedSign == Yrden && isMelee)
    {
      cout << "Yrden selected" << endl;
      activeSign = Yrden;
      isMelee = false;
    }

    // Igni
    if( (selectedSign == Igni) && (isMelee) )
    {
      cout << "Igni selected" << endl;
      
      activeSign = Igni;

      isMelee = false;
    }

    // Quen
    if( (selectedSign == Quen) && (isMelee) )
      {

          activeSign = Quen;
          isMelee = false;
      }
    else
    {
      // signTimer1 -= 13000;
      isMelee = false;
    }

  }

  // enemies
  for(int i = 0; i < enemiesNo; i++)
    {
      if(enemies[i].getName() == "gryphon")
        animate(enemies[i], 6, resPath + enemies[i].getName(), Renderer);
        // cout << SDL_GetError() << endl; invalid texture sometimes
    }

  animate(characters[0], 7, resPath + "geralt_pixel_running", Renderer);

  // Yrden trap logic

  if(activeSign == Yrden)
  {
    activeSign = noSign;
  }

   // Igni bullet logic
  
  if(activeSign == Igni)
    {
      if(!igniBullets[0].lifestatus())
        {
          igniBullets[0].setLaunch(true); // bullet mechanic
          igniBullets[0].setX(characters[0].getX() + 30);
          igniBullets[0].setY(characters[0].getY() + 20);
        }
    
       activeSign = noSign;
    }

  if(igniBullets[0].getLaunch())    // igni sound
  {
   Mix_PlayChannelTimed(-1, sounds[5], 0, 2000);
   igniBullets[0].setLaunch(false);
   igniBullets[0].setLife(true); 
  }

  

  if(igniBullets[0].lifestatus())
  {
    draw(igniBullets[0], Renderer);

    // igniBullets[0].isColliding(0, 20, enemies[0].getX() + enemies[0].getW() / 2, enemies[0].getY() + enemies[0].getH() / 2, 20, Renderer);
    
    // igniBullets[0].isColliding(0, 20, enemies[1].getX() + enemies[1].getW() / 2, enemies[1].getY() + enemies[1].getH() / 2, 20, Renderer);

    animate(igniBullets[0], 7, "Assets/geralt/fire/fire", Renderer);

    // cout << igniBullets[0].isColliding(enemies[1].getX(), enemies[1].getY(), Renderer);

    igniBullets[0].setX(igniBullets[0].getX() + 5);

    if(igniBullets[0].getX() >= 640)
    {
      igniBullets[0].setLife(false);
    }
  }

  // Quen shield logic

  if(activeSign == Quen)
     {
      if( (signTimerActivated) )
        {
          cout << "Quen timer activated" << endl;
            
          signTimer1 = SDL_GetTicks();
            
          signTimerActivated = false;
        }

      quenShield.setDim(characters[0].getX() - 10 - rand() % 3, characters[0].getY() - 20 - rand() % 3, 120, 120); // separate the shield from activeSign?
      quenShield.colorHit(Renderer);

       if(SDL_GetTicks() - signTimer1 >= 13000)
         activeSign = noSign;

      quenShield.show(Renderer);
    }

  // cout << IMG_GetError() << endl;

  SDL_RenderPresent(Renderer);

}

void Scene::loop(SDL_Renderer* Renderer)
{

  while(scene_running)
  {
     //time
    time1 = SDL_GetTicks();

   // cout << "FPS:" << time1 / tick;

    checkInput();
    update();
    render(Renderer);

    time2 = SDL_GetTicks();

    delay = 16;

    // cout << time2 - time1 << endl;

    delay = delay - (time2 - time1);

    if(delay > 16)
       {
         SDL_Delay(0);
        //  cout << "0 delay" << endl;
       }

    if(delay < 16)
     if(delay < 0)
     {
         SDL_Delay(0);
        //  cout << "0 delay" << endl;
     }
      else
      {
       SDL_Delay(delay);
      //  cout << delay << endl;
      }
      // check if pause
      checkPause(Renderer);

      checkInventory(Renderer);

      checkMenu(Renderer);

      // cout << 1000 / 16 << endl << endl; 
    //time

  }

}

void Scene::loadScene(SDL_Renderer* Renderer)
{

    loadRes(Renderer);
    loop(Renderer);
}

void Scene::checkPause(SDL_Renderer* Renderer)
{
  // bool scenePaused = true;

  // if(scenePaused) // while scenePaused
  // {
    // SDL_Delay(1000);
    // pause screen - text and input
    // cout << "PAUSE" << endl; 
    // Pause.setRunning(true);
    if(Pause.getRunning() == true)
     Pause.loadTextScene(Renderer);
  // }
}

void Scene::checkMenu(SDL_Renderer* Renderer)
{

    if(regularPause.getRunning() == true)
     regularPause.loadPauseScene(Renderer);

}


void Scene::checkInventory(SDL_Renderer* Renderer)
{
  if(Inventory.getRunning())
    Inventory.loadInventoryScene(Renderer);
}

void Scene::animate(Player& p, int frames_no, string frame_name, SDL_Renderer* Renderer)
{
    vector<string> frames(frames_no); //amount of frames can be set in player?

    int i;

    for(i = 0; i < frames_no; i++)
        {

          frames[i] = frame_name + to_string(i) + ".png";
          // cout << frames[i] << endl;
        }


    //  p.setImage(frames[i], Renderer);


      // cout << "TICKS: " << tick << endl;
      p.setImage(frames[(tick / 4) % (frames_no)], Renderer); // /10
}

Scene::~Scene()
{
  for(int i = 0; i < sounds.size(); i++)
    Mix_FreeChunk(sounds[i]);

  for(int i = 0; i < characters.size(); i++)
    characters[i].Free();

  for(int i = 0; i < enemiesNo; i++)
    enemies[i].Free();

  for(int i = 0; i < powerupsNo; i++)
    powerups[i].Free();

}

bool Scene::getRunning()
{
  return scene_running;
}

void Scene::setRunning(bool x)
{
  scene_running = x;
}

void Scene::free()
{

}