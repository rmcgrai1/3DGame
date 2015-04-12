varying vec3 vNormal;
uniform vec4 iColor;
varying float dp;
varying float lp;

uniform int textureBound;
uniform sampler2D tex;
varying vec3 wvNormal;
uniform float iHit;

uniform float iGlobalTime;
uniform vec3 rCamPos;
uniform vec3 charPos;
varying vec4 vWVertex;

uniform int lightNum;
uniform float lightRads[100];
uniform vec4 lightColors[100];
uniform vec3 lights[100];

uniform int shadowNum;
uniform vec3 shadows[100];
float zDir = (iGlobalTime*10. + 90.)/180.*3.14159;
float xN = cos(zDir), zN = sin(zDir);
float dayAmt = (zN+1.)/2.;
vec3 sunDirection = normalize(vec3(0.,zN,xN));


bool isInsideBox(vec2 pt, vec2 ptBox, float r) {
	return ((pt.x > ptBox.x - r && pt.x < ptBox.x + r) && (pt.y > ptBox.y - r && pt.y < ptBox.y + r));
}

float sqr(float x) {
	return x*x;
}

float contain(float val) {
	return max(0.,min(1.,val));
}

float calcDis(vec3 pt1, vec3 pt2) {
	return sqrt(sqr(pt1.x-pt2.x) + sqr(pt1.y-pt2.y) + sqr(pt1.z-pt2.z));
}

float calcDis(vec2 pt1, vec2 pt2) {
	return sqrt(sqr(pt1.x-pt2.x) + sqr(pt1.y-pt2.y));
}

vec4 addLighting(vec4 oriColor, float lightness) {

	float totalLight = 1.;

	for(int i = 0; i < lightNum; i++) {
		vec3 curLightPos = lights[i];
		vec4 curLightColor = lightColors[i];
		float curLightR = lightRads[i];
	
		float dis = calcDis(vWVertex.xyz,curLightPos.xyz); 
	
		float darkness = contain(pow(dis/curLightR, 1)); // 2
		//float light = pow(1.-contain((dis/100.))*.9,2.);

		totalLight *= darkness;

		oriColor.rgb += curLightColor.rgb*(1.-darkness)*curLightColor.a;
	}

	lightness = contain(lightness + (1.-totalLight));

	oriColor.rgb *= lightness; //mixColors(newCol, vec4(1.,1.,.5,light));
	return oriColor;
}

/*vec4 addFog(vec4 oriColor) {

	vec4 newCol = oriColor;
	
	float dis = calcDis(vWVertex.xyz,vec3(rCamPos.xyz)); 
	
	float col = contain((dis/2000.));

	newCol.a = 1.-col;

	return mixColors(newCol, vec4(getFogColor().rgb,col));
}*/

float addShadows() {
	
	float sh = 1.;
	for(int i = 0; i < shadowNum; i++) {
		vec3 curPos = shadows[i];
		float curR = curPos.z;

		if(curPos.xy == charPos.xy || !isInsideBox(vWVertex.xy,curPos.xy,curR))
			continue;

		float dis = calcDis(vWVertex.xy,curPos.xy);
	
		sh *= pow(contain((dis/curR)),2.);
	}

	return sh;
}




void main() {

	gl_FragColor = vec4(1.,1.-iHit,1.-iHit,1.); //vec4(vNormal,1.);


	if(textureBound == 1)
		gl_FragColor *= texture2D(tex,gl_TexCoord[0].xy);
	else
		gl_FragColor *= iColor;	

	gl_FragColor.r = contain(gl_FragColor.r+lp);
	gl_FragColor.g = contain(gl_FragColor.g+lp);
	gl_FragColor.b = contain(gl_FragColor.b+lp);

	gl_FragColor.rgb *= dp;

	gl_FragColor = addLighting(gl_FragColor,contain(1.5*addShadows()));
}
