#ifndef RECT2D_H
#define RECT2D_H

#include <SDL2/SDL.h>
#include "../common/component_props.h"


typedef struct Rect2D_t {
  SDL_Rect* rect;
  int r;
  int g;
  int b;
  int a;
} Rect2D_s;

Rect2D_s* drawRect2D(int r, int g, int b, int a,
                     int w, int h, 
                     int x, int y,
                     SDL_Renderer* ren)
{
  SDL_SetRenderDrawColor(ren, r, g, b, a);
  SDL_Rect rect;

  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  SDL_RenderFillRect(ren, &rect);

  Rect2D_s obj;

  // FIXME LATER
  obj.rect = &rect;
  obj.r = r;
  obj.g = g;
  obj.b = b;
  obj.a = a;
  return &obj;
}


#endif
