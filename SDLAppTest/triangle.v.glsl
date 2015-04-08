#version 330 core

in vec3 coord3d;
in vec3 v_color;

uniform vec3 translate;

out vec3 frag_color;

void main(void) {
    frag_color = v_color;
    gl_Position = vec4(coord3d + translate, 1.0);
}
