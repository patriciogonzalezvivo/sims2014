#version 120

uniform sampler2D heightMap;
uniform sampler2D normalMap;
uniform float time;

//	Varyings are variables that are passed to the Vector Shader
//
varying vec2 texCoord;

void main(){
	float height = 100.0; // Max altitud

	//	Get offset on Z using the texture
	//
	texCoord = gl_MultiTexCoord0.xy;	// This will be exported to the Fragment Shader
	float offset = texture2D(heightMap,texCoord).r;

	//	Move the point on Z to the right altitud 
	//
	vec4 vert = gl_Vertex;
	vert.z = offset*height;
	// vert.z = pow(offset*100.,0.2)*height;	// Try this to shape the altitud using power (this will smooth the jump)
	
	//	Project the vertex 
	//	(this is the mathematical operation to make the camera render things on perspective)
	//
	gl_Position = gl_ModelViewProjectionMatrix * vert;

	//	Asing a color to the vertex 
	//	(this will be interpolated with other conected vertices )
	//
	gl_FrontColor = vec4(offset);
}
