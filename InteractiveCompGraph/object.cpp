#define NOMINMAX
#define _USE_MATH_DEFINES

#include <iostream>
#include <algorithm>
//#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include "cyCore.h"
#include "cyPoint.h"
#include "cyTriMesh.h"
//#include "cyMatrix.h"
//#include "cyGL.h"

#include "object.h"

using namespace std;


void object::getMesh(char *filename) {
	mesh.LoadFromFileObj(filename, false);
}

void object::getVertex(cyTriMesh mesh) {
	unsigned int t_vSize = mesh.NF() * 3;
	vertex = new cyPoint3f[t_vSize];
	for (int i = 0; i < mesh.NF(); i++) {
		cyTriMesh::TriFace temp = mesh.F(i);
		unsigned int *v_index = temp.v;
		unsigned int a = v_index[0];
		unsigned int b = v_index[1];
		unsigned int c = v_index[2];
		vertex[3 * i] = mesh.V(a);
		vertex[3 * i + 1] = mesh.V(b);
		vertex[3 * i + 2] = mesh.V(c);
	}
}

void object::getNormal(cyTriMesh mesh) {
	mesh.ComputeNormals();
	unsigned int t_nSize = mesh.NF() * 3;
	normal = new cyPoint3f[t_nSize];
	for (int i = 0; i < mesh.NF(); i++) {
		cyTriMesh::TriFace temp = mesh.FN(i);
		unsigned int *n_index = temp.v;
		unsigned int a = n_index[0];
		unsigned int b = n_index[1];
		unsigned int c = n_index[2];
		normal[3 * i] = mesh.VN(a);
		normal[3 * i + 1] = mesh.VN(b);
		normal[3 * i + 2] = mesh.VN(c);
	}
}

//void object::calModelMatrix(cyTriMesh mesh) {
//	mesh.ComputeBoundingBox();
//	cyPoint3f Max = mesh.GetBoundMax();
//	cyPoint3f Min = mesh.GetBoundMin();
//	cyPoint3f center;// cyMatrix4f scale;
//	center = cyPoint3f((Max.x + Min.x) / 2, (Max.y + Min.y) / 2, (Max.y + Min.y) / 2);
//	cyPoint3f bound = (Max - Min);
//	//scale.SetScale(1.0f / std::max(bound[0], std::max(bound[1], bound[2])));
//	//modelMatrix.SetIdentity();
//	//modelMatrix.AddTrans(-1 * center);
//	//modelMatrix *= scale;
//
//}

//void object::calNormalMatrix(cyMatrix4f modelMatrix) {
//	cyMatrix3f M = modelMatrix.GetSubMatrix3();
//	M.Invert();
//	M.Transpose();
//	float temp[9];
//	M.Get(temp);
//	float new_temp[16] = { temp[0], temp[1], temp[2], 0, temp[3], temp[4], temp[5], 0, temp[6],
//		temp[7], temp[8], 0, 0,0, 0, 1 };
//	normalMatrix.Set(new_temp);
//}

object::object(char *filename) {
	object::getMesh(filename);
	object::getVertex(mesh);
	object::getNormal(mesh);
	//object::calModelMatrix(mesh);
	//object::calNormalMatrix(modelMatrix);
	numFace = mesh.NF();
}

int object::returnNumFace() {
	return mesh.NF();
}

cyPoint3f* object::returnVertex() {
	return vertex;
}

cyPoint3f* object::returnNormal() {
	return normal;
}

//cyMatrix4f object::returnModelMatrix() {
//	return modelMatrix;
//}
//
//cyMatrix4f object::returnNormalMatrix() {
//	return normalMatrix;
//}


object::object() {};

//void object::changeBackPlaneModelMatrix() {
//	cyMatrix4f scale;
//	scale.SetScaledIdentity(3.0f);
//	modelMatrix *= scale;
//	cyMatrix4f rotate;
//	rotate.SetRotationX((M_PI * (-180)) / 180);
//	modelMatrix *= rotate;
//	cyPoint3f trans = cyPoint3f(0, 0, 1.5);
//	modelMatrix.AddTrans(trans);
//	//change normal matrix
//	calNormalMatrix(modelMatrix);
//}

//void object::changeUnderPlaneModelMatrix() {
//	cyMatrix4f scale;
//	scale.SetScaledIdentity(3.0f);
//	modelMatrix *= scale;
//	cyMatrix4f rotate;
//	rotate.SetRotationX((M_PI * (-90)) / 180);
//	modelMatrix *= rotate;
//	cyPoint3f trans = cyPoint3f(0, -0.5, -0.5);
//	modelMatrix.AddTrans(trans);
//	//change normal matrix
//	calNormalMatrix(modelMatrix);
//}