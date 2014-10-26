#version 120

uniform sampler2D heightMap;
uniform sampler2D normalMap;
uniform float time;

varying vec2 texCoord;

void main(){
	vec4 color = gl_Color;	// Get Shadows from Vertex Shader

	float altitude = texture2D(heightMap,texCoord).r;	// Get altitud from texture

	color *= mix(	vec4(0.113,0.278,0.075,1.0),	// GREEN
					vec4(1.000,0.944,0.653,1.0),	// BROWN
					altitude);						// mixed acording altitud

	gl_FragColor = color;
}