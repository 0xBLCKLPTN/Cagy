#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
//#include <GL/gl.h>
#include <math.h>

#include <SDL2/SDL.h>
#define WINDOW_TITLE "Cagy"
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400
//#define CUBE_SIZE 100

#include "../components/rect_2d.h"


typedef struct Vector3D_t {
  float x, y, z;
} Vector3D_s;

int get_middle(int max, int min) {
  return (max + min) / 2;
}

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

int createRect(SDL_Window* window, SDL_Renderer* renderer)
{
  
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    
  int w, h, tl_x, tl_y;
  SDL_GetWindowSize(window, &w, &h);
  tl_x = get_middle(get_middle(w, w/2), w/2) - 200;
  tl_y = get_middle(get_middle(h, h/2), h/2) - 100;

  SDL_Point rectVertices[] = {
    {tl_x, tl_y},
    {tl_x + 300, tl_y},
    {tl_x + (300-100), tl_y + 100},
    {tl_x - 100, tl_y + 100},
    {tl_x, tl_y},
  };

  SDL_RenderDrawLines(renderer, rectVertices, 5);
  return 0;
}

int main(int argc, char* argv[])
{

  CagyWindow_s cw;
  if (initWindow(&cw) == -1) return -1;
  
  SDL_Event event;
  bool running = true;

  SDL_Point* rectVertices;
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
    createRect(cw.window, cw.renderer);
        //drawCube(cw.renderer);
    SDL_RenderPresent(cw.renderer);
    SDL_Delay(16);

  }
  destroyAll(&cw);
  SDL_Quit();
  return 0;
}
