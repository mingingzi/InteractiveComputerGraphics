#define _USE_MATH_DEFINES

#include <algorithm>
#include "cyCore.h"
#include "cyPoint.h"
#include "cyTriMesh.h"
#include "cyMatrix.h"

#include "light.h"

light::light() {};
const float light::ROTATION_ANGLE = M_PI / 360 * 0.1;
const float light::MOVEMENT_SPEED = 0.1f;
light::light(cyPoint3f p, cyPoint3f f, cyPoint3f u) {
	position = p;
	front = f;
	up = u;
	fov = 90.0f;
	aspect = 800.0f / 800.0f;
	_near = 0.1f;
	_far = 100.0f;
	WtoVMatrix.SetView(position, position + front, up);
}

cyPoint3f light::returnLightPosition() {
	return position;
}

void light::rotate(int dx, int dy) {
	WtoVMatrix *= cy::Matrix4<float>::MatrixRotationY(-dy * ROTATION_ANGLE * MOVEMENT_SPEED);
	WtoVMatrix *= cy::Matrix4<float>::MatrixRotationX(-dx * ROTATION_ANGLE * MOVEMENT_SPEED);
}
cyMatrix4f light::returnLightWtoVMatrix() {
	return WtoVMatrix;
}