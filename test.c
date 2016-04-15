#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

// gcc -c -o test.o test.c -D FREEGLUT_STATIC -I"F:\MINGW\msys\1.0\freeglut\include"
// gcc -o test.exe test.o  -L"F:\MINGW\msys\1.0\freeglut\lib" -lfreeglut_static -lopengl32 -lwinmm -lgdi32 -lglu32 -Wl,--subsystem,windows

GLUquadricObj *quadObj;
static float lmodel_twoside[] = {GL_TRUE};

double vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
	{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
	{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

void movetube(int a, int b)
{
	double v[3];
	v[0] = vertices[b][0] - vertices[a][0];
	v[1] = vertices[b][1] - vertices[a][1];
	v[2] = vertices[b][2] - vertices[a][2];

	double phi = 57.2957914 * acos(v[2]/2.0);
	double r = sqrt(v[0]*v[0] + v[1]*v[1]);
	double theta = 57.2957914 * acos(v[0]/r);

	// If r is zero, just translate
	if (r < .000001)
	{
		glPushMatrix();
			gluQuadricDrawStyle(quadObj, GLU_FILL);
//  			glColor3f(1.0, 1.0, 0.0);
			glTranslatef(vertices[a][0],vertices[a][1],vertices[a][2]);
			gluCylinder(quadObj, 0.15, 0.15, 2.0, 20, 8);
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
			gluQuadricDrawStyle(quadObj, GLU_FILL);
//  			glColor3f(1.0, 1.0, 0.0);
			glTranslatef(vertices[a][0],vertices[a][1],vertices[a][2]);
			glRotatef(theta, 0.0, 0.0, 1.0);
			glRotatef(phi, 0.0, 1.0, 0.0);
			gluCylinder(quadObj, 0.15, 0.15, 2.0, 20, 8);
		glPopMatrix();
	}
}

void placespheres(int a)
{
	glPushMatrix();
		gluQuadricDrawStyle(quadObj, GLU_FILL);
		glTranslatef(vertices[a][0],vertices[a][1],vertices[a][2]);
		gluSphere(quadObj, 0.5, 15, 15);
	glPopMatrix();
}

static GLfloat angle[] = {0.0,0.0,0.0};

void drawScene(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//  glColor3f(1.0, 1.0, 1.0);

  glRotatef(angle[0], 1.0, 0.0, 0.0);
  glRotatef(angle[1], 0.0, 1.0, 0.0);
  glRotatef(angle[2], 0.0, 0.0, 1.0);

/***************************************************/

	movetube(0,3);
	movetube(1,2);
	movetube(0,1);
	movetube(3,2);

	movetube(4,7);
	movetube(5,6);
	movetube(4,5);
	movetube(7,6);

	movetube(0,4);
	movetube(1,5);
	movetube(3,7);
	movetube(2,6);

/***************************************************/

	int i;
	for(i = 0; i < 8; i++)
		placespheres(i);

/***************************************************/

  glFlush();
  glutSwapBuffers();
}

void
keyboard(unsigned char c, int x, int y)
{
  switch (c) {
  case 27:
    exit(0);
    break;
  default:
    break;
  }
}


void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) angle[0] += 0.15;
		if( angle[0] > 360.0 ) angle[0] -= 360.0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) angle[1] += 0.15;
		if( angle[1] > 360.0 ) angle[1] -= 360.0;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) angle[2] += 0.15;
		if( angle[2] > 360.0 ) angle[2] -= 360.0;

	glutPostRedisplay();
}


void reshape(int w, int h)
{
  	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	if (w <= h)
//      	glOrtho(-2.5, 2.5, -2.5*(GLfloat)h/(GLfloat)w,
//         	2.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
		gluPerspective(60.0, (GLfloat)h/(GLfloat)w, 2.0, -2.0);
   	else
//      	glOrtho(-2.5*(GLfloat)w/(GLfloat)h,
//         2.5*(GLfloat)w/(GLfloat)h, -2.5, 2.5, -10.0, 10.0);
		gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 2.0, -2.0);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
	gluLookAt(0.525f, 1.525f, 4.f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void initLightAndMaterial(void)
{
  static float ambient[] = {0.1, 0.6, 0.6, 1.0};
//  static float diffuse[] = {0.5, 1.0, 1.0, 1.0};
  static float diffuse[] = {0.0, 0.5, 0.5, 1.0};
  static float position[] = {90.0, 90.0, 150.0, 0.0};

  static float front_mat_shininess[] = {60.0};
  static float front_mat_specular[] = {0.2, 0.8, 0.8, 1.0};
//  static float front_mat_diffuse[] = {0.5, 0.5, 0.28, 1.0};
  static float front_mat_diffuse[] = {0.2, 0.7, 0.7, 1.0};
  static float back_mat_shininess[] = {60.0};
  static float back_mat_specular[] = {0.2, 0.5, 0.5, 1.0};
  static float back_mat_diffuse[] = {1.0, 0.9, 0.2, 1.0};

  static float lmodel_ambient[] = {0.0, 1.0, 1.0, 1.0};

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  glMaterialfv(GL_FRONT, GL_SHININESS, front_mat_shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, front_mat_specular);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, front_mat_diffuse);
  glMaterialfv(GL_BACK, GL_SHININESS, back_mat_shininess);
  glMaterialfv(GL_BACK, GL_SPECULAR, back_mat_specular);
  glMaterialfv(GL_BACK, GL_DIFFUSE, back_mat_diffuse);

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  quadObj = gluNewQuadric();
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Symmetries of the cube");
  initLightAndMaterial();
  glutDisplayFunc(drawScene);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}

