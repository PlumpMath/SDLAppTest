#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Boilerplate.h"
#include "ShaderLoader.h"
#include "ResourcePath.h"
#include "VboHelper.h"

void game3() {
    Boilerplate::App app = Boilerplate::start(480, 480, "Game 3");
    
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
    
    float data2[] = {
        -0.2,  0.8, 0,   1, 0, 1,
        0.8,  0.2, 0,   1, 1, 0,
        0.0, -0.8, 0,   0, 1, 1,
        
        -0.7,  -0.7, 0,   1, 0, 1,
        0.2,  -0.7, 0,   1, 1, 0,
        0.0,   0.2, 0,   0, 1, 1
    };
    
    GLuint vao1, vao2;
    glGenVertexArrays(1, &vao1);
    glGenVertexArrays(1, &vao2);
    glBindVertexArray(vao1);
    
    GLuint vbo = VboHelper::makeVbo(sizeof(data), data);
    
    GLint attribute_coord3d = ShaderLoader::getAttribute(program, "coord3d");
    GLint attribute_color = ShaderLoader::getAttribute(program, "v_color");
    GLint uniform_translate = glGetUniformLocation(program, "translate");
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glEnableVertexAttribArray(attribute_coord3d);
    glEnableVertexAttribArray(attribute_color);
    
    glVertexAttribPointer(attribute_coord3d, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 6, 0);
    
    glVertexAttribPointer(attribute_color, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 6, (GLvoid*)(sizeof(float) * 3));
    
    // VAO 2
    glBindVertexArray(vao2);
    GLuint vbo2 = VboHelper::makeVbo(sizeof(data2), data2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glEnableVertexAttribArray(attribute_coord3d);
    glEnableVertexAttribArray(attribute_color);
    glVertexAttribPointer(attribute_coord3d, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    glVertexAttribPointer(attribute_color, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(float) * 3));
    
    //glDisableVertexAttribArray(attribute_coord3d);
    //glDisableVertexAttribArray(attribute_color);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.9, 1.0, 0.98, 1.0);
    
    app.render = [&]() {
        glUseProgram(program);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindVertexArray(vao1);
        glUniform3f(uniform_translate, 0.0, 0.0, 0.0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glBindVertexArray(vao2);
        glUniform3f(uniform_translate, 0.5, 0.0, 0.0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glUniform3f(uniform_translate, 0.6, 0.0, 0.0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glUniform3f(uniform_translate, 0.7, 0.0, 0.0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    };
    
    app.tick = [&](float dt) {
        
    };
    
    Boilerplate::loop(app);
    Boilerplate::stop(app);
}

int main() {
    game3();
}
