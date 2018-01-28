#pragma once

#include <GL\freeglut.h>
#include <GL\GL.h>
#include "cyCore.h"
#include "cyPoint.h"
#include "cyTriMesh.h"



class object {
private:
	cyTriMesh mesh;
	cyPoint3f *vertex;
	cyPoint3f *normal;
	float numFace;
public:
	object();
	object(char *filename);
	// load obj file
	void getMesh(char *filename);
	// get vertex
	void getVertex(cyTriMesh);
	//get normal
	void getNormal(cyTriMesh);
	// get model matrix
	/*void calModelMatrix(cyTriMesh);


	void changeBackPlaneModelMatrix();
	void changeUnderPlaneModelMatrix();
*/
	int returnNumFace();
	cyPoint3f* returnVertex();
	cyPoint3f* returnNormal();


};