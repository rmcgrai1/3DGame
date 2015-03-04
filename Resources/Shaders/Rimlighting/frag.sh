varying vec4 vColor;
varying float dp;
uniform sampler2D tex;

void main() {
	gl_FragColor = texture2D(tex, gl_TexCoord[0].xy) + dp;
}
