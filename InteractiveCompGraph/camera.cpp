#define _USE_MATH_DEFINES

#include "camera.h"

#include <algorithm>
#include "cyCore.h"
#include "cyPoint.h"
#include "cyTriMesh.h"
#include "cyMatrix.h"

camera::camera() {};
const float camera::ROTATION_ANGLE = M_PI/360 * 0.1;
const float camera::MOVEMENT_SPEED = 0.01f;
camera::camera(cyPoint3f p, cyPoint3f f, cyPoint3f u, int frustum) {
	position = p;
	front = f;
	up = u;
	fov = 60.0f;
	aspect = 800.0f / 800.0f;
	_near = 1.0f;
	_far = 100.0f;
	WtoVMatrix.SetIdentity();

	WtoVMatrix.SetView(position, position + front, up);
	VtoPMatrix.SetPerspective((M_PI * fov) / 180, aspect, _near, _far);
	
	//WtoPMatrix = VtoPMatrix * WtoVMatrix;
	IdentityMatrix.SetIdentity();
	strafeDirection = cyPoint3f(1.0f, 0.0f, 0.0f);
}

cyPoint3f camera::returnPosition() {
	return position;
};

cyMatrix4f camera::returnVtoPMatrix() {
	cyMatrix4f &p = VtoPMatrix;
	return  p;
};

cyMatrix4f camera::returnWtoVMatrix() {
	return WtoVMatrix;
};

cyMatrix4f camera::returnWtoPMatrix() {
	return WtoPMatrix;
};

void camera::rotate(int dx, int dy) {
	strafeDirection = front.Cross(up);
	cyMatrix4f rotatory = IdentityMatrix.MatrixRotation(strafeDirection, -dy * ROTATION_ANGLE);
	cyMatrix4f rotatorx = IdentityMatrix.MatrixRotation(up, -dx * ROTATION_ANGLE);
	front = cyMatrix3f(rotatory * rotatorx) * front;
	WtoVMatrix.SetView(position, position + front, up);
	//..return camera(position, front, up, frustum);
}
camera camera::translate(int dx, int dy, cyPoint3f objectCenter) {
	if (dy > 0) position -= MOVEMENT_SPEED * (objectCenter - position);
	if (dy < 0) position += MOVEMENT_SPEED * (objectCenter - position);
	return camera(position, front, up, frustum);
}
void camera::frustomSwitch(int frustum) {
	if (frustum == 1) {
		VtoPMatrix.OrthogonalizeX();
		VtoPMatrix.OrthogonalizeY();
		VtoPMatrix.OrthogonalizeZ();
	}
	else if (frustum == 0) {
		VtoPMatrix.SetPerspective((M_PI * fov) / 180, aspect, _near, _far);
	}
	else {

	}
}