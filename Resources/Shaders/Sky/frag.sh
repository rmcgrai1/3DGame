// many thanks to IQ for his useful articles !

uniform vec2 iResolution;
uniform float iGlobalTime;
uniform vec3 iCamPos;
uniform vec3 iCamDir;
varying vec3 vVertex;
uniform float seaLevel;
uniform sampler2D tex;


vec3 sunColor = vec3(1.8, 1.1, 0.6);
vec3 dayColor = vec3(0.4, 0.6, 0.85);
vec3 nightColor = vec3(0.22,0.10,0.32);

vec3 sunLightColor = vec3(1.5, 1.25, 0.9);
vec3 skyLightColor = vec3(0.15, 0.2, 0.3);
vec3 indLightColor = vec3(0.4, 0.3, 0.2);
vec3 cloudsColor = vec3(1.0, 1.0, 1.0);
vec3 horizonColor = vec3(0.7, 0.75, 0.8);
vec3 fogColorB = vec3(0.7, 0.8, 0.9);
vec3 fogColorR = vec3(0.8, 0.7, 0.6);

//vec3 sunDirection = normalize(vec3(0.6, 0.8, 0.5));

float zDir = iGlobalTime/180.*3.14159*10.;
float xN = cos(zDir), zN = sin(zDir);
float dayAmt = (zN+1.)/2.;

vec3 sunDirection = normalize(vec3(0.,zN,xN));

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
	return texture2D(tex, p / 256.0, -100.0).x * 2.0 - 1.0;
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

vec3 dayNightColor(vec3 colDay, vec3 colNight) {
	return dayAmt*colDay + (1.-dayAmt)*colNight;
}

void main() {

    uv = gl_FragCoord.xy;
    vec2 p = gl_FragCoord.xy / iResolution.xy * 2.0 - 1.0;

   //eye + vec3(cos(iGlobalTime * 0.1) * 1.25, sin(iGlobalTime * 0.1) * 0.5 + 0.15, iGlobalTime * 0.5);

	vec3 ro = iCamPos - vec3(0.,seaLevel,0.);


	vec3 ang = iCamDir;   
	vec3 dir = normalize(vec3(p,-2.5));
	vec3  rd = normalize(dir) * fromEuler(ang);

    // the powerful sun dot
    float sunDot = clamp(dot(sunDirection, rd), 0.0, 1.0);

    // terrain marching
    vec3 color;

	vec3 skyColor = dayNightColor(dayColor, nightColor);
    
    // sky and sun
    float sky = clamp(0.6 * (1.0 - 0.8 * rd.y), 0.0, 1.0);
    float diffuse = clamp(0.4 * sunDot, 0.0, 1.0);
    color = sky * skyColor + /*sunDot*sunColor*/ diffuse * skyLightColor;

    // clouds
    float t = (cloudsHeight - ro.y) / rd.y;
    if (t > 0.0) {
        vec3 pos = ro + rd * t;
        pos.z += iGlobalTime * 20.0;
        float clouds = fBmC(0.0025 * pos.xz) * cloudsDensity + cloudsCover;
        color = mix(color, mix(cloudsColor * 1.1, sunColor + diffuse * sunLightColor, 0.25), 0.8 * smoothstep(0.1, 0.9, clouds));
    }

        // horizon
        color = mix(color, dayNightColor(horizonColor,horizonColor*.3), pow(1.0 - rd.y, 4.0));

	color += pow(sunDot, 800.0) * sunColor;

    // gamma correction
    vec3 gamma = vec3(1.0 / 2.2);
    gl_FragColor = vec4(pow(color, gamma), 1.0);
}
