#pragma once
#include "cyCore.h"
#include "cyPoint.h"
#include "cyTriMesh.h"
#include "cyMatrix.h"

enum Direction {				//camera direction
	LEFT = 0x10,
	RIGHT,
	UP,
	DOWN
	//FORWARD,
	//BACKWARD,
	//NORTHEAST,
	//NORTHWEST,
	//SOUTHWEST,
	//SOUTHEAST
};

class camera {
private:
	cyPoint3f position;
	cyPoint3f front;
	cyPoint3f up;
	float fov;
	float aspect;
	float _near;
	float _far;
	cyMatrix4f WtoVMatrix;
	cyMatrix4f VtoPMatrix;
	cyMatrix4f WtoPMatrix;

	static const float ROTATION_ANGLE;
	static const float MOVEMENT_SPEED;
	cyPoint3f strafeDirection;
	cyMatrix4f IdentityMatrix;
	int frustum;
public:
	camera();
	camera(cyPoint3f, cyPoint3f, cyPoint3f, int);
	cyPoint3f returnPosition();
	cyMatrix4f returnWtoVMatrix();
	cyMatrix4f returnVtoPMatrix();
	cyMatrix4f returnWtoPMatrix();
	void rotate(int dx, int dy);
	camera translate(int dx, int dy, cyPoint3f objectCenter);
	void frustomSwitch(int);
};