#ifndef WINDOW_HH
#define WINDOW_HH

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <vector>

typedef int (*render_operation)(SDL_Renderer*, SDL_Window*);

int draw_rect(SDL_Renderer* renderer, SDL_Window* window);
int get_middle(int max, int min);

class CagyWindow
{
private:
  std::vector<render_operation> operations;  
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;
  bool running = true;
  int WINDOW_WIDTH = 600;
  int WINDOW_HEIGHT = 400;

public:
  int InitWindow();
  SDL_Renderer* GetRenderer();
  int start_main_loop();    
  int render();
  int LoadOperation(render_operation operation);
};

#endif
