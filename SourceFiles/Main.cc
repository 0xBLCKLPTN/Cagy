#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <vector>

typedef int (*render_operation)();


class Window
{
private:
    SDL_GLContext ctx;
    SDL_Window* window;
    SDL_DisplayMode mode;
    SDL_Event event;
    int now;
    int status;

    std::vector<render_operation> operations;
public:
    void Render()
    {
        for (int i = 0; i<this->operations.size(); i++)
            operations[i]();
    }
    void quit(int rc) {
        if (ctx) {
            /* SDL_GL_MakeCurrent(0, NULL); *//* doesn't do anything */
            SDL_GL_DeleteContext(ctx);
        }
        SDL_DestroyWindow( window );
        SDL_Quit();
        exit(rc);
    }
    
    int init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not init video %s\n", glGetError());
            return 0;
        }

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        window = SDL_CreateWindow
        (
            "Cagy Engine",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            SDL_WINDOW_OPENGL   
        );
        if (window == NULL) {
            printf("SDL could not init window: %s\n", glGetError());
            return 0;
        }
        ctx = SDL_GL_CreateContext(window);
        SDL_GL_SetSwapInterval(1);
   
   
        /* Set rendering settings */
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glShadeModel(GL_SMOOTH);
    }

    int run(std::vector<render_operation> operations) {
        int frames = 0;
        int then = SDL_GetTicks();
        int done = 0;
        this->operations = operations;
        while (!done) {
            /* Check for events */
            ++frames;
            SDL_Event ev;
            while( SDL_PollEvent( &ev ) )
            {
                SDL_PumpEvents();
                if (ev.type == SDL_QUIT)
                    done = true;
            }
            int w, h;
            SDL_GL_MakeCurrent(window, ctx);
            SDL_GetWindowSize(window, &w, &h);
            glViewport(0, 0, w, h);
            Render();
            SDL_GL_SwapWindow(window);
   
        }
   
        /* Print out some timing information */
        now = SDL_GetTicks();
        if (now > then) {
            printf("%2.2f frames per second\n",
                   ((double) frames * 1000) / (now - then));
        }
        quit(0);
        return 0;
    }
};

int Draw3DCube() {
    static float color[8][3] = {
        {1.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 1.0, 1.0},
        {1.0, 1.0, 1.0},
        {1.0, 0.0, 1.0},
        {0.0, 0.0, 1.0}
    };
    static float cube[8][3] = {
        {0.5, 0.5, -0.5},
        {0.5, -0.5, -0.5},
        {-0.5, -0.5, -0.5},
        {-0.5, 0.5, -0.5},
        {-0.5, 0.5, 0.5},
        {0.5, 0.5, 0.5},
        {0.5, -0.5, 0.5},
        {-0.5, -0.5, 0.5}
    };
   
    /* Do our drawing, too. */
    glClearColor(0.128, 0.128, 0.128, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    glBegin(GL_QUADS);

#ifdef SHADED_CUBE
    glColor3fv(color[0]);
    glVertex3fv(cube[0]);
    glColor3fv(color[1]);
    glVertex3fv(cube[1]);
    glColor3fv(color[2]);
    glVertex3fv(cube[2]);
    glColor3fv(color[3]);
    glVertex3fv(cube[3]);
   
    glColor3fv(color[3]);
    glVertex3fv(cube[3]);
    glColor3fv(color[4]);
    glVertex3fv(cube[4]);
    glColor3fv(color[7]);
    glVertex3fv(cube[7]);
    glColor3fv(color[2]);
    glVertex3fv(cube[2]);
   
    glColor3fv(color[0]);
    glVertex3fv(cube[0]);
    glColor3fv(color[5]);
    glVertex3fv(cube[5]);
    glColor3fv(color[6]);
    glVertex3fv(cube[6]);
    glColor3fv(color[1]);
    glVertex3fv(cube[1]);
   
    glColor3fv(color[5]);
    glVertex3fv(cube[5]);
    glColor3fv(color[4]);
    glVertex3fv(cube[4]);
    glColor3fv(color[7]);
    glVertex3fv(cube[7]);
    glColor3fv(color[6]);
    glVertex3fv(cube[6]);
   
    glColor3fv(color[5]);
    glVertex3fv(cube[5]);
    glColor3fv(color[0]);
    glVertex3fv(cube[0]);
    glColor3fv(color[3]);
    glVertex3fv(cube[3]);
    glColor3fv(color[4]);
    glVertex3fv(cube[4]);
   
    glColor3fv(color[6]);
    glVertex3fv(cube[6]);
    glColor3fv(color[1]);
    glVertex3fv(cube[1]);
    glColor3fv(color[2]);
    glVertex3fv(cube[2]);
    glColor3fv(color[7]);
    glVertex3fv(cube[7]);
#else
    glColor3f(1.0, 0.0, 0.0);
    glVertex3fv(cube[0]);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[3]);
   
    glColor3f(0.0, 1.0, 0.0);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[2]);
   
    glColor3f(0.0, 0.0, 1.0);
    glVertex3fv(cube[0]);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[6]);
    glVertex3fv(cube[1]);
   
    glColor3f(0.0, 1.0, 1.0);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[6]);
   
    glColor3f(1.0, 1.0, 0.0);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[0]);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[4]);
   
    glColor3f(1.0, 0.0, 1.0);
    glVertex3fv(cube[6]);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[7]);
#endif
    
    glEnd();
   
    glMatrixMode(GL_MODELVIEW);
    glRotatef(0.2, 1.0, 1.0, 1.0);
}

int main() {
    std::vector<render_operation> operations;
    operations.push_back(Draw3DCube);
    Window cw;
    cw.init();
    cw.run(operations);
}
