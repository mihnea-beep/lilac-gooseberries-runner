#include "InventoryScene.h"
#include "GUI.h"

InventoryScene::InventoryScene()
{

}

void InventoryScene::loadRes(SDL_Renderer* Renderer)
{
  TTF_Init();
  // invMessage.setColor(0, 0, 0);
  invMessage.setColor(255, 255, 255);

  invMessage.setText("Inventory", "fonts/witcherfont.ttf", 30, Renderer, "blended", 640);

  geralt = new Player[1];

  typeInvMessage = "Inventory";
  invMessage.setText("");

  string sentence = typeInvMessage; //"word1 and word2 and then word3 and so on lots of words long words quite long spectacular discriminatory 123 a";

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
      // typePos++;

      string pause = "";
      // string nextWord = "word";
      string nextWord;

      nextWord = "aaa";

      int r = rand() % 2;

      // if(r == 1)
        // pause = " ";
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

  if(inventorySelected > 1)
    inventorySelected = 0;

  if(inventorySelected == 1)
   invMessage.setColor(70, 0, 68);
  else
    invMessage.setColor(255, 255, 255);

  invMessage.setText(invMessage.getText(), "fonts/witcherfont.ttf", 30, Renderer, "blended", 360);// typeInvMessage.at(typePos));


  invMessage.display(250, 150, 300, 300, Renderer, "blended");

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
  words.clear();
  letters.clear();

  geralt[0].Free();
  
  delete [] geralt;

  typePos = 0;
}
