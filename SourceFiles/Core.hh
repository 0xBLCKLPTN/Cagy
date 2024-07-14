/* 
  Filename: Core.hh
  Description: Core functions for Cagy.
  Author: Daniil (Two Faced Janus) Ermolaev.
*/

#ifndef CORE_HH
#define CORE_HH

#include <SDL2/SDL.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

typedef int (*render_operation)(SDL_Renderer*, SDL_Window*);

/*
  Vector of functions.
  Usage example:

    #include "Core.hh"
    int function(SDL_Renderer* ren, SDL_Window* win) { return 0; }
    
    int main(void) {
      Operator op;
      op.LoadOperation(function);
      ...
      op.GetOperations();
    }  

*/
class Operator
{
private:
  std::vector<render_operation> operations;

public:
  std::vector<render_operation> GetOperations() {
    printf("[ Cagy-Operator ]=> Count of operations: %ld\n", this->operations.size());
    return this->operations;
  }
  
  int GetOperationsSize() { return this->operations.size(); }

  void LoadOperation(render_operation operation) {
    printf("[ Cagy-Operator ]=> Loading operation: %p - ", operation);
    this->operations.push_back(operation);
    printf("Done!\n");
  }

  
};


#endif
