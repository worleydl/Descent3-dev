#include <Windows.h>
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

extern "C" __declspec(dllimport) void* uwp_GetWindowReference();

int bootstrap(int argc, char** argv)
{
    SDL_SetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD, "true"); // 
    uwp_GetWindowReference(); // Call to init reference for gfx thread

    return SDL_main(argc, argv);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR argv, int argc)
{
    return SDL_RunApp(0, 0, bootstrap, NULL);
}
