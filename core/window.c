#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#define WINDOW_TITLE "Cagy"
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

typedef struct CagyWindow_t
{
  SDL_Renderer* renderer;
  SDL_Window* window;
} CagyWindow_s;

void destroyAll(CagyWindow_s* cw) {
  SDL_DestroyRenderer(cw->renderer);
  SDL_DestroyWindow(cw->window);
}

int initWindow(CagyWindow_s *cw)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    printf("Cant init SDL2: %s\n", SDL_GetError());
    return -1;
  }

  SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                                        SDL_WINDOW_SHOWN);

  if (!window)
  {
    printf("Window was not initialized: %s\n", SDL_GetError());
    return -1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer)
  {
    printf("Renderer was not inititalized: %s\n", SDL_GetError());
    return -1;
  }

  cw->window = window;
  cw->renderer = renderer;

  return 0;
}


int main(int argc, char* argv[])
{
  CagyWindow_s cw;
  if (initWindow(&cw) == -1) return -1;


  SDL_Event event;
  bool running = true;
  
  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      SDL_PumpEvents();

      if (event.type == SDL_QUIT)
      {
        running = false;
      }
    }

    
    SDL_SetRenderDrawColor(cw.renderer, 255, 0,0, 255);
    SDL_RenderClear(cw.renderer);

    // Something else
      // Test RECT 2D COMPONENT
    SDL_SetRenderDrawColor(cw.renderer, 0, 0, 255, 255);
    
    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.w = 200;
    rect.h = 200;


    SDL_RenderFillRect(cw.renderer, &rect);

      //
    // -----


    SDL_RenderPresent(cw.renderer);

  }
  SDL_Quit();
  return 0;
}
