/*
Toon fragment shader

Written by TheSnidr
www.thesnidr.com
*/

varying vec4 vColor;
varying float dp;
uniform sampler2D tex;
uniform sampler2D celShadingSample;

void main()
{
    gl_FragColor = v_vColor * texture2D(tex, gl_Texcoord[0].xy) * texture2D(celShadingSample, vec2(dp, 0.0));
}

