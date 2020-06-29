#include "GameScene.h"
#include "GUI.h"

GameScene::GameScene()
{

}

void GameScene::loadRes(SDL_Renderer* Renderer)
{

}

void GameScene::Init(SDL_Renderer* Renderer)
{
    loadRes(Renderer);
}

SDL_Window* GameScene::getWindow()
{
  return sceneWindow;
}

void GameScene::setWindow(SDL_Window* window)
{
  this->sceneWindow = window;
}

void GameScene::checkInput()
{

  SDL_Event ev;

  while(SDL_PollEvent(&ev))
      {
          if(ev.type == SDL_QUIT)
             {
                 cout<<"User pressed 'exit'!";
                 GameScene_running = false;
             }

            if(ev.type == SDL_KEYDOWN)
            {
              switch(ev.key.keysym.sym)
              {
                case SDLK_ESCAPE:

                cout<<"User pressed 'escape'!";

                GameScene_running = false;

                break;

                default:
                break;

              }
            }
          }

}

void GameScene::update()
{

}

void GameScene::render(SDL_Renderer* Renderer)
{
  SDL_SetRenderDrawColor(Renderer, 0, 80, 100, 100);
  SDL_RenderClear(Renderer);


  SDL_RenderPresent(Renderer);

}

void GameScene::loop(SDL_Renderer* Renderer)
{
  while(GameScene_running)
  {
     //time
    checkInput();
    update();
    render(Renderer);
    //time

  }

}

void GameScene::loadGameScene(SDL_Renderer* Renderer)
{

    loadRes(Renderer);
    loop(Renderer);
}

GameScene::~GameScene()
{

}

bool GameScene::getRunning()
{
  return GameScene_running;
}

void GameScene::setRunning(bool x)
{
  GameScene_running = x;
}

void GameScene::free()
{
  if(sceneWindow != NULL)
    SDL_DestroyWindow(sceneWindow);

}
