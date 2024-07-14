#include "./Window.hh"
#include <SDL2/SDL.h>
#include "./Core.hh"
#include <SDL_image.h>
#include <cmath>

const float PI = 3.14159265f;

struct Vector3 {
    float x, y, z;
};

struct Vector2 {
    float x, y;
};

struct Vertex {
    Vector3 position;
    Vector2 texCoord;
};

int op(SDL_Renderer* renderer, SDL_Window* window)
{
  printf("Hello Wolrd!\n");
  return 0;
}

int draw_rect(SDL_Renderer* renderer, SDL_Window* window) {
    SDL_Surface* surface = IMG_Load("~/texture.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
     Vertex vertices[6][4];

    float x = 400;
    float y = 300;
    float z = 200;

    float angle = 45;
    float size = 100;

    float a = angle * PI / 180.0f;
    float ca = cosf(a);
    float sa = sinf(a);

    float hs = size / 2;

    // Define the vertices and texture coordinates for each face of the cube
    vertices[0][0] = { { -hs, -hs, -hs }, { 0.0f, 0.0f } };
    vertices[0][1] = { { hs, -hs, -hs }, { 1.0f, 0.0f } };
    vertices[0][2] = { { hs, hs, -hs }, { 1.0f, 1.0f } };
    vertices[0][3] = { { -hs, hs, -hs }, { 0.0f, 1.0f } };

    vertices[1][0] = { { -hs, -hs, hs }, { 0.0f, 0.0f } };
    vertices[1][1] = { { hs, -hs, hs }, { 1.0f, 0.0f } };
    vertices[1][2] = { { hs, hs, hs }, { 1.0f, 1.0f } };
    vertices[1][3] = { { -hs, hs, hs }, { 0.0f, 1.0f } };

    vertices[2][0] = { { -hs, -hs, -hs }, { 0.0f, 0.0f } };
    vertices[2][1] = { { -hs, -hs, hs }, { 1.0f, 0.0f } };
    vertices[2][2] = { { -hs, hs, hs }, { 1.0f, 1.0f } };
    vertices[2][3] = { { -hs, hs, -hs }, { 0.0f, 1.0f } };

    vertices[3][0] = { { hs, -hs, -hs }, { 0.0f, 0.0f } };
    vertices[3][1] = { { hs, -hs, hs }, { 1.0f, 0.0f } };
    vertices[3][2] = { { hs, hs, hs }, { 1.0f, 1.0f } };
    vertices[3][3] = { { hs, hs, -hs }, { 0.0f, 1.0f } };

    vertices[4][0] = { { -hs, -hs, -hs }, { 0.0f, 0.0f } };
    vertices[4][1] = { { hs, -hs, -hs }, { 1.0f, 0.0f } };
    vertices[4][2] = { { hs, -hs, hs }, { 1.0f, 1.0f } };
    vertices[4][3] = { { -hs, -hs, hs }, { 0.0f, 1.0f } };

    vertices[5][0] = { { -hs, hs, -hs }, { 0.0f, 0.0f } };
    vertices[5][1] = { { hs, hs, -hs }, { 1.0f, 0.0f } };
    vertices[5][2] = { { hs, hs, hs }, { 1.0f, 1.0f } };
    vertices[5][3] = { { -hs, hs, hs }, { 0.0f, 1.0f } };

    // Rotate the vertices around the y-axis
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            float rx = vertices[i][j].position.x;
            float rz = vertices[i][j].position.z;
            vertices[i][j].position.x = rx * ca - rz * sa;
            vertices[i][j].position.z = rx * sa + rz * ca;
            vertices[i][j].position.x += x;
            vertices[i][j].position.y += y;
            vertices[i][j].position.z += z;
        }
    }

    // Project the vertices onto the screen
    SDL_Point screenVertices[6][4];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            float p = 300.0f / (vertices[i][j].position.z + 300.0f);
            screenVertices[i][j].x = vertices[i][j].position.x * p + 400;
            screenVertices[i][j].y = vertices[i][j].position.y * p + 300;
        }
    }

    // Draw the textured cube
    for (int i = 0; i < 6; i++) {
        SDL_RenderDrawLine(renderer, screenVertices[i][0].x, screenVertices[i][0].y, screenVertices[i][1].x, screenVertices[i][1].y);
        SDL_RenderDrawLine(renderer, screenVertices[i][1].x, screenVertices[i][1].y, screenVertices[i][2].x, screenVertices[i][2].y);
        SDL_RenderDrawLine(renderer, screenVertices[i][2].x, screenVertices[i][2].y, screenVertices[i][3].x, screenVertices[i][3].y);
        SDL_RenderDrawLine(renderer, screenVertices[i][3].x, screenVertices[i][3].y, screenVertices[i][0].x, screenVertices[i][0].y);

        SDL_FRect destRect = {
            screenVertices[i][0].x, screenVertices[i][0].y,
            (screenVertices[i][1].x - screenVertices[i][0].x) * 64,
            (screenVertices[i][3].y - screenVertices[i][0].y) * 64
        };

        SDL_Rect srcRect = {
            vertices[i][0].texCoord.x * 64, vertices[i][0].texCoord.y * 64,
            64,
            64
        };

        SDL_RenderCopyF(renderer, texture, &srcRect, &destRect);
    }

} 




int main(void)
{
  Operator cw_operator;
  CagyWindow cw;

  cw_operator.LoadOperation(draw_rect);
  cw.start_main_loop(cw_operator.GetOperations());
  return 0;
}
