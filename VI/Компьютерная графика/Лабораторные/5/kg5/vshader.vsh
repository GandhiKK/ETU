attribute vec4 vertex;
uniform mat4 mvp;
varying vec4 vtx;
uniform float time;

void main() {
    float t = vertex.x*5*cos(time);
    gl_Position = mvp * vec4(vertex.x, vertex.y*sin(t*0.5+time), vertex.z, 1.0);
    vtx = vertex;
}
