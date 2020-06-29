// #include "OptionsScene.h"
#include "GUI.h"
#include "OptionsScene.h"
#include "Message.h"
#include <fstream>
#include <iostream>
using namespace std;

OptionsScene::OptionsScene()
{

}

void OptionsScene::loadRes(SDL_Renderer* Renderer)
{
  pauseMessage.setColor(255, 255, 255);
  pauseMessage.setText("Game Paused - Meditating", "fonts/witcherfont.ttf", 40, Renderer, "blended");
  randomFactMessage.setColor(255, 255, 255);

  // messagesNo = 6;

  int factsNo = 15;

  int randomLine = rand() % factsNo;

  ifstream factsFile("facts.txt");
  string line;
  int lineNo = 0;
  string randomFact;

  if(factsFile.is_open())
    while(getline(factsFile, line))
      {
        lineNo++;

        if(lineNo == randomLine)
        {
          randomFact = line;
          break;
        }
        
      }

      factsFile.close();

      cout << randomFact << endl;

    typeRandomFactMessage = randomFact;
    typePos = 0;

    randomFactMessage.setText(randomFact, "fonts/witcherfont.ttf", 20, Renderer, "blended", 630);

}

void OptionsScene::Init(SDL_Renderer* Renderer)
{
    loadRes(Renderer);
}

void OptionsScene::checkInput()
{

  SDL_Event ev;

  while(SDL_PollEvent(&ev))
      {
          if(ev.type == SDL_QUIT)
             {
                 cout<<"User pressed 'exit'!";
                 OptionsScene_running = false;
             }

            if(ev.type == SDL_KEYDOWN)
            {
              switch(ev.key.keysym.sym)
              {
                case SDLK_f:

                cout << "Fullscreen toggled" << endl;

                fullscreenToggle = true;

                if(!fullscreenMode)
                  fullscreenMode = true;
                else
                {
                  fullscreenMode = false;
                }
                
                case SDLK_p:

                cout << "Unpaused!" << endl;

                OptionsScene_running = false;

                break;
                
                case SDLK_ESCAPE:

                cout<<"User pressed 'escape'!";

                OptionsScene_running = false;

                break;

                default:
                break;

              }
            }
          }

}

void OptionsScene::update()
{
  if(fullscreenToggle)
    if(fullscreenMode)
      SDL_SetWindowFullscreen(getWindow(), SDL_WINDOW_FULLSCREEN);
    else
      SDL_SetWindowFullscreen(getWindow(), 0);
  else
  {
    fullscreenToggle = false;
  }

}

void OptionsScene::setMessagesNumber(int messagesNo)
{
  this->messagesNo = messagesNo;
  messagesList = new Message[this->messagesNo];
}


void OptionsScene::loadElement(SDL_Renderer* Renderer, string messageText, int x, int y, int w, int h, string font, int fontSize, int elementIndex)
{
  messagesList[elementIndex].setColor(255, 255, 255);
  messagesList[elementIndex].setText(messageText, font, fontSize, Renderer, "blended", 640);
  messagesList[elementIndex].setX(x);
  messagesList[elementIndex].setY(y);

}

void OptionsScene::render(SDL_Renderer* Renderer)
{
  // SDL_SetRenderDrawColor(Renderer, 0, 80, 100, 100);
  // SDL_RenderClear(Renderer);

  pauseMessageSet = true;

  SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);

  SDL_RenderClear(Renderer);

  for(int i = 0; i < messagesNo; i++)
  {
    messagesList[i].display(messagesList[i].getX(), messagesList[i].getY(), 300, 630, Renderer, "blended");
  }

  SDL_RenderPresent(Renderer);

  if(!pauseMessageSet)
  {
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);

    pauseMessage.display(320 - 248, 200, 400, 60, Renderer, "blended");
    randomFactMessage.display(10, 300, 630, 30, Renderer, "blended");

    SDL_RenderPresent(Renderer);

    pauseMessageSet = true;
  }

}

void OptionsScene::loop(SDL_Renderer* Renderer)
{
  while(OptionsScene_running)
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

void OptionsScene::loadOptionsScene(SDL_Renderer* Renderer)
{
    loadRes(Renderer);
    loop(Renderer);
}

OptionsScene::~OptionsScene()
{

}

bool OptionsScene::getRunning()
{
  return OptionsScene_running;
}

void OptionsScene::setRunning(bool x)
{
  OptionsScene_running = x;
}

void OptionsScene::free()
{

  // delete[] pauseMessage;
  pauseMessage.Free();
  // delete pauseMessage;
  pauseMessageSet = false;
  OptionsScene_running = false;

  for(int i = 0; i < messagesNo; i++)
    messagesList[i].Free();
  delete [] messagesList;

  messagesNo = 0;

}
