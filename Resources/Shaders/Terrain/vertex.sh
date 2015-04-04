uniform mat4 uMVPMatrix;
attribute vec4 vPosition;                  // (x,y,z)
attribute vec4 vColour;                    // (r,g,b,a)

varying vec2 v_vTexcoord;
varying vec3 vNormal;
varying vec4 vColor;
varying float height;
varying float grassWeight;
varying float sandWeight;

varying vec4 vWVertex;
uniform mat4 uMMatrix;
uniform vec3 camNormal;
varying float dp;
uniform float seaLevel;


float calcDir(float x, float y) {
	return 3.14159 + atan(y,x);
}

vec3 rotateNormalZ(vec3 norm, float dir) {
	//mat3 mat = mat3(1, 0, 0, 0, cos(dir), sin(dir), 0, -sin(dir), cos(dir));
	float co = cos(dir), si = sin(dir);

	mat3 mat = mat3(co, si, 0, -si, co, 0, 0, 0, 1);



	return mat*norm;
}

vec3 rotateNormalX(vec3 norm, float dir) {
	float co = cos(dir), si = sin(dir);

	mat3 mat = mat3(1, 0, 0, 0, co, si, 0, -si, co);

	return mat*norm;
}

vec3 rotateNormalY(vec3 norm, float dir) {
	float co = cos(dir), si = sin(dir);

	mat3 mat = mat3(co, 0, -si, 0, 1, 0, si, 0, co);

	return mat*norm;
}

float calcDark() {    

	float camNX, camNY, camNZ;
	camNX = camNormal.x;
	camNY = camNormal.y;
	camNZ = camNormal.z;

	vec3 vNormal = gl_Normal;

		vNormal = rotateNormalX(vNormal, calcDir(sqrt(camNX*camNX + camNY*camNY), camNZ));		
		vNormal = rotateNormalZ(vNormal, calcDir(camNX, camNY));
		//vNormal = (gl_ModelViewMatrix * vNormal).xyz;
	
	vec3 wvNormal = normalize((gl_ModelViewMatrix * vec4(vNormal, 0.0)).xyz);
    	
	return abs(dot(vNormal, camNormal));
}

void main()
{
	gl_Position = ftransform();

	vWVertex = gl_Vertex;//uMMatrix * gl_ModelViewMatrix * gl_Position;
 	//vWVertex = vec4(vWVertex.xyz/vWVertex.w,1.);


	vNormal = gl_Normal;

	height = gl_Vertex.z;
	float tDis = 1. - pow(height/(seaLevel+10.),40.);
    
	tDis = max(0., min(1., tDis));

    	grassWeight = 1.-tDis; 
	sandWeight = tDis;//pow(1.5*tDis,5.);

	dp = 1.;//calcDark();

	gl_TexCoord[0] = gl_MultiTexCoord0;
}
