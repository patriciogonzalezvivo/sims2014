
uniform sampler2D texture;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float time;

void main(){

	float xOffset = 0.0015;
	float yOffset = xOffset;

	float sCoord     = gl_TexCoord[0].s;
    float tCoord     = gl_TexCoord[0].t;
    
    float center     = texture2D(texture, vec2( sCoord, tCoord ) ).r;
    float topLeft    = texture2D(texture, vec2(sCoord - xOffset , tCoord - yOffset  ) ).r;
    float left       = texture2D(texture, vec2(sCoord - xOffset , tCoord            ) ).r;
    float bottomLeft = texture2D(texture, vec2(sCoord - xOffset , tCoord + yOffset  ) ).r;
    float top        = texture2D(texture, vec2(sCoord           , tCoord - yOffset  ) ).r;
    float bottom     = texture2D(texture, vec2(sCoord           , tCoord + yOffset  ) ).r;
    float topRight   = texture2D(texture, vec2(sCoord + xOffset , tCoord - yOffset  ) ).r;
    float right      = texture2D(texture, vec2(sCoord + xOffset , tCoord            ) ).r;
    float bottomRight= texture2D(texture, vec2(sCoord + xOffset , tCoord + yOffset  ) ).r;
    
    float dX = topRight + 2.0 * right + bottomRight - topLeft - 2.0 * left - bottomLeft;
    float dY = bottomLeft + 2.0 * bottom + bottomRight - topLeft - 2.0 * top - topRight;
    
    vec3 N = normalize( vec3( dX, dY, 0.01) );
    
    N *= 0.5;
    N += 0.5;

	gl_FragColor.rgb = N;
	gl_FragColor.a = 1.;
}