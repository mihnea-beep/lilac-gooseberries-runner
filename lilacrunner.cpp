#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Scene.h"


using namespace std;


int main(int argc, char const *argv[])
{
    /* code */

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    SDL_Renderer* renderer;

    window = SDL_CreateWindow("Lilac & Gooseberries", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //| SDL_RENDERER_PRESENTVSYNC); // ? get refresh rate first ? if 60 then use this

    // Window = SDL_CreateWindow("Carrot Master 0.49", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_FULLSCREEN);
    // Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    Scene soundScene;
    
    soundScene.setRunning(true);
    soundScene.loadScene(renderer);

    // string soundName = "sound1.wav";
	// Mix_Chunk* sound;

	// int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
	// result = Mix_AllocateChannels(4);

	// sound = Mix_LoadWAV(soundName.c_str());

    // Mix_PlayChannel(-1, sound, 2);

    SDL_Quit();

    


    return 0;
}


