#include "Player.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>

using namespace std;

Player::Player()
{
    name = "Character";
    cout<<name<<" created!"<<endl;
    texture = NULL;
    weapon = NULL;
    x = 50;
    y = 50;
    isAlive = true;

}

void Player::setLife(bool livingstatus)
{
    isAlive = livingstatus;
}

void Player::live()
{
    isAlive = true;
    randSpawn();
}

void Player::die()
{
    setPos(-100, -100);
    isAlive = false;
   // Free();

    //Free();

    deadTime = SDL_GetTicks();
}


void Player::respawn(int respawnTime)
{
    if( (SDL_GetTicks() - deadTime) > respawnTime)
        live();

}

bool Player::lifestatus()
{
    return isAlive;

}

void Player::setImage(string filename, SDL_Renderer* ren)
{
    if(texture != NULL)
        SDL_DestroyTexture(texture);

    texture = NULL;

    SDL_Surface* psurf = IMG_Load(filename.c_str());

    if(psurf == NULL)
        cout << "IMAGE LOADING ERROR - surface";

    texture = SDL_CreateTextureFromSurface(ren, psurf);

    if(texture == NULL)
        cout << "IMAGE LOADING ERROR - texture";

    SDL_FreeSurface(psurf);

}

void Player::setH(int h)
{
    this->h = h;
}

void Player::setW(int w)
{
    this->w = w;
}

int Player::getH()
{
    return h;
}

int Player::getW()
{
    return w;
}

void Player::draw(SDL_Renderer* render) // test for now
{
    SDL_Rect prect;

    prect.h = h;
    prect.w = w;

    SDL_RenderCopy(render, getTexture(), NULL, &prect);

}

void Player::attack(SDL_Renderer* Renderer) // here or in game?
{
    //SDL_Surface* wep_surf = IMG_Load();
    //SDL_Rect rc;
    //rc.x = 200;
    //rc.y = rc.x;
    //rc.h = rc.w = 20;
    //attacking = true;
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(Renderer, getX() + getW() / 2, getY(), getX() + 100, getY());
    //SDL_RenderDrawRect(Renderer, &rc);
   // setPos(10, 10);
}

void Player::Free()
{
    if(texture != NULL)
        SDL_DestroyTexture(texture);

    texture = NULL;

}

string Player::getName()
{
    return name;
}

void Player::setImage(string filename, SDL_Renderer* ren, int color_key) //color_key -> see pixel value return from SDL_MapRGB
{
    if(texture != NULL)
        SDL_DestroyTexture(texture);

    texture = NULL;

    SDL_Surface* psurf = IMG_Load(filename.c_str());

    SDL_SetColorKey(psurf, SDL_FALSE, SDL_MapRGB(psurf->format, 0, 0, 0xFF));

    texture = SDL_CreateTextureFromSurface(ren, psurf);

    SDL_FreeSurface(psurf);

}

void Player::drawPlayer(SDL_Renderer* renderer)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;

    dest.w = 20; // player tile size
    dest.h = 16; //

    SDL_RenderCopy(renderer, texture, NULL, &dest);


}

int Player::getX()
{
    return x;
}

int Player::getY()
{
    return y;
}

void Player::setX(int dx)
{
    x = dx;
}

void Player::setY(int dy)
{
    y = dy;
}

SDL_Texture* Player::getTexture() const
{
    return texture;
}



Player::Player(const string name, const string filepath, int x, int y, int h, int w, SDL_Renderer* renderer)
{
    this->name = name;

    this->x = x;
    this->y = y;

    this->h = h;
    this->w = w;

    SDL_Surface* psurf = IMG_Load(filepath.c_str());

    texture = SDL_CreateTextureFromSurface(renderer, psurf);

    SDL_FreeSurface(psurf);
    // setImage(filepath, renderer);

}

bool Player::isColliding(Player& p)
{
    return isColliding(p.getX() + p.getW() / 2, p.getY() - p.getH() / 2);

}

bool Player::isColliding(int x, int y)
{
    float centerX = getX() + getW() / 2;
    float centerY = getY() - getH() / 2;

    float dstx = centerX - x;
    float dsty = centerY - y;

    float dist = sqrt( (dstx * dstx) + (dsty * dsty) );

    if(dist <= 65) // collision distance
        return 1;
    else
        return 0;
}

bool Player::isColliding(int x, int y, int offsetX, int offsetY)
{

}


void Player::setPos(int dx, int dy)
{
    setX(dx);
    setY(dy);
}

void Player::randSpawn()
{
    setPos(rand() % 600, rand() % 400);
}

Player::~Player()
{
    if(texture != NULL)
        SDL_DestroyTexture(texture);
    //if(weapon != NULL)
      //  SDL_DestroyTexture(weapon);

    cout<<endl<<"Character deleted!";
}
