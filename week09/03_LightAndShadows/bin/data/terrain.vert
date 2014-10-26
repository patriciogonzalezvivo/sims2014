#version 120

uniform sampler2D heightMap;
uniform sampler2D normalMap;
uniform float time;

varying vec4 diffuseColor;
varying vec3 lightDir;
varying vec3 vecNormal;
varying vec2 texCoord;

void main(){
	float height = 100.0; // Max altitud

	texCoord = gl_MultiTexCoord0.xy;
	float offset = texture2D(heightMap,texCoord).r;	// get altitud from texture (0.0-1.0)

	//	Move vertex to the right altitud
	//
	vec4 vert = gl_Vertex;
	vert.z = pow(offset*100.,0.2)*height;
	gl_Position = gl_ModelViewProjectionMatrix * vert;

	//	Get normal using precompute normals
	//
	vecNormal = (texture2D(normalMap,texCoord).xyz*2.0-vec3(1.0));

	//	Compute light position and the consecuent direction from the vertex been compute
	//
	vec3 lightPos = vec3(gl_ModelViewProjectionMatrix * gl_LightSource[0].position);
	lightDir = normalize(lightPos-vert.xyz);

	//	Calculate how much light this vertext recieve based on their angle
	//
	float NdotL = max(pow(dot(vecNormal, lightDir),0.5), 0.0);

	//	Compute diffuse color
	//
	diffuseColor = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;

	//	Compute Shadow
	//
	gl_FrontColor = NdotL * diffuseColor;
	gl_FrontColor.a = 1.0;
}
