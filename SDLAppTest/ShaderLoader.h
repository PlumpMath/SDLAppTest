#pragma once

//#include <GL/glew.h>
#include <OpenGL/gl3.h>
#include <string>

namespace ShaderLoader {
    
    GLuint createProgram(std::string vertexShader, std::string fragmentShader);
    GLuint getAttribute(GLuint shaderProgram, std::string attributeName);
    
}
