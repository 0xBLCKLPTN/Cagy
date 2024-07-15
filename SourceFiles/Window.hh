#ifndef WINDOW_HH
#define WINDOW_HH

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <vector>
#include "./Core.hh"

class CagyWindow
{
private:
  std::vector<render_operation> operations;  
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;
  SDL_GLContext ctx;
  bool running = true;
  int WINDOW_WIDTH = 600;
  int WINDOW_HEIGHT = 400;

public:
  int InitWindow();
  SDL_Renderer* GetRenderer();
  int start_main_loop(std::vector<render_operation> operations);    
  int render();
  int Quit();
};

#endif
