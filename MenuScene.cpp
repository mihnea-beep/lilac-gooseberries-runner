#include "MenuScene.h"
#include "GUI.h"

MenuScene::MenuScene()
{

}

void MenuScene::loadRes(SDL_Renderer* Renderer)
{
  TTF_Init();

  optionsMessage = new Message[optionsNo];
  menuOptions = statsOption;

  invMessage.setColor(255, 255, 255);
  invMessage.setText("AAAAAAAAA", "fonts/witcherfont.ttf", 30, Renderer, "blended", 640);

  optionsMessage[0].setColor(255, 255, 255);
  optionsMessage[0].setText("Options", "fonts/witcherfont.ttf", 30, Renderer, "blended", 640);
  optionsMessage[1].setText("Exit", "fonts/witcherfont.ttf", 30, Renderer, "blended", 640);
  // optionsMessage[2].setText("Exit", "fonts/witcherfont.ttf", 30, Renderer, "blended", 640);
  // menuOptions = inventoryOption;

  selectOption = false;


  geralt = new Player[1];

  typeInvMessage = "New game";

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

void MenuScene::Init(SDL_Renderer* Renderer)
{
    loadRes(Renderer);
}

void MenuScene::checkInput()
{

  SDL_Event ev;

  while(SDL_PollEvent(&ev))
      {
          if(ev.type == SDL_QUIT)
             {
                 cout<<"User pressed 'exit'!";
                 MenuScene_running = false;
             }

            if(ev.type == SDL_KEYDOWN)
            {
              switch(ev.key.keysym.sym)
              {

                case SDLK_q:

                case SDLK_i:

                cout << "Inventory exited" << endl;

                MenuScene_running = false;

                break;
                
                case SDLK_UP:

                inventorySelected--;

                break;
                
                case SDLK_DOWN:

                inventorySelected++;

                break;                

                case SDLK_RETURN:

                selectOption = true;

                cout << "Option selected!" << endl;

                break;
                
                case SDLK_ESCAPE:

                cout<<"User pressed 'escape'!";

                MenuScene_running = false;

                break;

                default:
                break;

              }
            }
          }

}

void MenuScene::update()
{

}

void MenuScene::checkMenu(SDL_Renderer* Renderer)
{
    if(Options.getRunning() == true)
     Options.loadOptionsScene(Renderer);
}

void MenuScene::render(SDL_Renderer* Renderer)
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
  
  if(selectOption)
    {

      if(inventorySelected == 0)
        {
          // cout << "Inventory" << endl;

          MenuScene_running = false;
  
          // Options.setMessagesNumber(1);
  
          // Options.loadElement(Renderer, "Inventory", 250, 50, 100, 30, "fonts/witcherfont.ttf", 30, 0);
          // Options.setRunning(true);
          // checkMenu(Renderer);
        }


      if(inventorySelected == 1)
        {
          cout << "Options" << endl;
          
          Options.setWindow(getWindow());

          // Options.loadElement(Renderer, "Options", 30, 30, 100, 30, "fonts/witcherfont.ttf", 30, 0);
          // Options.loadElement(Renderer, "Stamina: ?/100", 30, 80, 100, 30, "fonts/witcherfont.ttf", 30, 1);
          // Options.loadElement(Renderer, "Jumps: unlimited", 30, 130, 100, 30, "fonts/witcherfont.ttf", 30, 2);
          // Options.loadElement(Renderer, "Adrenaline: ?/?", 30, 180, 100, 30, "fonts/witcherfont.ttf", 30, 3);
          // Options.loadElement(Renderer, "Level: ?", 30, 180 + 100, 100, 30, "fonts/witcherfont.ttf", 30, 4);
          // Options.loadElement(Renderer, "Experience: ?/10", 30, 180 + 150, 100, 30, "fonts/witcherfont.ttf", 30, 5);

          Options.setRunning(true);
          checkMenu(Renderer);
        }

      if(inventorySelected == 2)
        {
          cout << "Exit" << endl;

          MenuScene_running = false;
          exitGame = true;
  
          // Options.setMessagesNumber(1);
  
          // Options.loadElement(Renderer, "Signs", 280, 50, 100, 30, "fonts/witcherfont.ttf", 30, 0);
          // Options.setRunning(true);
          // checkMenu(Renderer);
        }

      

    }

    
  selectOption = false;
}

void MenuScene::loop(SDL_Renderer* Renderer)
{
  while(MenuScene_running)
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

void MenuScene::loadMenuScene(SDL_Renderer* Renderer)
{

    loadRes(Renderer);
    loop(Renderer);
}

MenuScene::~MenuScene()
{

}

bool MenuScene::getExit()
{
  return exitGame;
}

bool MenuScene::getRunning()
{
  return MenuScene_running;
}

void MenuScene::setRunning(bool x)
{
  MenuScene_running = x;
}

void MenuScene::free()
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
