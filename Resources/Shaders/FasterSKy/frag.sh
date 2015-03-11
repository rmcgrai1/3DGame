// many thanks to IQ for his useful articles !

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

float cloudsHeight = 800.0;
float cloudsDensity = 0.3;
float cloudsCover = 0.2;

float noiseT(in vec2 p) {
    return texture2D(iChannel0, p / 256.0, -100.0).x * 2.0 - 1.0;
}

float noiseW(in vec2 p) {
    return texture2D(iChannel0, (p - 16.0) / 256.0, -100.0).x;
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

float fBmW(in vec2 p) {
    float sum = 0.0;
    float amp = 0.5;
    for(int i = 0; i < 5; i++) {
        sum += amp * noiseT(p);
        amp *= 0.5;
        p *= 2.0;
    }
    return sum * 0.2;
}

float raymarchAO(in vec3 ro, in vec3 rd, float tmin) {
    float ao = 0.0;
    for (float i = 0.0; i < 5.0; i++) {
        float t = tmin + pow(i / 5.0, 2.0);
        vec3 p = ro + rd * t;
        float d = p.y - fBm(p.xz);
        ao += max(0.0, t - 0.5 * d - 0.05);
    }
    return 1.0 - 0.4 * ao;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {

    vec2 p = fragCoord.xy / iResolution.xy * 2.0 - 1.0;

    vec3 eye = vec3(0.0, 2.0, 1.0);
    vec2 rot = 6.2831 * (vec2(0.0, 0.25) + vec2(1.0, 0.25) * (iMouse.xy - iResolution.xy * 0.5) / iResolution.x);
    eye.yz = cos(rot.y) * eye.yz + sin(rot.y) * eye.zy * vec2(-1.0, 1.0);
    eye.xz = cos(rot.x) * eye.xz + sin(rot.x) * eye.zx * vec2(1.0, -1.0);

    vec3 ro = eye + vec3(cos(iGlobalTime * 0.1) * 1.25, sin(iGlobalTime * 0.1) * 0.5 + 0.15, iGlobalTime * 0.5);
    ro.y += 2.5;
    vec3 ta = vec3(0.0, -0.75, 0.0);

    // build camera matrix
    vec3 cw = normalize(ta - eye);
    vec3 cu = normalize(cross(vec3(0.0, 1.0, 0.0), cw));
    vec3 cv = normalize(cross(cw, cu));
    mat3 cam = mat3(cu, cv, cw);

    // compute ray direction
    vec3 rd = cam * normalize(vec3(p.xy, 1.0));

    // the powerful sun dot
    float sunDot = clamp(dot(sunDirection, rd), 0.0, 1.0);

    // terrain marching
    float tmin = 0.1;
    float tmax = 50.0;
    float t;
    vec3 color;
        // sky and sun
        float sky = clamp(0.6 * (1.0 - 0.8 * rd.y), 0.0, 1.0);
        float diffuse = clamp(0.4 * sunDot, 0.0, 1.0);
        color = sky * skyColor + pow(sunDot, 800.0) * sunColor + diffuse * skyLightColor;

        // clouds
        t = (cloudsHeight - ro.y) / rd.y;
        if (t > 0.0) {
            vec3 pos = ro + rd * t;
            pos.z += iGlobalTime * 20.0;
            float clouds = fBmC(0.0025 * pos.xz) * cloudsDensity + cloudsCover;
            color = mix(color, mix(cloudsColor * 1.1, sunColor + diffuse * sunLightColor, 0.25), 0.8 * smoothstep(0.1, 0.9, clouds));
        }

        // horizon
        color = mix(color, horizonColor, pow(1.0 - rd.y, 4.0));

    // gamma correction
    vec3 gamma = vec3(1.0 / 2.2);
    fragColor = vec4(pow(color, gamma), 1.0);
}
