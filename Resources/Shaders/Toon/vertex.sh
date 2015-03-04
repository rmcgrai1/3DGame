/*
Toon vertex shader

Written by TheSnidr
www.thesnidr.com
*/
//attribute vec4 in_Colour;                    // (r,g,b,a)
varying vec2 v_vTexcoord;
varying vec4 vColor;
varying float dp;

void main()
{
	vec4 inColor = vec4(0,0,0,0)

    vec4 object_space_pos = vec4(gl_Vertex.x, gl_Vertex.y, gl_Vertex.z, 1.0);
	gl_Position = ftransform();
//gl_Position = gm_Matrices[MATRIX_WORLD_VIEW_PROJECTION] * object_space_pos;
    
	gl_TexCoord[0] = gl_MultiTexCoord0;
    v_vColor = vec4(1.0, 1.0, 1.0, 1.0);
    
    vec3 vNormal = normalize((inColor.xyz) * 2.0 - 1.0);
    vec3 wvNormal = (gm_Matrices[MATRIX_WORLD_VIEW] * vec4(vNormal, 0.0)).xyz;
    float normalLength = length(wvNormal);
    
    if (dot(normalize((gm_Matrices[MATRIX_WORLD_VIEW] * vec4(in_Position, 1.0)).xyz), wvNormal / normalLength) >= 0.0)
    {
        vColor = vec4(0.0, 0.0, 0.0, 1.0);
        gl_Position = gm_Matrices[MATRIX_WORLD_VIEW_PROJECTION] * vec4(in_Position + in_Normal / normalLength * gl_Position.z / 100.0, 1.0);
    }
    else
    {
        dp = (1.0 - dot((normalize(gm_Matrices[MATRIX_WORLD_VIEW] * vec4(in_Normal, 0.0))).xyz, normalize(vec3(1.0, -1.0, 1.0)))) / 2.0;
    }
}
