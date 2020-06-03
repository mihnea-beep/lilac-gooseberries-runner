#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
using namespace std;


class Player
{
    private:

        int x, y;

        int h, w;

        uint8_t px, py;

        string name;

        SDL_Texture* weapon;

        float moveSpeed;
        float frameCounter;

        int frameWidth;
        int frameHeight;

        int textureWidth;
        int textureHeight; // none?

        bool isActive;

        bool isAlive;

        bool hasDied = false;

        int deadTime;

        SDL_Scancode keys[4];
        SDL_Rect cropRect;
        SDL_Texture* texture;

    public:

        Player();
        Player(string name, string filepath, int x, int y, int h, int w, SDL_Renderer* renderer);
        Player(SDL_Renderer* renderTarget, string FilePath, int x, int y, int framesX, int framesY, string name);

        int getX();
        int getY();

        int getH();
        int getW();

        void setH(int h);
        void setW(int w);

        string getName();
        // int getFrames();


        void setX(int dx);
        void setY(int dy);
        void setPos(int dx, int dy);

        void setName(string name);

        void setImage(string filename, SDL_Renderer* ren);
        void setImage(string filename, SDL_Renderer* ren, int color_key); //transparency

        bool isColliding(int x, int y);
        bool isColliding(int x, int y, SDL_Renderer* renderer);
        bool isColliding(int objX, int objY, int x, int y, int collisionDist, SDL_Renderer* renderer = NULL);
        bool isColliding(int x, int y, int collisionDistance);
        bool isColliding(int x, int y, int offsetX, int offsetY);
        bool isColliding(Player& p);

        void Free();

        void setLife(bool livingstatus);
        void live();
        void die();
        bool lifestatus();
        void respawn(int respawnTime);

        SDL_Texture* getTexture() const;

        void drawPlayer(SDL_Renderer* renderer);
        void randSpawn();

        void attack(SDL_Renderer*); // here or in game?




        void Update(float delta, const uint8_t *keyState);
        void Draw(SDL_Renderer* renderTarget);
        void draw(SDL_Renderer* render);

        ~Player();

        SDL_Rect posRect;




};



#endif // PLAYER_H_INCLUDED
