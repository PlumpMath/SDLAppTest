#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Boilerplate.h"
#include "ShaderLoader.h"
#include "ResourcePath.h"
#include "VboHelper.h"

void game2() {
    Boilerplate::App app = Boilerplate::start(480, 480, "game2");
    
    GLuint program = ShaderLoader::createProgram(getResourcePath("triangle.v", "glsl"),
                                                 getResourcePath("triangle.f", "glsl"));
    
    float data[] = {
        -0.8,  0.8, 0,   1, 0, 1,
         0.8,  0.9, 0,   1, 1, 0,
         0.0, -0.8, 0,   0, 1, 1,
        
        -0.7,  -0.7, 0,   1, 0, 1,
         0.7,  -0.7, 0,   1, 1, 0,
         0.0,   0.7, 0,   0, 1, 1
    };
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint vbo = VboHelper::makeVbo(sizeof(data), data);
    
    GLint attribute_coord3d = ShaderLoader::getAttribute(program, "coord3d");
    GLint attribute_color = ShaderLoader::getAttribute(program, "v_color");
    
    GLuint uniform_translate = glGetUniformLocation(program, "translate");
    
    float x = 0.0f;
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    app.render = [&]() {
        glUseProgram(program);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glClearColor(0.9, 1.0, 0.98, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        
        glEnableVertexAttribArray(attribute_coord3d);
        glEnableVertexAttribArray(attribute_color);
        
        glVertexAttribPointer(attribute_coord3d,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(float) * 6,
                              0);
        
        glVertexAttribPointer(attribute_color,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(float) * 6,
                              (GLvoid*)(sizeof(float) * 3));
        
        glUniform3f(uniform_translate, sinf(x) * 0.5f, 0.0, 0.0);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glDisableVertexAttribArray(attribute_coord3d);
        glDisableVertexAttribArray(attribute_color);
    };
    
    app.tick = [&](float dt) {
        x += dt * 3.0;
    };
    
    Boilerplate::loop(app);
    Boilerplate::stop(app);
}

int main() {
    game2();
}
