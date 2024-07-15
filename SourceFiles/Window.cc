#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./Window.hh"
#include <vector>
#include <SDL_image.h>

#define WINDOW_TITLE "Cagy"


typedef int (*render_operation)(SDL_Renderer*, SDL_Window*);

int CagyWindow::InitWindow()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("Can't init SDL2: %s\n", SDL_GetError());
    return -1;
  }
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  
  window = SDL_CreateWindow
    (
     WINDOW_TITLE,
     0,0,
     WINDOW_WIDTH, WINDOW_HEIGHT,
     SDL_WINDOW_OPENGL
   );

  if (!window) {
    return -1;
  }

  ctx = SDL_GL_CreateContext(window);
  SDL_GL_SetSwapInterwal(1);

  /* Set Rendering Settings */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity()
  glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity()
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glShadeModel(GL_SMOOTH);

  

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer) {
    return -1;
  }

  
  
}

int CagyWindow::Quit() {
  if (thix->ctx) SDL_GL_DeleteContext(this->ctx);

  
}

int CagyWindow::render() {
  SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
  SDL_RenderClear(this->renderer);
  for (int i = 0; i<this->operations.size(); i++)
  {
    operations[i](this->renderer, this->window);
  }

  

  
  SDL_RenderPresent(this->renderer);
  SDL_Delay(16);  
}

int CagyWindow::start_main_loop(std::vector<render_operation> operations) {
  if (this->InitWindow() == -1) exit(-1);
  running = true;
  this->operations = operations;
  while (running)
  {
    while (SDL_PollEvent(&this->event)) {
      SDL_PumpEvents();
      if (this->event.type == SDL_QUIT)
        running = false;
    }
  SDL_GL_MakeCurrent(this->window, this->ctx);
  SDL_GetWindowSize(window, this->&w, this->&h);
  glViewport(0,0,w,h);
  this->render();
  SDL_GL_SwapWindow(window);
  }
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  SDL_Quit();
  return 0;
}

