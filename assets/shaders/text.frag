#version 150

in vec4 exColor;
in vec2 exTexcoord;

uniform sampler2D tex;

out vec4 color;

void main(){
        color = texture(tex, exTexcoord);
		color.a = color.r;
		color.r = 0;

		color += exColor;
}
