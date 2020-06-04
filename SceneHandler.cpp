#include "SceneHandler.h"
#include "GUI.h"

SceneHandler::SceneHandler()
{

}

void SceneHandler::loadRes(SDL_Renderer* Renderer)
{

}

void SceneHandler::Init(SDL_Renderer* Renderer)
{
    loadRes(Renderer);
}


void SceneHandler::checkInput()
{

  SDL_Event ev;

  while(SDL_PollEvent(&ev))
      {
          if(ev.type == SDL_QUIT)
             {
                 cout<<"User pressed 'exit'!";
                 SceneHandler_running = false;
             }

            if(ev.type == SDL_KEYDOWN)
            {
              switch(ev.key.keysym.sym)
              {
                case SDLK_ESCAPE:

                cout<<"User pressed 'escape'!";

                SceneHandler_running = false;

                break;

                default:
                break;

              }
            }
          }

}

void SceneHandler::update()
{

}

void SceneHandler::render(SDL_Renderer* Renderer)
{
  SDL_SetRenderDrawColor(Renderer, 0, 80, 100, 100);
  SDL_RenderClear(Renderer);


  SDL_RenderPresent(Renderer);

}

void SceneHandler::loop(SDL_Renderer* Renderer)
{
  while(SceneHandler_running)
  {
     //time
    checkInput();
    update();
    render(Renderer);
    //time

  }

}

void SceneHandler::loadSceneHandler(SDL_Renderer* Renderer)
{

    loadRes(Renderer);
    loop(Renderer);
}

SceneHandler::~SceneHandler()
{

}

bool SceneHandler::getRunning()
{
  return SceneHandler_running;
}

void SceneHandler::setRunning(bool x)
{
  SceneHandler_running = x;
}

void SceneHandler::free()
{

}
