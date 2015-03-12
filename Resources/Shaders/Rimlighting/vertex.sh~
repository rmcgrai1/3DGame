uniform mat4 uMVPMatrix;
attribute vec4 vPosition;                  // (x,y,z)
attribute vec4 vColour;                    // (r,g,b,a)

varying vec2 v_vTexcoord;
varying vec3 vNormal;
varying vec4 vColor;
varying float dp;

void main()
{
	gl_Position = ftransform();
	// gl_Position = uMVPMatrix * vec4( in_Position, 1.0);
    
    	vColor = vec4(1.,1.,1.,1.);
	gl_TexCoord[0] = gl_MultiTexCoord0;
    

	vNormal = gl_Normal;
    	vec3 wvPosition = normalize((gl_ModelViewMatrix * gl_Position).xyz);
    	vec3 wvNormal = normalize((gl_ModelViewMatrix * vec4(gl_Normal, 0.0)).xyz);
    	float power = 1.0; //Increase to reduce the effect or decrease to increase the effect
    	dp = pow(dot(wvPosition, wvNormal) + 1.0, power);
}



// M->V->P
// uMVPMatrix

// P-point
// ftransform()

// Model->View
// gl_ModelViewMatrix


//
// gl_ProjectionMatrix
