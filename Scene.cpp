#include "Scene.h"
//#include "GUI.h"


Scene::Scene()
{

}

void Scene::loadRes(SDL_Renderer* Renderer)
{
  rectangle1.setDim(320, 240, 20, 20);

  Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
	Mix_AllocateChannels(4);

	sound = Mix_LoadWAV(soundName.c_str());

  

  speed = 4;

  characters.push_back(Player("Geralt", geraltImage, 100, 200, 84, 84, Renderer));
  powerups.push_back(Player("Lavender", lavenderImage, 100, 200, 84, 84, Renderer));
  // powerups.push_back(Player("Lavender", lavenderImage, 100, 200, 84, 84, Renderer));
  // powerups.push_back(Player("Lavender", lavenderImage, 100, 200, 84, 84, Renderer));
  enemies.push_back(Player("drowner", drownerImage, 100, 100, 120, 100, Renderer));
  enemies.push_back(Player("gryphon", gryphonImage, 100, 100, 120, 100, Renderer));




  characters[0].setPos(300, 480 - 84);
  characters[0].setImage(geraltImage, Renderer);

  if(characters[0].getTexture() == NULL) // doesn't print out anything
    cout << "AAAAAAA";


  for(int i = 0; i < 2; i++)
  {
    obstacles.push_back(Rect(rand() % 640, 480 - 200, 80, 200));
  }

  for(int i = 0; i < powerups.size(); i++)
  {
    powerups[i].setImage(lavenderImage, Renderer);
    powerups[i].setPos(-100, -100);
  }

  for(int i = 0; i < enemies.size(); i++)
  {
    cout << enemies[i].getName() << endl;
     if(enemies[i].getName() == "drowner")
      enemies[i].setImage(drownerImage, Renderer);
    
     if(enemies[i].getName() == "gryphon")
      enemies[i].setImage(gryphonImage, Renderer);

  }

  powerups[0].setPos(500, 200);


}

void Scene::draw(Player &p, SDL_Renderer* Renderer)
{

  SDL_Rect dest;

  dest.x = p.getX();
  dest.y = p.getY();

  dest.w = p.getW();; // player tile size
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
    } 
  }

  

  if(characters[0].getY() >= 480 - characters[0].getH())
  {
    characters[0].setY(480 - characters[0].getH());
    
  }
  else
  {
    characters[0].setY(characters[0].getY() + 1);
  }

  if(characters[0].getY() <= 0)
  {
    
  }

  int obstNo = 0;

  //for(int i = 0; i < powerups.size(); i++)
  {
    if(characters[0].isColliding(powerups[0]))
      {
        pickedUp = true;
        Mix_PlayChannel(-1, sound, 0);
      }
      

    if(powerups[0].getX() <= -100 || characters[0].isColliding(powerups[0]) ) // type
      powerups[0].setPos(rand() % characters[0].getX() + 640 + 100, rand() % 480);
    

      powerups[0].setX(powerups[0].getX() - 3);

  }

  
    if(characters[0].isColliding(enemies[0]))
      damageTaken = true;

    if(enemies[0].getX() <= -100 || characters[0].isColliding(enemies[0]) ) // type
      enemies[0].setPos(rand() % characters[0].getX() + 640 + 100, 480 - enemies[0].getH());
    

      enemies[0].setX(enemies[0].getX() - 3);

  

  

  for(auto it = obstacles.begin(); it != obstacles.end(); it++)
  {
    obstNo++;

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

  // characters[0].setImage(geraltImage - geraltImage.length(), Renderer);

  animate(characters[0], 7, resPath + "geralt_pixel_running", Renderer);

  for(int i = 0; i < enemies.size(); i++)
    animate(enemies[i], enemies[i].getFrames(), resPath + enemies[i].getName(), Renderer);

  SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);


  for(int i = 0; i < characters.size(); i++)
    draw(characters[i], Renderer);

  for(int i = 0; i < enemies.size(); i++)
    draw(enemies[i], Renderer);

  // for(int i = 0; i < powerups.size(); i++)

  draw(powerups[0], Renderer);
  // cout << "Rectangle";


  // rectangle1.show(Renderer);
 // SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);

  for(int i = 0; i < obstacles.size(); i++)
  {
    obstacles[i].setX(obstacles[i].getX() - 3); 
    obstacles[i].show(Renderer);

  }
  
  SDL_RenderPresent(Renderer);

}

void Scene::loop(SDL_Renderer* Renderer)
{


  while(scene_running)
  {
     //time
    int time1 = SDL_GetTicks();

   // cout << "FPS:" << time1 / tick;

    checkInput();
    update();
    render(Renderer);

    int time2 = SDL_GetTicks();

    int delay = 16;

    // delay = delay - (time2 - time1);

    SDL_Delay(delay);

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