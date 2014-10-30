#version 120

uniform sampler2D heightmap;
uniform float time;

void main(){
	gl_TexCoord[0] = gl_MultiTexCoord0;

	float height = texture2D(heightmap,gl_MultiTexCoord0.st).r;
	
	vec4 vertex = gl_Vertex;
	vertex.z = height*100.0;

	gl_Position = gl_ModelViewProjectionMatrix * vertex;
	gl_FrontColor = gl_Color;
}
