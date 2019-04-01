#define PROGRAM_TITLE "Liam King"
#define DISPLAY_INFO "MultiRot Program for 3710 - Liam King"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<stdbool.h>
#include<iostream>
#include<time.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<math.h>
#include "robot.cpp"

#define PI 3.1415927

int Window_ID;
int Window_Width = 600;
int Window_Height = 400;


int recentfKey = 0;

void moveCam(int);

bool headTurnR = false; //can head turn right
bool headTurnL = false; // can head turn left
int randNums[400];
Robot robot;

//Draws the buildings for a block
void drawBuildingA(int x, int z) {

glLoadIdentity();
  glColor3f( 1, 0, 0);
  //Top Building
  // BACK
  glBegin(GL_POLYGON);
  glVertex3f(  x+16.5, 0, z+45 );
  glVertex3f(  x+16.5, 60, z+45 );
  glVertex3f( x+34, 60, z+45 );
  glVertex3f( x+34, 0, z+45 );
  glEnd();
  //RIGHT
  glBegin(GL_POLYGON);
  glVertex3f( x+34, 60, z+45 );
  glVertex3f( x+34, 0, z+45 );
  glVertex3f( x+34, 0, z+27.5 );
  glVertex3f( x+34, 60, z+27.5 );
  glEnd();
  //LEFT
  glBegin(GL_POLYGON);
  glVertex3f( x+16.5, 60, z+27.5 );
  glVertex3f( x+16.5, 0, z+27.5 );
  glVertex3f( x+16.5, 0, z+45 );
  glVertex3f( x+16.5, 0, z+27.5 );
  glEnd();
  //TOP
  glBegin(GL_POLYGON);
  glVertex3f( x+16.5, 60, z+27.5 );
  glVertex3f( x+16.5 , 60, z+45 );
  glVertex3f( x+34, 60, z+45 );
  glVertex3f( x+34, 60, z+27.5 );
  glEnd();
  //BOTTOM
  glBegin(GL_POLYGON);
  glVertex3f( x+16.5, 0, z+27.5 );
  glVertex3f( x+16.5, 0, z+45 );
  glVertex3f( x+34 , 0, z+45 );
  glVertex3f( x+34, 0, z+27.5 );
  glEnd();

  //Bottom Left Building
  // BACK
  glBegin(GL_POLYGON);
  glVertex3f(  x+5, 0, z+22.5 );
  glVertex3f(  x+5, 50, z+22.5 );
  glVertex3f( x+22.5, 50, z+22.5 );
  glVertex3f( x+22.5, 0, z+22.5 );
  glEnd();
  //RIGHT
  glBegin(GL_POLYGON);
  glVertex3f( x+22.5, 0, z+5 );
  glVertex3f( x+22.5, 50, z+5 );
  glVertex3f( x+22.5, 50, z+22.5 );
  glVertex3f( x+22.5, 0, z+22.5 );
  glEnd();
  //LEFT
  glBegin(GL_POLYGON);
  glVertex3f( x+5, 0, z+5 );
  glVertex3f( x+5, 50, z+5 );
  glVertex3f( x+5, 50, z+22.5 );
  glVertex3f( x+5, 0, z+22.5 );
  glEnd();
  //TOP
  glBegin(GL_POLYGON);
  glVertex3f( x+5, 50, z+5 );
  glVertex3f( x+5 , 50, z+22.5 );
  glVertex3f( x+22.5, 50, z+22.5 );
  glVertex3f( x+22.5, 50, z+5 );
  glEnd();
  //BOTTOM
  glBegin(GL_POLYGON);
  glVertex3f( x+5, 0, z+5 );
  glVertex3f( x+5, 0, z+22.5 );
  glVertex3f( x+22.5 , 0, z+22.5 );
  glVertex3f( x+22.5, 0, z+5 );
  glEnd();

  //Draw the cylindrical building
  //Set up transformation matrix resulted from rotation and translation
  glLoadIdentity();
  glRotatef(90, 1, 0, 0);
  glTranslatef(x+36.5, 0, z+13.75);
  //Draw the cylinder based on the current matrix so it's it the correct position
  glBegin(GL_POLYGON);
  GLUquadricObj *obj = gluNewQuadric();
  gluCylinder(obj, 8.75, 8.75, 55, 50, 50);
  glEnd();
  //Reset current matrix to identity
  glLoadIdentity();
}

//Draws the buildings for a block
void drawBuildingB(int x, int z) {
  //Draw the one cylindrical building on the block
  glColor3f( 1, 0, 0);
  glLoadIdentity();
  glRotatef(90, 1, 0, 0);
  glTranslatef(x+25, -4.95, z+25);
  //Draw the cylinder based on the current matrix so it's it the correct position
  glBegin(GL_POLYGON);
  GLUquadricObj *obj = gluNewQuadric();
  gluCylinder(obj, 20, 20, 75, 30, 70);
  glEnd();
  //Reset current matrix to identity
  glLoadIdentity();

}

//Draws the buildings for a block
void drawBuildingC(int x, int z) {
  glColor3f( 1, 0, 0);
  // BACK
  glBegin(GL_POLYGON);
  glVertex3f(  x+5, 0, z+45 );
  glVertex3f(  x+5, 80, z+45 );
  glVertex3f( x+45, 80, z+45 );
  glVertex3f( x+45, 0, z+45 );
  glEnd();
  //RIGHT
  glBegin(GL_POLYGON);
  glVertex3f( x+45, 80, z+45 );
  glVertex3f( x+45, 0, z+45 );
  glVertex3f( x+45, 0, z+5 );
  glVertex3f( x+45, 80, z+5 );
  glEnd();
  //LEFT
  glBegin(GL_POLYGON);
  glVertex3f( x+5, 0, z+5 );
  glVertex3f( x+5, 80, z+5 );
  glVertex3f( x+5, 80, z+45 );
  glVertex3f( x+5, 0, z+45 );
  glEnd();
  //TOP
  glBegin(GL_POLYGON);
  glVertex3f( x+5, 80, z+5 );
  glVertex3f( x+5 , 80, z+45 );
  glVertex3f( x+45, 80, z+45 );
  glVertex3f( x+45, 80, z+5 );
  glEnd();
  //BOTTOM
  glBegin(GL_POLYGON);
  glVertex3f( x+5, 0, z+5 );
  glVertex3f( x+5, 0, z+45 );
  glVertex3f( x+45 , 0, z+45 );
  glVertex3f( x+45, 0, z+5 );
  glEnd();

}

void draw_environment(GLenum mode){

	// CLEAR THE BUFFER, all drawing code should be after this point
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


		//BLOCK COLORS:::
    glColor4f(0.5, 0.9, 0.8, 1.0);

    glBegin(GL_QUADS);
		for (int i=0; i<10; i++) {
			for (int j=0; j<10; j++) {
                glTexCoord2f(1.0, 1.0); glVertex3f(-50.0+i*10, -5.0, -40.0+j*10);
				glTexCoord2f(0.0, 1.0); glVertex3f(-40.0+i*10, -5.0, -40.0+j*10);
                glTexCoord2f(0.0, 0.0); glVertex3f(-40.0+i*10, -5.0, -50.0+j*10);
                glTexCoord2f(1.0, 0.0); glVertex3f(-50.0+i*10, -5.0, -50.0+j*10);
			}
		}
		glEnd();

		//ROAD COLORS:::
    glColor4f(0.3, 0.3, 0.3, 0.3);

    glBegin(GL_QUADS);

    for (int i=0; i<10; i++) {
            glTexCoord2f(1.0, 1.0); glVertex3f(-51+i*10, -4.95, 50.0);
            glTexCoord2f(0.0, 1.0); glVertex3f(-49+i*10, -4.95, 50.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-49+i*10, -4.95, -50.0);
            glTexCoord2f(1.0, 0.0); glVertex3f(-51+i*10, -4.95, -50.0);
    }

    for (int i=0; i<10; i++) {
        glTexCoord2f(1.0, 0.0); glVertex3f(-50, -4.95, -51+i*10);

        glTexCoord2f(0.0, 0.0); glVertex3f(-50, -4.95, -49+i*10);
        glTexCoord2f(0.0, 1.0); glVertex3f(50, -4.95, -49+i*10);
        glTexCoord2f(1.0, 1.0); glVertex3f(50, -4.95, -51+i*10);


    }
    glEnd();


		//SKY COLORS:::
    glColor4f(1.0, 1.0, 1.0, 0.0);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0); glVertex3f( 50.0, 5.0, -50.0);

		glTexCoord2f(0.0, 1.0); glVertex3f( 50.0, 5.0,  50.0);

		glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 5.0,  50.0);

		glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 5.0, -50.0);
		glEnd();
		glEnd();
//		glBindTexture(GL_TEXTURE_2D, horizon);
		glBegin(GL_QUADS);
        glTexCoord2f(1.0, 1.0); glVertex3f( 50.0,  -5.0,  -50.0);
        glTexCoord2f(1.0, 0.0); glVertex3f( 50.0, 5.0,  -50.0);
        glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, 5.0,  -50.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-50.0,  -5.0,  -50.0);



		glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, -5.0,   50.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-50.0,  5.0,   50.0);
		glTexCoord2f(1.0, 1.0); glVertex3f( 50.0,  5.0,   50.0);
		glTexCoord2f(1.0, 0.0); glVertex3f( 50.0, -5.0,   50.0);

		glTexCoord2f(0.0, 0.0); glVertex3f( 50.0, 5.0,  -50.0);
		glTexCoord2f(0.0, 1.0); glVertex3f( 50.0,  -5.0,  -50.0);
		glTexCoord2f(1.0, 1.0); glVertex3f( 50.0,  -5.0,   50.0);
		glTexCoord2f(1.0, 0.0); glVertex3f( 50.0, 5.0,   50.0);

		glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, -5.0,  -50.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-50.0,  5.0,  -50.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(-50.0,  5.0,   50.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, -5.0,   50.0);
		glEnd();


		glFlush();


}

static void PrintString(void *font, char *str)
{
   int i,len=strlen(str);

   for(i=0;i < len; i++)
      glutBitmapCharacter(font,*str++);
}



void CallBackRenderScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


   glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glPushMatrix();
robot.draw_environment(GL_RENDER);
glPopMatrix();
//glTranslatef(605, 0, 605);

//drawBuildingA(0,0);
for (int i = 0; i<19; i++) {
  for (int j = 0; j<19; j++) {
    int build = randNums[i*j];
    switch(build) {
      case 1:
      robot.drawBuildingA(0 + i*60, 0+j*60);
      break;
      case 2:
      robot.drawBuildingB(0 + i*60, 0+j*60);
      break;
      case 3:
      robot.drawBuildingC(0+ i*60, 0+j*60);
    }
}
}
//robot.drawBuildingB(0,0);
//dogs
robot.drawRobot();


   glLoadIdentity();
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();

   glLoadIdentity();
   glOrtho(0,Window_Width,0,Window_Height,-1.0,1.0);
   glColor4f(0.6,1.0,0.6,1.00);


   glTranslatef(6.0f, Window_Height - 14, 0.0f);

   glPopMatrix();
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

   glutSwapBuffers();

   robot.headRotate(headTurnR, headTurnL);
   robot.moveCam(recentfKey);

}



void mouse(int button, int state, int x, int y)
{
    if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {


    }
    if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP)) {

    }
    if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {

    }
    if((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {

    }
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   case 122: // z key
       robot.cz += 5.0f;
       robot.eyez += 5.0f;
       robot.atz += 5.0f;
      break;
   case 97: // a key

      break;
   case 113: // q key

      break;
   case 32: // space bar
      break;
   default:
      printf ("No case assigned for %d.\n", key);
      break;
    }
}

void speckeyboard(int key, int x, int y) {
    if (key == GLUT_KEY_F1) {
        recentfKey = 1;
    }
    if (key == GLUT_KEY_F2) {
        headTurnR = true;
    }
    if (key == GLUT_KEY_F3) {
        headTurnL = true;
    }
    if (key == GLUT_KEY_F6) {
            recentfKey = 6;
    }
    if (key == GLUT_KEY_F5) {
    recentfKey = 5;
    }
    if (key == GLUT_KEY_F7) {
            recentfKey = 7;
    }
    if (key == GLUT_KEY_F8) {
        recentfKey = 8;
    }
    if (key == GLUT_KEY_F9) {
            recentfKey = 9;
    }
    if (key == GLUT_KEY_F10) {
        recentfKey = 10;
    }
    if (key == GLUT_KEY_F11) {
        recentfKey = 11;
    }
    if (key == GLUT_KEY_F12) {
        recentfKey = 12;
    }


}

void speckeyboarddown(int key, int x, int y) {

    if (GLUT_KEY_F2) {
        headTurnR = false;
    }
    if (GLUT_KEY_F3) {
        headTurnL = false;
    }


}

void CallBackResizeScene(int Width, int Height)
{
   if (Height == 0) {
      Height = 1;
   }

   glViewport(0, 0, Width, Height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //glOrtho(-200, 200, -200, 200, 0, 50);
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,500.0f);

   glMatrixMode(GL_MODELVIEW);

   Window_Width  = Width;
   Window_Height = Height;
}

void MyInit(int Width, int Height)
{
   glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

   glClearDepth(1.0);
   glDepthFunc(GL_LESS);
   glEnable(GL_DEPTH_TEST);
   glDepthMask(GL_TRUE);

   glShadeModel(GL_SMOOTH);

   CallBackResizeScene(Width,Height);
}

int main(int argc, char **argv)
{
  srand(time(NULL));
for (int i = 0; i<400; i++) {
  randNums[i] = rand() % 3 + 1;
}


   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

   glutInitWindowSize(Window_Width, Window_Height);
   Window_ID = glutCreateWindow(PROGRAM_TITLE);

   glutDisplayFunc(&CallBackRenderScene);

   glutIdleFunc(&CallBackRenderScene);

   glutReshapeFunc(&CallBackResizeScene);

   glutMouseFunc(&mouse);

   glutSpecialFunc(&speckeyboard);
   glutSpecialUpFunc(&speckeyboarddown);
   glutKeyboardFunc(&keyboard);

   MyInit(Window_Width, Window_Height);

   printf("\n%s\n\n", PROGRAM_TITLE);
   glutMainLoop();
   return 1;
}
