#version 120

uniform sampler2D heightmap;
uniform vec2 resolution;

void main(){

	vec2 st = gl_TexCoord[0].st;

	vec4 color = gl_Color;

	color.rgb = texture2D(heightmap,st).rgb; 

	gl_FragColor = color;
}