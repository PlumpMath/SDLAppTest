#include "VboHelper.h"

GLuint VboHelper::makeVbo(size_t dataSize, void *data) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    return vbo;
}
