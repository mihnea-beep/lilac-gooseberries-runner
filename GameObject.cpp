#include "GameObject.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>

using namespace std;

GameObject::GameObject()
{
    name = "Character";
    cout<<name<<" created!"<<endl;
    texture = NULL;
    weapon = NULL;
    x = 50;
    y = 50;
    w = 100;
    h = 100;
    isAlive = true;

}

void GameObject::setLife(bool livingstatus)
{
    isAlive = livingstatus;
}

void GameObject::setName(string name)
{
    this->name = name;
}

void GameObject::live()
{
    isAlive = true;
    randSpawn();
}

void GameObject::die()
{
    setPos(-100, -100);
    isAlive = false;
   // Free();

    //Free();

    deadTime = SDL_GetTicks();
}


void GameObject::respawn(int respawnTime)
{
    if( (SDL_GetTicks() - deadTime) > respawnTime)
        live();

}

bool GameObject::lifestatus()
{
    return isAlive;

}

void GameObject::setImage(string filename, SDL_Renderer* ren)
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

void GameObject::setH(int h)
{
    this->h = h;
}

void GameObject::setW(int w)
{
    this->w = w;
}

int GameObject::getH()
{
    return h;
}

int GameObject::getW()
{
    return w;
}

void GameObject::draw(SDL_Renderer* render) // test for now
{
    SDL_Rect prect;

    prect.h = h;
    prect.w = w;

    SDL_RenderCopy(render, getTexture(), NULL, &prect);

}

void GameObject::attack(SDL_Renderer* Renderer) // here or in game?
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

void GameObject::Free()
{
    if(texture != NULL)
        SDL_DestroyTexture(texture);

    texture = NULL;

}

string GameObject::getName()
{
    return name;
}

void GameObject::setImage(string filename, SDL_Renderer* ren, int color_key) //color_key -> see pixel value return from SDL_MapRGB
{
    if(texture != NULL)
        SDL_DestroyTexture(texture);

    texture = NULL;

    SDL_Surface* psurf = IMG_Load(filename.c_str());

    SDL_SetColorKey(psurf, SDL_FALSE, SDL_MapRGB(psurf->format, 0, 0, 0xFF));

    texture = SDL_CreateTextureFromSurface(ren, psurf);

    SDL_FreeSurface(psurf);

}

void GameObject::drawGameObject(SDL_Renderer* renderer)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;

    dest.w = 20; // GameObject tile size
    dest.h = 16; //

    SDL_RenderCopy(renderer, texture, NULL, &dest);


}

int GameObject::getX()
{
    return x;
}

int GameObject::getY()
{
    return y;
}

void GameObject::setX(int dx)
{
    x = dx;
}

void GameObject::setY(int dy)
{
    y = dy;
}

SDL_Texture* GameObject::getTexture() const
{
    return texture;
}



GameObject::GameObject(const string name, const string filepath, int x, int y, int h, int w, SDL_Renderer* renderer)
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

bool GameObject::isColliding(GameObject& p)
{
    return isColliding(p.getX() + p.getW() / 2, p.getY() - p.getH() / 2);

}

bool GameObject::isColliding(int x, int y)
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

bool GameObject::isColliding(int objX, int objY, int x, int y, int collisionDist, SDL_Renderer* renderer)
{
    float centerX = getX() + getW() / 2 + objX; // object offset
    float centerY = getY() - getH() / 2 + objY; // object offset

    float dstx = centerX - x;
    float dsty = centerY - y;

    float dist = sqrt( (dstx * dstx) + (dsty * dsty) );


    if(renderer != NULL)
        SDL_RenderDrawLine(renderer, centerX, centerY, x, y);

    if(dist <= collisionDist) // collision distance
        return 1;
    else
        return 0;
}


bool GameObject::isColliding(int x, int y, int collisionDistance)
{
    float centerX = getX() + getW() / 2;
    float centerY = getY() - getH() / 2;

    float dstx = centerX - x;
    float dsty = centerY - y;

    float dist = sqrt( (dstx * dstx) + (dsty * dsty) );

    if(dist <= collisionDistance) // collision distance
        return 1;
    else
        return 0;
}

bool GameObject::isColliding(int x, int y, int offsetX, int offsetY)
{

}


void GameObject::setPos(int dx, int dy)
{
    setX(dx);
    setY(dy);
}

void GameObject::randSpawn()
{
    setPos(rand() % 600, rand() % 400);
}

GameObject::~GameObject()
{
    if(texture != NULL)
        SDL_DestroyTexture(texture);
    //if(weapon != NULL)
      //  SDL_DestroyTexture(weapon);

    cout<<endl<<"Character deleted!";
}
