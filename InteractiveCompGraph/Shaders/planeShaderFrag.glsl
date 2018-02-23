#version 430

uniform sampler2D renderTex;

in vec3 cameraView;
in vec3 vertexPositionView;
in vec2 Texcoord;

out vec4 daColor;

void main()
{	
	vec3 diffuse_tex = texture2D(renderTex, Texcoord).rgb;
	daColor = vec4(diffuse_tex, 1.0f) + vec4(0.1, 0.1, 0.1, 1.0f);
}