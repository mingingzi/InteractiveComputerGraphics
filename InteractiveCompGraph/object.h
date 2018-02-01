#define NOMINMAX
#define _USE_MATH_DEFINES

#include <iostream>


#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include "cyCore.h"
#include "cyPoint.h"
#include "cyTriMesh.h"
#include "cyMatrix.h"
#include "cyGL.h"



class object {
private:
	cyTriMesh mesh;
	cyPoint3f *vertex;
	cyPoint3f *normal;
	cyMatrix4f MtoWMatrix;
	float numFace;
	cyPoint3f objectCenter;
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
	void calModelMatrix(cyTriMesh);


	int returnNumFace();
	cyPoint3f* returnVertex();
	cyPoint3f* returnNormal();
	cyMatrix4f returnMtoWMatrix();
	cyPoint3f returnObjectCenter();
};