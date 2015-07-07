#version 150

in vec3 exColor;
in vec2 exTexcoord;

uniform sampler2D tex;

out vec4 color;

void main(){
        color = texture2D(tex, exTexcoord);

		color += vec4(exColor, 0.);
}
