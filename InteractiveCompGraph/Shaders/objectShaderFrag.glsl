#version 430

uniform sampler2D TextureDiffuse;
uniform sampler2D TextureSpecular;

in vec3 normalView;
in vec3 lightView;
in vec3 cameraView;
in vec3 vertexPositionView;
in vec2 Texcoord;

out vec4 daColor;

void main()
{	
	vec3 ambientColor = vec3(0.03, 0.03, 0.03);
	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	vec3 mat_color = vec3(1.0, 0.0, 0.0);
	float mat_shininess = 16.0;

	vec3 lightDir = lightView - vertexPositionView;
	vec3 viewDir = cameraView - vertexPositionView;

	vec3 L = normalize(lightDir);
	vec3 V = normalize(viewDir);
	vec3 H = normalize(L + V);
	vec3 N = normalize(normalView);

	//texture
	vec3 diffuse_tex = texture2D(TextureDiffuse, Texcoord).rgb;
	vec3 specular_tex = texture2D(TextureSpecular, Texcoord).rgb;

	// Check whether face is lit
	float checkLit = ceil(dot(L, N));

	//diffuse
	float brightness = clamp(dot(N, L), 0, 1) * checkLit;
	vec3 diffuse = brightness * lightColor * diffuse_tex;

	//specular
	vec3 specular = brightness * lightColor * pow(dot(N, H), mat_shininess) * specular_tex;

	daColor = vec4(ambientColor + diffuse + specular, 1.0f);
}