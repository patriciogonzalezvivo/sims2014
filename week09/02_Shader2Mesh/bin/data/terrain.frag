#version 120

uniform sampler2D heightMap;
uniform sampler2D normalMap;
uniform float time;

varying vec2 texCoord;

void main(){
	vec4 color = vec4(1.0);
	// color = gl_Color;
	// color = texture2D(heightMap,texCoord);
	// color = texture2D(normalMap,texCoord);
	gl_FragColor = color;
}