// #include "PauseScene.h"
#include "GUI.h"
#include "PauseScene.h"
#include "Message.h"

PauseScene::PauseScene()
{

}

void PauseScene::loadRes(SDL_Renderer* Renderer)
{
  pauseMessage.setColor(0, 0, 0);
  pauseMessage.setText("Game Paused - Meditating", "fonts/witcherfont.ttf", 50, Renderer);
}

void PauseScene::Init(SDL_Renderer* Renderer)
{
    loadRes(Renderer);
}


void PauseScene::checkInput()
{

  SDL_Event ev;

  while(SDL_PollEvent(&ev))
      {
          if(ev.type == SDL_QUIT)
             {
                 cout<<"User pressed 'exit'!";
                 PauseScene_running = false;
             }

            if(ev.type == SDL_KEYDOWN)
            {
              switch(ev.key.keysym.sym)
              {
                case SDLK_p:

                cout << "Unpaused!" << endl;

                PauseScene_running = false;

                break;
                
                case SDLK_ESCAPE:

                cout<<"User pressed 'escape'!";

                PauseScene_running = false;

                break;

                default:
                break;

              }
            }
          }

}

void PauseScene::update()
{

}

void PauseScene::render(SDL_Renderer* Renderer)
{
  // SDL_SetRenderDrawColor(Renderer, 0, 80, 100, 100);
  // SDL_RenderClear(Renderer);

  if(!pauseMessageSet)
  {
    pauseMessage.display(320 - 200, 200, 400, 60, Renderer);

    SDL_RenderPresent(Renderer);

    pauseMessageSet = true;
  }

}

void PauseScene::loop(SDL_Renderer* Renderer)
{
  while(PauseScene_running)
  {
     //time
    checkInput();
    update();
    render(Renderer);
    //time
    SDL_Delay(30);
  }

  free();
}

void PauseScene::loadPauseScene(SDL_Renderer* Renderer)
{
    loadRes(Renderer);
    loop(Renderer);
}

PauseScene::~PauseScene()
{

}

bool PauseScene::getRunning()
{
  return PauseScene_running;
}

void PauseScene::setRunning(bool x)
{
  PauseScene_running = x;
}

void PauseScene::free()
{

  // delete[] pauseMessage;
  pauseMessage.Free();
  // delete pauseMessage;
  pauseMessageSet = false;

}
