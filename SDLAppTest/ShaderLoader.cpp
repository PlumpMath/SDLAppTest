#include "ShaderLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <GLFW/glfw3.h>

using namespace std;

void printLog(GLuint object)
{
    GLint log_length = 0;
    if (glIsShader(object))
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
    else if (glIsProgram(object))
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
    else {
        fprintf(stderr, "printlog: Not a shader or a program\n");
        return;
    }
    
    char* log = (char*)malloc(log_length);
    
    if (glIsShader(object))
        glGetShaderInfoLog(object, log_length, NULL, log);
    else if (glIsProgram(object))
        glGetProgramInfoLog(object, log_length, NULL, log);
    
    fprintf(stderr, "%s", log);
    free(log);
}

GLuint loadShader(string path, int shaderType) {
    
    string code;

    try {
        std::ifstream shaderFile(path);
        std::stringstream stream;
        stream << shaderFile.rdbuf();
        shaderFile.close();
        code = stream.str();
    }
    catch(std::exception e) {
        cerr << "Failed to load shader '" << path << "'" << endl;
        exit(1);
    }

    GLint success;
    GLchar infoLog[512];
    
    int shader = glCreateShader(shaderType);
    
    const char *codeStr = code.c_str();
    glShaderSource(shader, 1, &codeStr, NULL);
    glCompileShader(shader);
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cerr << "Failed to compile shader '" << path << "'" << endl;
        exit(1);
    };
    
    return shader;
}

GLuint ShaderLoader::createProgram(string vertexShader, string fragmentShader) {
    GLuint vs, fs;
    
    vs = loadShader(vertexShader, GL_VERTEX_SHADER);
    fs = loadShader(fragmentShader, GL_FRAGMENT_SHADER);
    
    GLuint program;
    GLint link_ok = GL_FALSE;
    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
    
    if (!link_ok) {
        fprintf(stderr, "glLinkProgram:");
        printLog(program);
        exit(1);
    }
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}

GLuint ShaderLoader::getAttribute(GLuint shaderProgram, std::string attributeName) {
    GLint attribute = glGetAttribLocation(shaderProgram, attributeName.c_str());
    if (attribute == -1) {
        fprintf(stderr, "Could not bind attribute %s\n", attributeName.c_str());
        exit(1);
    }
    return attribute;
}
