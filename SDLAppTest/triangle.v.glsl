
attribute vec3 coord3d;
attribute vec3 v_color;

uniform vec3 translate;

varying vec3 frag_color;

// attribute - per vertex
// varying - send to fragment shader
// uniform - for the whole VBO

void main(void) {
    frag_color = v_color;
    gl_Position = vec4(coord3d + translate, 1.0);
}
