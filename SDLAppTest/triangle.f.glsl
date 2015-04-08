#version 330 core

in vec3 frag_color;
out vec4 col;

void main(void) {
    col = vec4(frag_color, 0.5);
}
