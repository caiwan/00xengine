#version 150

precision highp float;

uniform mat4 Mvp;

//What we receive :
layout(triangles) in;

layout(triangle_strip, max_vertices = 6) out;

in vec3 geom_Color[3];
out vec3 exColor;

void main(){
	int i;

	for(i=0; i < gl_in.length(); ++i){
		gl_Position = Mvp * gl_in[i].gl_Position;
		exColor = geom_Color[i];
		EmitVertex();
	}
	EndPrimitive();
}
