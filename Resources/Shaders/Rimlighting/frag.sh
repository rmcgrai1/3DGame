varying vec2 v_vTexcoord;
varying vec4 v_vColour;
varying float dp;

void main()
{
    gl_FragColor = v_vColour * texture2D( gm_BaseTexture, v_vTexcoord ) + dp;
}
