#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>


#include <initialization.h>
#include <object.h>
#include <camera.h>


object teapot;
cyGLSLProgram teapotShader;
GLuint teapotVAO;
GLuint teapotV_VBO;
camera Camera;

object initObject(char *filename);
camera initCamera();

cyPoint3f position = cyPoint3f(0.0f, 0.0f, -2.0f);
cyPoint3f front = cyPoint3f(0.0f, 0.0f, 2.0f);
cyPoint3f up = cyPoint3f(0.0f, 1.0f, 0.0f);

int frustum = 0;
int mouseState, mouseButton, mousex = 0, mousey = 0;

object initObject(char *filename) {
	object object(filename);
	return object;
}
void initObjectVAO() {
	int numF = teapot.returnNumFace();
	cyPoint3f* newVertex = teapot.returnVertex();

	glGenVertexArrays(1, &teapotVAO);
	glBindVertexArray(teapotVAO);
	glGenBuffers(1, &teapotV_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, teapotV_VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cyPoint3f) * numF * 3, newVertex, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, teapotV_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void changeViewPort(int w, int h)
{
	glViewport(0, 0, w, h);
}

camera initCamera() {
	camera Camera(position, front, up, frustum);
	return Camera;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	Camera.frustomSwitch(frustum);
	teapotShader.Bind();
	teapotShader.SetUniform(0, Camera.returnVtoPMatrix());
	teapotShader.SetUniform(1, Camera.returnWtoVMatrix());
	teapotShader.SetUniform(2, teapot.returnMtoWMatrix());

	glBindVertexArray(teapotVAO);
	int numF = teapot.returnNumFace();
	glDrawArrays(GL_POINTS, 0, sizeof(cyPoint3f) * numF);
	glBindVertexArray(0);
	//glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:									// ESCAPE key
		exit(0);
		break;
	case 'p':									// 0 perspective
		if (frustum == 0) {
			frustum = 1;			// 1 orthogonal
		}else if (frustum == 1) {
			frustum = 0;
		}
		//glutPostRedisplay();
		break;
	}
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F6:							// recompile GLSL shaders
		teapotShader.BuildFiles("./Shaders/objectShaderVert.glsl", "./Shaders/objectShaderFrag.glsl");
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	mouseState = state;
	mouseButton = button;
	mousex = x;
	mousey = y;
}

void mouseMotion(int x, int y)
{
	if (mouseState == GLUT_DOWN) {
		// left button to adjust camera angle
		if (mouseButton == GLUT_LEFT_BUTTON) {
			int dx = x - mousex, dy = y - mousey;
			Camera.rotate(dx, dy);

			mousex = x;
			mousey = y;
			//glutPostRedisplay();
		}
		// right button to adjust camera distance
		else if (mouseButton == GLUT_RIGHT_BUTTON) {
			int dx = x - mousex, dy = y - mousey;
			Camera = Camera.translate(dx, dy, teapot.returnObjectCenter());

			mousex = x;
			mousey = y;
		}
		else {

		}
	}
}

void initialize(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Ming Zi's Graphics Pad");
	glewInit();
	
	glutReshapeFunc(changeViewPort);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutIdleFunc(idle);
}


int main(int argc, char* argv[]) {
	initialize(argc, argv);
	//load object
	char *objectFilePath = argv[1];
	teapot = initObject(objectFilePath);

	Camera = initCamera();
	//run from cmd, use \InteractiveCompGraph\InteractiveCompGraph\Debug>InteractiveCompGraph ../InteractiveCompGraph/Files/teapot.obj
	//teapotShader.BuildFiles("../InteractiveCompGraph/Shaders/objectShaderVert.glsl", "../InteractiveCompGraph/Shaders/objectShaderFrag.glsl");
	teapotShader.BuildFiles("./Shaders/objectShaderVert.glsl", "./Shaders/objectShaderFrag.glsl"); //run from Visual Studio
	teapotShader.RegisterUniform(0, "VtoPMatrix");
	teapotShader.RegisterUniform(1, "WtoVMatrix");
	teapotShader.RegisterUniform(2, "MtoWMatrix");

	
	initObjectVAO();

	glutMainLoop();
	return 0;
}