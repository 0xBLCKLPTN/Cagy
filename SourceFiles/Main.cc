#include "./Window.hh"
#include <SDL2/SDL.h>

int op(SDL_Renderer* renderer, SDL_Window* window)
{
  printf("Hello Wolrd!\n");
  return 0;
}

int main(void)
{
  CagyWindow cw;
  cw.start_main_loop();
  cw.LoadOperation(op);
  return 0;
}
