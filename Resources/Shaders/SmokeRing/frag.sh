uniform vec2 iResolution;
uniform float iGlobalTime;
uniform sampler2D tex;
uniform float iSmoke;


void main()
{


	vec2 uv = gl_TexCoord[0].xy - .5;
	
	//float t = iGlobalTime + ((.25 + .05 * sin(iGlobalTime * .1))/(length(uv.xy) + .07)) * 30.;

	float v, r = length(uv);

	v = pow(r,.8);

	if(r > .45) {
		v -= 20.*(r-.45);
	}	

	//v += sin(t)*v;

	v *= 1.5;

	v *= iSmoke; //sin(iSmoke*3.14159);

	gl_FragColor = vec4(vec3(1.),v);
}
