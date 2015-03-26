uniform float iGlobalTime;
varying vec4 vColor;
uniform vec3 iCamPos;
uniform vec2 iResolution;
uniform vec3 iCamDir;
uniform vec3 rCamPos;
varying float grassWeight;
varying float sandWeight;
varying float height;
uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform vec3 lights[1];

varying vec4 vWVertex;
varying mat4 uMMatrix;
uniform float seaLevel;
uniform sampler2D noiseTex;

	vec3 sunColor = vec3(1.8, 1.1, 0.6);
	vec3 skyColor = vec3(0.4, 0.6, 0.85);
	vec3 sunLightColor = vec3(1.5, 1.25, 0.9);
	vec3 skyLightColor = vec3(0.15, 0.2, 0.3);
	vec3 indLightColor = vec3(0.4, 0.3, 0.2);
	vec3 cloudsColor = vec3(1.0, 1.0, 1.0);
	vec3 horizonColor = vec3(0.7, 0.75, 0.8);
	vec3 fogColorB = vec3(0.7, 0.8, 0.9);
	vec3 fogColorR = vec3(0.8, 0.7, 0.6);

	vec3 sunDirection = normalize(vec3(0.6, 0.8, 0.5));

	vec2 uv;


	mat3 fromEuler(vec3 ang) {
		vec2 a1 = vec2(sin(ang.x),cos(ang.x));
	    vec2 a2 = vec2(sin(ang.y),cos(ang.y));
	    vec2 a3 = vec2(sin(ang.z),cos(ang.z));
	    mat3 m;
	    m[0] = vec3(a1.y*a3.y+a1.x*a2.x*a3.x,a1.y*a2.x*a3.x+a3.y*a1.x,-a2.y*a3.x);
		m[1] = vec3(-a2.y*a1.x,a1.y*a2.y,a2.x);
		m[2] = vec3(a3.y*a1.x*a2.x+a1.y*a3.x,a1.x*a3.x-a1.y*a3.y*a2.x,a2.y*a3.y);
		return m;
	}

	float cloudsHeight = 800.0;
	float cloudsDensity = 0.3;
	float cloudsCover = 0.2;

	float noiseT(in vec2 p) {
		return texture2D(noiseTex, p / 256.0, -100.0).x * 2.0 - 1.0;
	}

	float fBm(in vec2 p) {
	    float sum = 0.0;
	    float amp = 1.0;
	    for(int i = 0; i < 4; i++) {
		sum += amp * noiseT(p);
		amp *= 0.5;
		p *= 2.0;
	    }
	    return sum;
	}

	float fBmC(in vec2 p) {
	    float sum = 0.0;
	    float amp = 1.0;
	    for(int i = 0; i < 5; i++) {
		sum += amp * noiseT(p);
		amp *= 0.5;
		p *= 2.0;
	    }
	    return sum;
	}



	float raymarchShadow(in vec3 ro, in vec3 rd, float tmin, float tmax) {
	    float sh = 1.0;
	    float t = tmin;
	    for(int i = 0; i < 50; i++) {
		vec3 p = ro + rd * t;
		float d = p.y - fBm(p.xz);
		sh = min(sh, 16.0 * d / t);
		t += 0.5 * d;
		if (d < (0.001 * t) || t > tmax)
		    break;
	    }
	    return sh;
	}


float sqr(float x) {
	return x*x;
}

float calcDis(vec3 pt1, vec3 pt2) {
	return sqrt(sqr(pt1.x-pt2.x) + sqr(pt1.y-pt2.y) + sqr(pt1.y-pt2.y));
}

float contain(float val) {
	return max(0.,min(1.,val));
}

vec4 getFogColor() {
	uv = gl_FragCoord.xy;
	vec2 p = gl_FragCoord.xy / iResolution.xy * 2.0 - 1.0;

	//eye + vec3(cos(iGlobalTime * 0.1) * 1.25, sin(iGlobalTime * 0.1) * 0.5 + 0.15, iGlobalTime * 0.5);

	vec3 ro = iCamPos - vec3(0.,seaLevel,0.);


	vec3 ang = iCamDir;   
	vec3 dir = normalize(vec3(p,-2.5));
	vec3  rd = normalize(dir) * fromEuler(ang);

	// the powerful sun dot
	float sunDot = clamp(0, 0.0, 1.0);

	// terrain marching
	vec3 color;

	// sky and sun
	float sky = clamp(0.6 * (1.0 - 0.8 * rd.y), 0.0, 1.0);
	float diffuse = clamp(0.4 * sunDot, 0.0, 1.0);
	color = sky * skyColor + diffuse * skyLightColor;

	// horizon
	color = mix(color, horizonColor, pow(1.0 - rd.y, 4.0));

	// gamma correction
	vec3 gamma = vec3(1.0 / 2.2);
	return vec4(pow(color, gamma), 1.0);
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

vec4 addFog(vec4 oriColor) {

	vec4 newCol = oriColor;

	vec3 curLightPos = lights[0];

	
	float dis = calcDis(vWVertex.xyz,vec3(rCamPos.xyz)); 
	
	float col = contain((dis/1000.));

	newCol.a = 1.-col;

	return mixColors(newCol, vec4(getFogColor().rgb,col));
}


#define TAU 6.28318530718
#define MAX_ITER 5

vec4 caustics(vec4 fragColor, vec2 uv) {
	float time = iGlobalTime * .5+23.0;
	// uv should be the 0-1 uv of texture...



	float hDis = 1. - (height)/seaLevel;
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
	vec4 colour = vec4(vec3(pow(abs(c), 8.0)), (pow(abs(c), 8.0))*(1.-hDis));

	//vec4 aColor = vec4(colour.rgb, 1.0);
	//aColor = vec4(clamp(aColor.rgb + vec3(0.0, 0.35, 0.5), 0.0, 1.0), aColor.a);
    
	//vec4 mixed = mixColors(colour, aColor);
	//	mixed = vec4(mixed.rgb, (colour.a+aColor.a)/2.);

	colour = vec4(clamp(colour.rgb + vec3(0.0, 0.35, 0.5), 0.0, 1.0), 1.-hDis);
	colour = mixColors(colour, vec4(clamp(vec3(0.,0.,0.) + vec3(0.0, 0.35, 0.5), 0.0, 1.0), 1.0));
	colour.a *= (.4 + .6*hDis);

	return mixColors(colour, fragColor);
}

void main() {
	vec4 grassColor = vec4(texture2D(Texture0, gl_TexCoord[0].xy).rgb, grassWeight);
	vec4 sandColor = vec4(texture2D(Texture1, gl_TexCoord[0].xy).rgb, sandWeight);

	gl_FragColor = mixColors(grassColor, sandColor);

	if(height < seaLevel)
		gl_FragColor = caustics(gl_FragColor, gl_TexCoord[0].xy);

	gl_FragColor = addFog(addLighting(gl_FragColor));
}