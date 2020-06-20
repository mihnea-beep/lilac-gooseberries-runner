#include "InventoryScene.h"
#include "GUI.h"

InventoryScene::InventoryScene()
{

}

void InventoryScene::loadRes(SDL_Renderer* Renderer)
{
  TTF_Init();

  optionsMessage = new Message[optionsNo];
  menuOptions = statsOption;

  invMessage.setColor(255, 255, 255);
  invMessage.setText("Inventory", "fonts/witcherfont.ttf", 30, Renderer, "blended", 640);

  optionsMessage[0].setColor(255, 255, 255);
  optionsMessage[0].setText("Character", "fonts/witcherfont.ttf", 30, Renderer, "blended", 640);
  optionsMessage[1].setText("Signs", "fonts/witcherfont.ttf", 30, Renderer, "blended", 640);
  // optionsMessage[2].setText("Shop", "fonts/witcherfont.ttf", 30, Renderer, "blended", 640);



  // menuOptions = inventoryOption;

  geralt = new Player[1];

  typeInvMessage = "Inventory";

  menuMessages.push_back(typeInvMessage);
  invMessage.setText("");

  string sentence = typeInvMessage;
  string word;

  for(int i = 0; i < sentence.size(); i++)
  {

    string letter = "";

    if(sentence.at(i) == ' ')
      {
        cout << word << endl;
        words.push_back(word);
        letter = "";
        word = "";
        letter = sentence.at(i);
        letters.push_back(letter);
      }
    else
    {
      letter = sentence.at(i);
      letters.push_back(letter);
      word = word + sentence.at(i);
    }
    // if letter != "", add letter
    letter = "";
  }

  // geralt[0].setImage

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
                
                case SDLK_UP:

                inventorySelected--;

                break;
                
                case SDLK_DOWN:

                inventorySelected++;

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
  // SDL_SetRenderDrawColor(Renderer, 68, 70, 68, 0);
  SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
  SDL_RenderClear(Renderer);
  SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
  // SDL_RenderDrawLine(Renderer, 360 + 250, 0, 360 + 250, 480);

  // if(typePos < typeInvMessage.size() + 20)
  if((invMessage.getText()).size() < letters.size())
    {
      string pause = "";

      if(typePos >= 4)
        {
          // pause = " ";
          // typePos = 0;
        }
      if(typeRowPos >= 10)
        {
          // pause = " ";
          typeRowPos = 0;
        }
      else
        pause = "";

      invMessage.setText(invMessage.getText() + letters[typePos] + pause, "fonts/witcherfont.ttf", 30, Renderer, "blended", 360);// typeInvMessage.at(typePos));
      typePos++;
      typeRowPos++;

      // cout << "TEXT: " << invMessage.getText() << endl;
    }

  if(inventorySelected > 2)
    inventorySelected = 0;
  if(inventorySelected < 0)
    inventorySelected = 2;

  optionsMessage[0].setColor(255, 255, 255);
  optionsMessage[1].setColor(255, 255, 255);
  invMessage.setColor(255, 255, 255);

  int x, y;

  SDL_GetMouseState(&x, &y);

  if(inventorySelected == 0)
   {
    menuOptions = inventoryOption;
     invMessage.setColor(78, 64, 78);
   }

   for(int i = 1; i < 3; i++)
    if(inventorySelected == i)
      optionsMessage[i - 1].setColor(78, 64, 78);


  for(int i = 0; i < 2; i++)
  {
    // if(menuOptions != i)
    // if(i != inventorySelected)
      // optionsMessage[i].setColor(255, 255, 255);
  }


  invMessage.setText(invMessage.getText(), "fonts/witcherfont.ttf", 30, Renderer, "blended", 360);// typeInvMessage.at(typePos));
  optionsMessage[0].setText(optionsMessage[0].getText(), "fonts/witcherfont.ttf", 30, Renderer, "blended", 360);
  optionsMessage[1].setText(optionsMessage[1].getText(), "fonts/witcherfont.ttf", 30, Renderer, "blended", 360);



  invMessage.display(250, 150, 300, 300, Renderer, "blended");
  optionsMessage[0].display(250, 200, 300, 300, Renderer, "blended");
  optionsMessage[1].display(250, 250, 300, 300, Renderer, "blended");


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

    SDL_Delay(30);
    //time

  }

  free();

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
  invMessage.clearText();
  for(int i = 0; i < 2; i++)
    optionsMessage[i].Free();
  words.clear();
  letters.clear();
  geralt[0].Free();
  
  delete [] geralt;
  delete [] optionsMessage;

  inventorySelected = 0;
  typePos = 0;
}
