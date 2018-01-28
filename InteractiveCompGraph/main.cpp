#include <GL\freeglut.h>
#include <iostream>
#include <initialization.h>
#include <Files\cyTriMesh.h>
#include <object.h>

int timePassed = 0;                             //time counter
int pause = 0;									//pause counter
Color curColor = makeColor(1.0f, 1.0f, 1.0f);	//initialize background color to white
object teapot;

object initObject(char *filename) {
	object object(filename);
	return object;
}
void changeViewPort(int w, int h)
{
	glViewport(0, 0, w, h);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(curColor.r, curColor.g, curColor.b, 1.0f);
	glutSwapBuffers();
}

void idle()
{
	const int curTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = curTime - timePassed;

	if (deltaTime>2000)
	{
		timePassed = curTime;
		curColor = makeColor((float)myrandom(255) / 255, (float)myrandom(255) / 255,
							 (float)myrandom(255) / 255); //new random color for background
		if (pause == 0) glutPostRedisplay();			  //redisplay when not paused
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:									// ESCAPE key
		exit(0);
		break;
	case 'p':									//pause control
		if (pause == 0) pause = 1;
		else pause = 0;
		break;
	
	}
}

void initialize(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Ming Zi's Graphics Pad");
	glutReshapeFunc(changeViewPort);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
}


int main(int argc, char* argv[]) {
	//bool isFileNull = false;
	//Scene file reader
	//FILE* objFile = fopen("Files/teapot.obj", "r");
	//if (objFile == NULL) {
	//	printf("Error. Could not open .obj file.\n");
	//	//isFileNull = true;
	//	return false;
	//}
	//bool LoadFromFileObj("teapot.obj", false, std::ostream *outStream);
	//char* sourceFilePath
	initialize(argc, argv);
	//load object
	char *objectFilePath = "Files/teapot.obj";
	teapot = initObject(objectFilePath);


	glutMainLoop();
	return 0;
}