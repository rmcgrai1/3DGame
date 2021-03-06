uniform vec2 iResolution;
uniform float iGlobalTime;
uniform float iRadius;
uniform sampler2D tex;

varying vec4 vColor;

void main() {
    gl_FragColor = vec4(gl_Color.rgb, gl_Color.a);
}
