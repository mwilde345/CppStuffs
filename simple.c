
//$ gcc -c -o simple.o simple.c -D FREEGLUT_STATIC -I"F:\MINGW\msys\1.0\freeglut\include"

//$ gcc -o simple.exe simple.o  -L"F:\MINGW\msys\1.0\freeglut\lib" -lfreeglut_static -lopengl32 -lwinmm -lgdi32 -lglu32 -Wl,--subsystem,windows
  
#include <GL/freeglut.h>        /* glut.h includes gl.h and glu.h*/
#include <stdio.h>
#include <stdlib.h>

GLuint startList,startList2;
GLuint d = 1;

void init(void)
{
   GLUquadricObj *qobj;
   GLUquadricObj *qobj2;
   GLfloat mat_ambient[] = { 0.0, 0.6, 0.3, 1.0 };
   GLfloat mat_specular[] = { 0.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   GLfloat model_ambient[] = { 0.5, 0.5, 0.5, 1.0 };

   glClearColor(0.4, 0.4, 0.4, 0.1);

   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);

   startList = glGenLists(1);
   qobj = gluNewQuadric();
   
   gluQuadricDrawStyle(qobj, GLU_FILL);
   gluQuadricNormals(qobj, GLU_FLAT);
   

   glNewList(startList, GL_COMPILE);



   gluCylinder(qobj, 0.10, 0.10, 2.0, 16, 1);
   glEndList();


   startList2 = glGenLists(1);

   qobj2 = gluNewQuadric();
   gluQuadricDrawStyle(qobj2, GLU_FILL);
   gluQuadricNormals(qobj2, GLU_FLAT);
   glNewList(startList2, GL_COMPILE);
   gluCylinder(qobj2, .2,.2,3,16,1);
   glEndList();
   

}

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 1;


void display(void)
{
glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


glRotatef(theta[0], 1.0, 0.0, 0.0);
glRotatef(theta[1], 0.0, 1.0, 0.0);
glRotatef(theta[2], 0.0, 0.0, 1.0);

glEnable(GL_LIGHTING);

 glPushMatrix();
 glTranslatef(0.0, 1.0, 1.0);  // shift to center of rotation

// y axis cylinders

   glPushMatrix();
   	glTranslatef(1, 0.0, 0.0);
   	glRotatef(90.0, 1.0, 0.0, 0.0);
   	glCallList(startList2);
   glPopMatrix();

   glPushMatrix();
   	glTranslatef(-1, 0.0, 0.0);
   	glRotatef(90.0, 1.0, 0.0, 0.0);
   	glCallList(startList);
   glPopMatrix();

   glPushMatrix();
   	glTranslatef(1, 0.0, -2.0);
   	glRotatef(90.0, 1.0, 0.0, 0.0);
   	glCallList(startList);
   glPopMatrix();

   glPushMatrix();
   	glTranslatef(-1, 0.0, -2.0);
   	glRotatef(90.0, 1.0, 0.0, 0.0);
   	glCallList(startList2);
   glPopMatrix();

// z axis cylinders

   glPushMatrix();
   	glTranslatef(1.0, 0.0, -2.0);
   	glRotatef(0.0, 1.0, 0.0, 0.0);
   	glCallList(startList);
   glPopMatrix();

   glPushMatrix();
   	glTranslatef(-1.0, 0.0, -2.0);
   	glRotatef(0.0, 1.0, 0.0, 0.0);
   	glCallList(startList2);
   glPopMatrix();

   glPushMatrix();
   	glTranslatef(1.0, -2.0, -2.0);
   	glRotatef(0.0, 1.0, 0.0, 0.0);
   	glCallList(startList);
   glPopMatrix();

   glPushMatrix();
   	glTranslatef(-1.0, -2.0, -2.0);
   	glRotatef(0.0, 1.0, 0.0, 0.0);
   	glCallList(startList2);
   glPopMatrix();

// x axis cylinders

   glPushMatrix();
   	glTranslatef(-1.0, 0.0, 0.0);
   	glRotatef(90.0, 0.0, 1.0, 0.0);
   	glCallList(startList);
   glPopMatrix();

   glPushMatrix();
   	glTranslatef(-1.0, 0.0, -2.0);
   	glRotatef(90.0, 0.0, 1.0, 0.0);
   	glCallList(startList2);
   glPopMatrix();

   glPushMatrix();
   	glTranslatef(-1.0, -2.0, 0.0);
   	glRotatef(90.0, 0.0, 1.0, 0.0);
   	glCallList(startList);
   glPopMatrix();

   glPushMatrix();
   	glTranslatef(-1.0, -2.0, -2.0);
   	glRotatef(90.0, 0.0, 1.0, 0.0);
   	glCallList(startList2);
   glPopMatrix();

 glPopMatrix();
 

   glFlush();
   glutSwapBuffers();

}

void reshape (int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-2.5, 2.5, -2.5*(GLfloat)h/(GLfloat)w,
         2.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho(-2.5*(GLfloat)w/(GLfloat)h,
         2.5*(GLfloat)w/(GLfloat)h, -2.5, 2.5, -10.0, 10.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

}

void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) theta[0] += 0.15;
		if( theta[0] > 360.0 ) theta[axis] -= 360.0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) theta[1] += 0.15;
		if( theta[1] > 360.0 ) theta[axis] -= 360.0;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) theta[2] += 0.15;
		if( theta[2] > 360.0 ) theta[axis] -= 360.0;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);
   init();
   glutMainLoop();
   return 0;
}