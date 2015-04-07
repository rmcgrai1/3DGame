uniform float iGlobalTime;
uniform sampler2D tex;
uniform vec3 lights[1];
uniform vec4 iColor;

varying vec2 uvCoords;
varying float dp;

vec4 mixColors(vec4 col1, vec4 col2) {
	float a1 = col1.a, a2 = col2.a;
	float aTot = a1+a2;
	float w1 = a1/aTot, w2 = a2/aTot;

	vec4 mixed = vec4(col1.rgb*w1 + col2.rgb*w2, 1.);

	return mixed;
}

void main() {
	float dark = 1.-uvCoords.y, light = 1.-dark;

	dark = pow(dark, 3.);
	light = .5*pow(light, 5.);

	gl_FragColor = mixColors(texture2D(tex, uvCoords), vec4(iColor.rgb,.5));
	
	gl_FragColor.rgb -= dark*vec3(2.,1.5,1.5);
	gl_FragColor.rgb += .5*light*vec3(.5,.8,.8);

	gl_FragColor.rgb *= dp;
}
