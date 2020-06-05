
#include "Message.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

using namespace std;

Message::Message()
{

}

Message::Message(SDL_Renderer* renderer, string text)
{

}

TTF_Font* Message::getFont()
{
    return msg_font;
}

void Message::setText(string text, string font, uint16_t size, SDL_Renderer* renderer, string mode, int wrapLength)
{
    //msg_color = {0, 0, 100};

    if(msg_font != NULL)
        TTF_CloseFont(msg_font);
    msg_font = NULL;

    //if(msg_font != NULL)
    //    delete [] msg_font;

    // maybe the surface is used right after being freed?
    // somewhere in the program

    //if(msg_surface != NULL)
     //   SDL_FreeSurface(msg_surface);

   // msg_surface = NULL;


    msg_font = TTF_OpenFont(font.c_str(), size);

    if(msg_font == NULL)
        cout << "LOADING ERROR - font " << TTF_GetError() << endl;

	if(msg_texture != NULL)
		SDL_DestroyTexture(msg_texture);

    msg_texture = NULL;

	//if(msg_surface != NULL)
	//	SDL_FreeSurface(msg_surface);

    if(mode == "blended")
        msg_surface = TTF_RenderText_Blended_Wrapped(msg_font, text.c_str(), {0, 0, 0}, wrapLength); 
    else
        msg_surface = TTF_RenderText_Solid(msg_font, text.c_str(), msg_color);

    msg_texture = SDL_CreateTextureFromSurface(renderer, msg_surface);

    SDL_FreeSurface(msg_surface);

    messageText = text;

	//TTF_CloseFont(msg_font); instacrash :D

	//msg_surface = NULL; no clue what just happened
}

void Message::setColor(int r, int g, int b)
{
    msg_color = {r, g, b};
}

void Message::Free()
{
    if(msg_texture != NULL)
        SDL_DestroyTexture(msg_texture);

    msg_texture = NULL;

   // if(msg_surface != NULL)
     //   SDL_FreeSurface(msg_surface);
    //msg_surface = NULL;

  //  if(msg_font != NULL)
    //    TTF_CloseFont(msg_font);

    //msg_font = NULL;

    //if(msg_surface != NULL)
    //    SDL_FreeSurface(msg_surface);

	//if(msg_font != NULL)
	//	TTF_CloseFont(msg_font);
}

void Message::display(int x, int y, int w, int h, SDL_Renderer* renderer, string mode)
{
    msgRc.x = x;
    msgRc.y = y;

     if(mode == "blended")
    {
        int width, height;
        TTF_SizeText(msg_font, messageText.c_str(), &width, &height);
        // int multiply = round((width / 500) + 0.5);
        // if(multiply >= 2)
            // msgRc.h = height * multiply;
        // else

        SDL_QueryTexture(getTexture(), NULL, NULL, &width, &height);

            msgRc.h = height;

        msgRc.w = width;

        // cout << msgRc.w << endl;

    }
    else
    {
        msgRc.w = w;
        msgRc.h = h;
    }

    // if(mode == "blended")
        // SDL_RenderCopy(renderer, msg_texture, NULL, NULL);
    // else
    // {
        SDL_RenderCopy(renderer, msg_texture, NULL, &msgRc);
    // }
    
}

SDL_Texture* Message::getTexture()
{
    return msg_texture;
}

Message::~Message()
{
    if(msg_surface != NULL)
        delete [] msg_surface;

    if(msg_texture != NULL)
        delete [] msg_texture;

    if(msg_font != NULL)
        delete [] msg_font;

}
