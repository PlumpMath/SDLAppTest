varying vec3 frag_color;

void main(void) {
    gl_FragColor = vec4(frag_color, 0.5); // vec4(0.2, 0.2, 0.2, 1);
}
