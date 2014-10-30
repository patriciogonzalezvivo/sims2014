#version 120

uniform sampler2D heightMap;
uniform sampler2D normalMap;
uniform float time;

varying vec4 vert;
varying vec2 texCoord;

void main(){
	float height = 100.0; // Max altitud

	texCoord = gl_MultiTexCoord0.xy;
	float offset = texture2D(heightMap,texCoord).r;

	vert = gl_Vertex;
	// vert.z = offset*height;
	vert.z = pow(offset*100.,0.2)*height;

	

	gl_Position = gl_ModelViewProjectionMatrix * vert;
	gl_FrontColor = gl_Color;
}
