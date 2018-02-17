#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 normal;
in layout(location = 2) vec3 texcoord;

uniform mat4 VtoPMatrix ;
uniform mat4 WtoVMatrix ;
uniform mat4 MtoWMatrix ;
uniform mat4 NormalMatrix ;
uniform vec3 LightPosition ;
uniform mat4 LightWtoVMatrix;
uniform vec3 CameraPosition;

out vec3 normalView;
out vec3 lightView;
out vec3 cameraView;
out vec3 vertexPositionView;
out vec2 Texcoord;

void main()
{
	gl_Position = VtoPMatrix * WtoVMatrix * MtoWMatrix * vec4(position, 1.0);
	vertexPositionView = vec3(WtoVMatrix * MtoWMatrix * vec4(position, 1.0));
	normalView = vec3(WtoVMatrix * NormalMatrix * vec4(normal, 0));
	lightView = vec3(LightWtoVMatrix * vec4(LightPosition, 0));
	cameraView = vec3(WtoVMatrix * vec4(CameraPosition, 0));
	Texcoord = vec2(texcoord.x, 1.0 - texcoord.y);
}