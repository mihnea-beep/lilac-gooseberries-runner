#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class Rect
{
    SDL_Rect rc;
    
    int x;
    int y;

    int w;
    int h;

    string name = "rectangle";

    string type = "solid"; 

    int weight;

    // other attributes (weight, color, etc.)

    public:

        Rect();
        Rect(int x, int y, int w, int h);

        int setX(int x);
        int setY(int y);
        int setW(int w);
        int setH(int h);

        int getY();
        int getX();
        int getH();
        int getW();

        void colorHit(SDL_Renderer* renderer);

        int setDim(int x, int y, int w, int h);
        



        void show(SDL_Renderer* renderer);


        ~Rect();
};