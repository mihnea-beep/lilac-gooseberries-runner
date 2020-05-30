#include "Rect.h"

Rect::Rect()
{

}

Rect::Rect(int x, int y, int w, int h)
{
    rc.x = x;
    rc.y = y;
    
    rc.w = w;
    rc.h = h;

    this->x = x;
    this->y = y;

    this->w = w;
    this->h = h;
}

int Rect::setX(int x)
{
    rc.x = x;
    this->x = x;
}

int Rect::setY(int y)
{
    rc.y = y;
    this->y = y;
}


int Rect::setW(int w)
{
    rc.w = w;
    this->w = w;
}


int Rect::setH(int h)
{
    rc.h = h;
    this->h = h;
}

int  Rect::setDim(int x, int y, int w, int h)
{
    setX(x);
    setY(y);
    setW(w);
    setH(h);

}

int Rect::getX()
{
    return x;
}

int Rect::getY()
{
    return y;
}

int Rect::getH()
{
    return h;
}

int Rect::getW()
{
    return w;
}


void Rect::show(SDL_Renderer* renderer)
{
    SDL_RenderDrawRect(renderer, &rc);
}

void Rect::colorHit(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
    show(renderer);
}

Rect::~Rect()
{
    
}