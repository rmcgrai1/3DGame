varying vec3 vNormal;
varying vec4 vColor;
varying float dp;
uniform sampler2D tex;
varying vec3 wvNormal;

void main() {
	gl_FragColor = vec4(vec3(dp),1.); //vec4(vNormal,1.);
	//gl_FragColor = vec4(wvNormal,1.);//dp;
}