#version 430

in layout(location = 0) vec3 position;

uniform mat4 VtoPMatrix ;
uniform mat4 WtoVMatrix ;
uniform mat4 MtoWMatrix ;

out vec3 vertexPositionWorld;

void main()
{
	gl_Position = VtoPMatrix * WtoVMatrix * MtoWMatrix * vec4(position, 1.0);
	//gl_Position = vec4(position, 1.0);
	vertexPositionWorld = vec3(0.5 * vec4(position, 1));
}