uniform float iGlobalTime;
varying vec2 uvCoords;

uniform vec3 camNormal;
varying float dp;


float calcDir(float x, float y) {
	return 3.14159 + atan(y,x);
}

vec3 rotateNormal(vec3 norm, float dir) {
	//mat3 mat = mat3(1, 0, 0, 0, cos(dir), sin(dir), 0, -sin(dir), cos(dir));
	float co = cos(dir), si = sin(dir);

	mat3 mat = mat3(co, si, 0, -si, co, 0, 0, 0, 1);



	return mat*norm;
}

float calcDark() {    

	float camNX, camNY;
	camNX = camNormal.x;
	camNY = camNormal.y;

	vec3 vNormal = gl_Normal;
		//vNormal = rotateNormal(vNormal, calcDir(camNX, camNY));
		//vNormal = (gl_ModelViewMatrix * vNormal).xyz;
	
	vec3 wvNormal = normalize((gl_ModelViewMatrix * vec4(vNormal, 0.0)).xyz);
    	
	return abs(dot(vNormal, camNormal));
}

void main() {
	gl_Position = ftransform();

	gl_TexCoord[0] = gl_MultiTexCoord0;

	dp = calcDark();

	uvCoords = gl_TexCoord[0].xy;
}
