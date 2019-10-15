// Rotating Triangle
// Credits - Lighthouse3d
#include <GL/glut.h>

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w / h;

	// Use the Projection Matrix ie in world-co-ordinate sys
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	// converts normalised device co-ordinates to window co-ordinates
	// it keeps the triangle to our center by spanning the complete axes..instead of increasing co-ordinates on window maximise
	glViewport(0, 0, w, h);

	// Set the correct frustum perspective.
	// it should match aspect ratio of viewport
	gluPerspective(45.0f, ratio, 0.1f, 100.0f); // (field of view in y, aspect ratio, near clipping plane, far clipping plane)

	// Get Back to the Modelview ie transfomed
	glMatrixMode(GL_MODELVIEW);
}

float angle = 0.0f;

void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	0.0f, 0.0f, 10.0f, // eye
				0.0f, 0.0f,  0.0f, // center
				0.0f, 1.0f,  0.0f);// up

	glRotatef(angle, 0.0f, 1.0f, 0.0f); // angle, abt co-ordinates

	glBegin(GL_TRIANGLES);
		glVertex3f(-2.0f,-2.0f, 0.0f);
		glVertex3f( 2.0f, 0.0f, 0.0);
		glVertex3f( 0.0f, 2.0f, 0.0);
	glEnd();

	// causes rotation
	angle += 0.5f;

	// promotes contents of the back buffer of the layer to the current window to become contents of front buffer. The contents of the back buffer become undefined
    glutSwapBuffers();
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("Rotating triangle");

	// if glutreshape isnt used--alternative
	// only the rotation rate changes on window resizing
	// changeSize(500,500);

	// register callbacks
	glutDisplayFunc(renderScene);
	// resets callback for current window as well as on reize
	glutReshapeFunc(changeSize);
	// for continous calling of display to produce animation
	glutIdleFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}