#version 150

precision highp float;

in vec3 inPosition;
in vec3 inColor;
in vec2 inTexcoord;

uniform mat4 Mvp;

out vec3 exColor;
out vec2 exTexcoord;

void main(){
    gl_Position = Mvp * vec4(inPosition, 1.0);
	exColor = inColor;
	exTexcoord = inTexcoord;
}
