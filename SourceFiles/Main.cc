#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <vector>
#include <iostream>
#include "./Window.hh"
typedef int (*render_operation)();

const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec2 position;
void main() {
    gl_Position = vec4(position, 0.0, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}
)";
GLuint compileShader(const char* source, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}


GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}


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
    //glRotatef(0.5, 0.0, 1.0, 0.3);
}



int main() {
    std::vector<render_operation> operations;
    operations.push_back(Draw3DCube);
    CagyWindow cw;
    cw.init();
    cw.run(operations);
}
