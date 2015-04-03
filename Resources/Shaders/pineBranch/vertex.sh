uniform float iGlobalTime;
varying vec2 uvCoords;

void main() {
	gl_Position = ftransform();

	float rX = gl_Vertex.x, rY = gl_Vertex.y, rZ = gl_Vertex.z;	
	float x = gl_Position.x, y = gl_Position.y, z = gl_Position.z;
	float time = (iGlobalTime*20. + rX*2. + rY*3. + rZ*4.)/30.;


	y += sin(time);
	x += cos(time);

	gl_Position.xyz = vec3(x,y,z);

	gl_TexCoord[0] = gl_MultiTexCoord0;



	uvCoords = gl_TexCoord[0].xy;
		uvCoords += -.15-.15*sin(time/5.)*vec2(0.,1.)*uvCoords.y;
}
