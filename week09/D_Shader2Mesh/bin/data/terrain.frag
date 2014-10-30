#version 120

uniform sampler2D heightMap;
uniform sampler2D normalMap;
uniform float time;

varying vec4 vert;
varying vec2 texCoord;



void main(){
	vec4 color = gl_Color;
	// color = texture2D(normalMap,texCoord);
	
	vec3 lightPos = vec3(1000*sin(time),1000*cos(time),500);

	vec3 normal = (texture2D(normalMap,texCoord).rgb-0.5)*2.0;
	vec3 diff = normalize(lightPos - vert.xyz);
	color.rgb = vec3(dot(diff,normal));

	gl_FragColor = color;
}