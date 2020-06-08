#include "InventoryScene.h"
#include "GUI.h"

InventoryScene::InventoryScene()
{

}

void InventoryScene::loadRes(SDL_Renderer* Renderer)
{
  invMessage.setColor(0, 0, 0);
  invMessage.setText("Inventory", "fonts/witcherfont.ttf", 30, Renderer, "blended", 640);
}

void InventoryScene::Init(SDL_Renderer* Renderer)
{
    loadRes(Renderer);
}


void InventoryScene::checkInput()
{

  SDL_Event ev;

  while(SDL_PollEvent(&ev))
      {
          if(ev.type == SDL_QUIT)
             {
                 cout<<"User pressed 'exit'!";
                 InventoryScene_running = false;
             }

            if(ev.type == SDL_KEYDOWN)
            {
              switch(ev.key.keysym.sym)
              {

                case SDLK_i:

                cout << "Inventory exited" << endl;

                InventoryScene_running = false;

                break;

                case SDLK_ESCAPE:

                cout<<"User pressed 'escape'!";

                InventoryScene_running = false;

                break;

                default:
                break;

              }
            }
          }

}

void InventoryScene::update()
{

}

void InventoryScene::render(SDL_Renderer* Renderer)
{
  // SDL_SetRenderDrawColor(Renderer, 0, 80, 100, 100);
  // SDL_RenderClear(Renderer);

  invMessage.display(200, 200, 300, 300, Renderer, "blended");


  SDL_RenderPresent(Renderer);

}

void InventoryScene::loop(SDL_Renderer* Renderer)
{
  while(InventoryScene_running)
  {
     //time
    checkInput();
    update();
    render(Renderer);

    SDL_Delay(33);
    //time

  }

}

void InventoryScene::loadInventoryScene(SDL_Renderer* Renderer)
{

    loadRes(Renderer);
    loop(Renderer);
}

InventoryScene::~InventoryScene()
{

}

bool InventoryScene::getRunning()
{
  return InventoryScene_running;
}

void InventoryScene::setRunning(bool x)
{
  InventoryScene_running = x;
}

void InventoryScene::free()
{
  invMessage.Free();
}
