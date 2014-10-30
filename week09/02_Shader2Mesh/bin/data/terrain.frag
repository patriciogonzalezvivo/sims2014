#version 120

uniform sampler2D heightMap;
uniform sampler2D normalMap;
uniform float time;

varying vec2 texCoord;

void main(){
	vec4 color = vec4(1.0);

	// color = gl_Color;	// Use the color comming from the vertex shader
	
	// color = texture2D(heightMap,texCoord);	// Use the color comming from the texture
	color = texture2D(normalMap,texCoord);	// Use the color comming from the precompute normal shader
	
	gl_FragColor = color;
}