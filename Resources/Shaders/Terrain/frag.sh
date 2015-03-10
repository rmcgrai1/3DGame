uniform float iGlobalTime;
varying vec4 vColor;
varying float grassWeight;
varying float sandWeight;
varying float height;
uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform vec3 lights[1];

varying vec4 vWVertex;
varying mat4 uMMatrix;



float sqr(float x) {
	return x*x;
}

float calcDis(vec3 pt1, vec3 pt2) {
	return sqrt(sqr(pt1.x-pt2.x) + sqr(pt1.y-pt2.y) + sqr(pt1.y-pt2.y));
}

float contain(float val) {
	return max(0.,min(1.,val));
}

vec4 mixColors(vec4 col1, vec4 col2) {
	float a1 = col1.a, a2 = col2.a;
	float aTot = a1+a2;
	float w1 = a1/aTot, w2 = a2/aTot;

	vec4 mixed = vec4(col1.rgb*w1 + col2.rgb*w2, 1.);

	return mixed;
}

vec4 addLighting(vec4 oriColor) {

	vec4 newCol = oriColor;

	vec3 curLightPos = lights[0];

	
	float dis = calcDis(vWVertex.xyz,curLightPos); 
	
	float col = contain((dis/100.))*.7;

	newCol.a = 1.-col;

	return mixColors(newCol, vec4(0.,0.,0.,col));
}


#define TAU 6.28318530718
#define MAX_ITER 5

vec4 caustics(vec4 fragColor, vec2 uv) {
	float time = iGlobalTime * .5+23.0;
	// uv should be the 0-1 uv of texture...



	float hDis = 1. - (height)/200.;
	hDis = max(0., min(1., hDis));

	vec2 p = mod(uv*TAU, TAU)-250.0;

	vec2 i = vec2(p);
	float c = 1.0;
	float inten = .005;

	for (int n = 0; n < MAX_ITER; n++) 
	{
		float t = time * (1.0 - (3.5 / float(n+1)));
		i = p + vec2(cos(t - i.x) + sin(t + i.y), sin(t - i.y) + cos(t + i.x));
		c += 1.0/length(vec2(p.x / (sin(i.x+t)/inten),p.y / (cos(i.y+t)/inten)));
	}
	c /= float(MAX_ITER);
	c = 1.17-pow(c, 1.4);
	vec4 colour = vec4(vec3(pow(abs(c), 8.0)), hDis);

	vec4 aColor = vec4(colour.rgb, colour.r);
	aColor = vec4(clamp(aColor.rgb + vec3(0.0, 0.35, 0.5), 0.0, 1.0), aColor.a);
    
	vec4 mixed = mixColors(colour, aColor);
		mixed = vec4(mixed.rgb, (colour.a+aColor.a)/2.);

	return mixColors(mixed, fragColor);
}

void main() {
	vec4 grassColor = vec4(texture2D(Texture0, gl_TexCoord[0].xy).rgb, grassWeight);
	vec4 sandColor = vec4(texture2D(Texture1, gl_TexCoord[0].xy).rgb, sandWeight);

	gl_FragColor = mixColors(grassColor, sandColor);

	if(height < 200.)
		gl_FragColor = caustics(gl_FragColor, gl_TexCoord[0].xy);

	gl_FragColor = addLighting(gl_FragColor);
}
