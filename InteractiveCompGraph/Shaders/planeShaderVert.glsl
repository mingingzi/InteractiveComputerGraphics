#version 430

in layout(location = 0) vec3 position;


uniform mat4 VtoPMatrix ;
uniform mat4 WtoVMatrix ;
uniform mat4 MtoWMatrix ;
uniform vec3 CameraPosition;

out vec3 cameraView;
out vec3 vertexPositionView;
out vec2 Texcoord;

void main()
{
	gl_Position = VtoPMatrix * WtoVMatrix * MtoWMatrix * vec4(position, 1.0);
	vertexPositionView = vec3(WtoVMatrix * MtoWMatrix * vec4(position, 1.0));

	cameraView = vec3(WtoVMatrix * vec4(CameraPosition, 0));
	Texcoord = vec2(position.xy + vec2(1,1))/2.0;
}