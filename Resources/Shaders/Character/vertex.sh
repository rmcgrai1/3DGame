uniform mat4 uMVPMatrix;
uniform mat4 modelMatrix;
attribute vec4 vPosition;                  // (x,y,z)
attribute vec4 vColour;                    // (r,g,b,a)

varying vec4 vWVertex;

varying vec2 v_vTexcoord;
varying vec3 vNormal;
uniform vec3 camNormal;
varying vec4 vColor;
varying vec3 wvNormal;
varying float dp;

uniform float cDirection;


float calcDir(float x, float y) {
	return 3.14159 + atan(y,x);
}

vec3 rotateNormal(vec3 norm, float dir) {
	//mat3 mat = mat3(1, 0, 0, 0, cos(dir), sin(dir), 0, -sin(dir), cos(dir));
	float co = cos(dir), si = sin(dir);

	mat3 mat = mat3(co, si, 0, -si, co, 0, 0, 0, 1);



	return mat*norm;
}

void main() {
	gl_Position = ftransform();
	// gl_Position = uMVPMatrix * vec4( in_Position, 1.0);
    
    	vColor = vec4(1.,1.,1.,1.);
	gl_TexCoord[0] = gl_MultiTexCoord0;
    

	vWVertex = gl_Vertex*modelMatrix;

	float camNX, camNY;
	camNX = camNormal.x;
	camNY = camNormal.y;

	//vNormal = gl_Normal;
	vNormal = rotateNormal(gl_Normal, cDirection+((180. + 45.)/180.*3.14159));
		//vNormal = rotateNormal(vNormal, calcDir(camNX, camNY));
		//vNormal = (gl_ModelViewMatrix * vNormal).xyz;
	
	vec3 wvPosition = normalize((gl_ModelViewMatrix * gl_Position).xyz);
    	wvNormal = normalize((gl_ModelViewMatrix * vec4(vNormal, 0.0)).xyz);
    	float power = 1.0; //Increase to reduce the effect or decrease to increase the effect

    	dp = pow(dot(wvPosition, vNormal) + 1.0, power);
	
	dp = abs(dot(vNormal, camNormal));
}



// M->V->P
// uMVPMatrix

// P-point
// ftransform()

// Model->View
// gl_ModelViewMatrix


//
// gl_ProjectionMatrix
