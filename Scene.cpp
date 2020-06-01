#include "Scene.h"
//#include "GUI.h"
#include "Message.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>
using namespace std;

Scene::Scene()
{

}

void Scene::loadRes(SDL_Renderer* Renderer)
{
  IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
  TTF_Init();
  
  // rectangle1.setDim(320, 240, 20, 20);

  Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
	Mix_AllocateChannels(4);

  soundNames.push_back("Assets/geralt/ladder1.wav");
  soundNames.push_back("Assets/geralt/damage1.wav"); //witcher-fck.wav"); // too NSFW? or boring?
  soundNames.push_back("Assets/geralt/witcher_levelup.wav");
  soundNames.push_back("Assets/geralt/witcher-fck.wav");
  soundNames.push_back("Assets/geralt/sword1.wav");


	sounds.push_back(Mix_LoadWAV(soundNames[0].c_str()));
	sounds.push_back(Mix_LoadWAV(soundNames[1].c_str()));
	sounds.push_back(Mix_LoadWAV(soundNames[2].c_str()));
	sounds.push_back(Mix_LoadWAV(soundNames[3].c_str()));
	sounds.push_back(Mix_LoadWAV(soundNames[4].c_str()));

  lilacAmount.setColor(100, 100, 100);
  lilacAmount.setText(to_string(score), "fonts/witcherfont.ttf", 30, Renderer);


  lilac.setColor(100, 100, 100);
  lilac.setText("Lilac", "fonts/witcherfont.ttf", 30, Renderer);

  speed = 4;

  signsNo = 2;
  powerupsNo = 3;
  enemiesNo = 2;
  starsNo = 500;
  bgElementsNo = 1;

  sign = new Player[signsNo];
  powerups = new Player[powerupsNo];
  enemies = new Player[enemiesNo];
  background = new Player[bgElementsNo];
  stars = new SDL_Point[starsNo];

  for(int i = 0; i < bgElementsNo; i++)
  {
    background[i].setH(84);
    background[i].setW(84);
    background[i].setPos(500, 60);
  }

  background[0].setImage(moonImage, Renderer);

  // signs

  for(int i = 0; i < signsNo; i++)
  {
    sign[i].setH(84);
    sign[i].setW(84);
    sign[i].setPos(20, 20);
  }

  sign[0].setImage(signsImage, Renderer);
  sign[1].setImage(resPath + "Quen.png", Renderer);

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

                cout << "JUMP" << endl;

                jumping = true;

                jumpHeightSet = false;

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

  // cout << "y: " << rectangle1.getY() << endl;

  tick++;
  //  if(powerups[0].getTexture() == NULL)
    // cout << "AAAAAA";
  
  
  pickedUp = false;

  //cout << "y: " << characters[0].getY() << endl;

  if(jumping)
  {
    if(!jumpHeightSet)
      {
        jumpHeight = characters[0].getY() - 180;//rectangle1.getY() - 180;
        jumpHeightSet = true;
        jumpDecrease = false;
        speed = 18;
      }

    // speed = speed - 0.4;

    characters[0].setY(characters[0].getY() - speed);

    if((characters[0].getY() - jumpHeight) < 60)
      {
        if(!jumpDecrease)
          {
            speed = speed - 2;
            jumpDecrease = true;
          } 
      }

      // extraSpeed = (float)speed - 0.5;
      speed --;
      
      // speed = (float)speed - extraSpeed;


    if(characters[0].getY() <= jumpHeight)
    {
      jumpHeightSet = false;
      jumping = false;
      // speed = 18;
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
    // speed = 4;
  }

  if(characters[0].getY() <= 0)
  {
    
  }

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

  // cout << speed;
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
            cout << "Monsters slain: " << monsterScore << endl;
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


      if(landed)
        if(isMelee)
          if(selectedSign == Quen)
            if(!signTimerActivated)
              {
                // if(enemies[i].getX() -  rectangle1.getX() <= rectangle1.getW())
                if(enemies[i].isColliding(rectangle1.getX(), rectangle1.getY(), 150))
                    {
                      if(enemies[i].getX() >= rectangle1.getX())
                        enemies[i].setX(enemies[i].getX() + 4);
                      else
                      {
                        enemies[i].setX(enemies[i].getX() - 1);
                      }
                      
                      cout << "DISTANCE" << endl;
                    }
                    
              }

      if(enemies[i].getX() <= -120 || characters[0].isColliding(enemies[i])) // type
        if(i % 2)
          enemies[i].setPos(rand() % characters[0].getX() + 640 + 100, 480 - enemies[i].getH());
        else
        {
          enemies[i].setPos(rand() % characters[0].getX() + 1440 + 100, 480 - enemies[i].getH());
        }   

        enemies[i].setX(enemies[i].getX() - 3);
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

void Scene::render(SDL_Renderer* Renderer)    // TODO: if health is low && killing monsters -> no more fk sound! 
{
  // cout << tick << endl;
  SDL_SetRenderDrawColor(Renderer, 78, 64, 78, 1);
  SDL_RenderClear(Renderer); 

  SDL_SetRenderDrawColor(Renderer, 255, 255, 20, 0);

  // for(int i = 0; i < bgElementsNo; i++)


  for(int i = 0; i < starsNo; i++)
  {
    SDL_RenderDrawPoint(Renderer, stars[i].x, stars[i].y);
  }

  draw(background[0], Renderer);


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

  if(selectedSign == 1 || selectedSign == 0)
    draw(sign[selectedSign], Renderer);

  for(int i = 0; i < characters.size(); i++)
    draw(characters[i], Renderer);

  for(int i = 0; i < enemiesNo; i++)
    draw(enemies[i], Renderer);

  for(int i = 0; i < powerupsNo; i++)
    {
      draw(powerups[i], Renderer);
      // cout << powerups[i].getName() << endl;
    }

  for(int i = 0; i < obstacles.size(); i++)
  {
    obstacles[i].setX(obstacles[i].getX() - 3); 
    obstacles[i].show(Renderer);
  }

    if(isMelee)
  {

    if(signTimerActivated)
    {
      signTimer1 = SDL_GetTicks();
      
      signTimerActivated = false;
    }

    // characters[0].attack(Renderer);
    if(selectedSign == Quen)
      {
        rectangle1.setDim(characters[0].getX() - 10 - rand() % 3, characters[0].getY() - 20 - rand() % 3, 120, 120);
        rectangle1.colorHit(Renderer);

        if(SDL_GetTicks() - signTimer1 >= 13000)
          isMelee = false;

      }
    else
    {
      signTimer1 -= 13000;
      isMelee = false;
    }
    

  }

  for(int i = 0; i < enemiesNo; i++)
    {
      if(enemies[i].getName() == "gryphon")
        animate(enemies[i], 6, resPath + enemies[i].getName(), Renderer);
    }

  animate(characters[0], 7, resPath + "geralt_pixel_running", Renderer);

  if(isMelee)
    if(selectedSign == Quen)
      rectangle1.show(Renderer);

  cout << IMG_GetError() << endl;

  
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

      // cout << 1000 / 16 << endl << endl; 
    //time

  }

}

void Scene::loadScene(SDL_Renderer* Renderer)
{

    loadRes(Renderer);
    loop(Renderer);
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