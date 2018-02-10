#pragma once

#include "cyCore.h"
#include "cyPoint.h"
#include "cyTriMesh.h"
#include "cyMatrix.h"

class light {
private:
	cyPoint3f position;
	cyPoint3f front;
	cyPoint3f up;
	float fov;
	float aspect;
	float _near;
	float _far;
	cyMatrix4f WtoVMatrix;

	static const float ROTATION_ANGLE;
	static const float MOVEMENT_SPEED;

public:
	light();
	light(cyPoint3f, cyPoint3f, cyPoint3f);

	cyPoint3f returnLightPosition();
	void rotate(int dx, int dy);
	cyMatrix4f returnLightWtoVMatrix();
};