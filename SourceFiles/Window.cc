#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./Window.hh"
#include <vector>

#define WINDOW_TITLE "Cagy"


typedef int (*render_operation)(SDL_Renderer*, SDL_Window*);

int CagyWindow::InitWindow()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("Can't init SDL2: %s\n", SDL_GetError());
    return -1;
  }

  window = SDL_CreateWindow(WINDOW_TITLE, 0,0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window) {
    return -1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer) {
    return -1;
  }
}

int CagyWindow::render() {
  SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
  SDL_RenderClear(this->renderer);
  printf("%li\n", this->operations.size());
  for (int i = 0; i<this->operations.size(); i++)
  {
    operations[i](this->renderer, this->window);
  }
  SDL_RenderPresent(this->renderer);
  SDL_Delay(16);  
}

int CagyWindow::LoadOperation(render_operation operation) {
  printf("Loading new Cagy Operation: %p\n", operation);
  this->operations.push_back(operation);
  return 0;
}

int CagyWindow::start_main_loop() {
  if (this->InitWindow() == -1) exit(-1);
  running = true;
  while (running)
  {
    while (SDL_PollEvent(&this->event)) {
      SDL_PumpEvents();
      if (this->event.type == SDL_QUIT)
        running = false;
    }
  this->render();       
  }
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  SDL_Quit();
  return 0;
}

