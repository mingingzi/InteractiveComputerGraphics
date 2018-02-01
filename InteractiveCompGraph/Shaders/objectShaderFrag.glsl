#version 430
//layout(location = 0) out vec4 daColor;
in vec3 vertexPositionWorld;

out vec4 daColor;

void main()
{	
	daColor = vec4(vertexPositionWorld, 1.0f);
}