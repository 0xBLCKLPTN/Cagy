#include "./Window.hh"
#include <SDL2/SDL.h>
#include "./Core.hh"
#include <SDL_image.h>
#include <cmath>

int main(void)
{
  Operator cw_operator;
  CagyWindow cw;


  /* For loading some operation:
    cw_operator.LoadOperation(draw_rect);
  */
  cw.start_main_loop(cw_operator.GetOperations());
  return 0;
}
