// #include "TextScene.h"
#include "GUI.h"
#include "TextScene.h"
#include "Message.h"
#include <fstream>
#include <iostream>
using namespace std;

TextScene::TextScene()
{

}

void TextScene::loadRes(SDL_Renderer* Renderer)
{
  pauseMessage.setColor(255, 255, 255);
  pauseMessage.setText("Game Paused - Meditating", "fonts/witcherfont.ttf", 40, Renderer, "blended");
  randomFactMessage.setColor(255, 255, 255);

  setMessagesNumber(6);

  messagesNo = 6;

  loadElement(Renderer, "Health: ?/100", 30, 30, 100, 30, "fonts/witcherfont.ttf", 30, 0);
  loadElement(Renderer, "Stamina: ?/100", 30, 80, 100, 30, "fonts/witcherfont.ttf", 30, 1);
  loadElement(Renderer, "Jumps: unlimited", 30, 130, 100, 30, "fonts/witcherfont.ttf", 30, 2);
  loadElement(Renderer, "Adrenaline: ?/?", 30, 180, 100, 30, "fonts/witcherfont.ttf", 30, 3);
  loadElement(Renderer, "Level: ?", 30, 180 + 100, 100, 30, "fonts/witcherfont.ttf", 30, 4);
  loadElement(Renderer, "Experience: ?/10", 30, 180 + 150, 100, 30, "fonts/witcherfont.ttf", 30, 5);

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

void TextScene::Init(SDL_Renderer* Renderer)
{
    loadRes(Renderer);
}

void TextScene::checkInput()
{

  SDL_Event ev;

  while(SDL_PollEvent(&ev))
      {
          if(ev.type == SDL_QUIT)
             {
                 cout<<"User pressed 'exit'!";
                 TextScene_running = false;
             }

            if(ev.type == SDL_KEYDOWN)
            {
              switch(ev.key.keysym.sym)
              {
                case SDLK_p:

                cout << "Unpaused!" << endl;

                TextScene_running = false;

                break;
                
                case SDLK_ESCAPE:

                cout<<"User pressed 'escape'!";

                TextScene_running = false;

                break;

                default:
                break;

              }
            }
          }

}

void TextScene::update()
{

}

void TextScene::setMessagesNumber(int messagesNo)
{
  this->messagesNo = messagesNo;
  messagesList = new Message[this->messagesNo];
}


void TextScene::loadElement(SDL_Renderer* Renderer, string messageText, int x, int y, int w, int h, string font, int fontSize, int elementIndex)
{
  messagesList[elementIndex].setColor(255, 255, 255);
  messagesList[elementIndex].setText(messageText, font, fontSize, Renderer, "blended", 640);
  messagesList[elementIndex].setX(x);
  messagesList[elementIndex].setY(y);

}

void TextScene::render(SDL_Renderer* Renderer)
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

void TextScene::loop(SDL_Renderer* Renderer)
{
  while(TextScene_running)
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

void TextScene::loadTextScene(SDL_Renderer* Renderer)
{
    loadRes(Renderer);
    loop(Renderer);
}

TextScene::~TextScene()
{

}

bool TextScene::getRunning()
{
  return TextScene_running;
}

void TextScene::setRunning(bool x)
{
  TextScene_running = x;
}

void TextScene::free()
{

  // delete[] pauseMessage;
  pauseMessage.Free();
  // delete pauseMessage;
  pauseMessageSet = false;
  TextScene_running = false;

  for(int i = 0; i < messagesNo; i++)
    messagesList[i].Free();
  delete [] messagesList;

}
