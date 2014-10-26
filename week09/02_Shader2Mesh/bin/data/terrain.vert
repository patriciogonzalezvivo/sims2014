#version 120

uniform sampler2D heightMap;
uniform sampler2D normalMap;
uniform float time;

varying vec2 texCoord;

void main(){
	float height = 100.0; 

	texCoord = gl_MultiTexCoord0.xy;
	float offset = texture2D(heightMap,texCoord).r;

	vec4 vert = gl_Vertex;
	vert.z = pow(offset*100.,0.2)*height;
	
	gl_Position = gl_ModelViewProjectionMatrix * vert; 
	gl_FrontColor = vec4(offset);
}
