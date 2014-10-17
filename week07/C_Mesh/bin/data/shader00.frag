
uniform sampler2D texture;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float time;

float PI = 3.14;

float rand(vec2 n) { 
    return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

float noise(vec2 p){
    vec2 ip = floor(p);
    vec2 u = fract(p);
    u = u*u*(3.0-2.0*u);

    float res = mix(
        mix(rand(ip),rand(ip+vec2(1.0,0.0)),u.x),
        mix(rand(ip+vec2(0.0,1.0)),rand(ip+vec2(1.0,1.0)),u.x),u.y);
    return res*res;
}

void main(){

	vec2 pos = gl_TexCoord[0].xy;

	float n = noise( pos * sin(time)*(mouse.x) );
	float radius = 0.1;
	vec2 offset;
	offset.x = radius * cos(n);
	offset.y = radius * sin(n);

	vec4 color = texture2D(texture,pos+offset);

	gl_FragColor = color;
}