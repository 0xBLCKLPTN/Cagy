#ifndef CORE_HH
#define CORE_HH


#include <SDL2/SDL.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

typedef int (*render_operation)(SDL_Renderer*, SDL_Window*);

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
