uniform vec4 color;
varying vec4 vtx;
uniform float time;


void main() {

    vec4 newcol = color;

    gl_FragColor = newcol;
}

