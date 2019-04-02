#ifndef ROBOT_H
#define ROBOT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<stdbool.h>
#include<iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<math.h>

#define PI 3.1415927

void moveCam(int);
void headRotate(bool, bool);


class Robot {
public:
  float atx = 0, aty = 0.0, atz = 0; //floats for the at coordinates in our LookAt
  float eyex = 0, eyey = 4, eyez = -15; //the xyz coords for the eye location in our LookAt, starting at 0 0 5
  float cx = 0, cy = -3.5, cz = 0;  //floats for defining coords of the center of cube, cube starts centered at 0 0 0
  int bodyAngle = 0; //the angle at which the cube is currently.
  int headAngle = 0;
  int antRot = 0;
  float offz = 0;
  float offx = 0;

	//Draws the buildings for a block
	void drawBuildingB(int x, int z) {
	  //Draw the one cylindrical building on the block

	  glColor3f( 1, 0, 0);
  //  glTranslatef(-605 + x, 0, -605 + z);
	  glLoadIdentity();
			gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1 ,0);
    glTranslatef(-600, 0, -600);
	  glTranslatef(x+30, -4.95, z+30);
	  glRotatef(90, -1, 0, 0);
	  //Draw the cylinder based on the current matrix so it's it the correct position
	  glBegin(GL_TRIANGLE_STRIP);
	  GLUquadricObj *obj = gluNewQuadric();
	  gluCylinder(obj, 15, 15, 30, 10, 10);
	  glEnd();
	  //Reset current matrix to identity
	  glLoadIdentity();

	}

	//Draws the buildings for a block
	void drawBuildingA(int x, int z) {

	glLoadIdentity();
		gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1 ,0);
    glTranslatef(-595, -4.95, -595);
	  glColor3f( 1, 0, 0);
	  //Top Building
	  // BACK
	  glBegin(GL_POLYGON);
	  glVertex3f(  x+16.5, 0, z+45 );
	  glVertex3f(  x+16.5, 30, z+45 );
	  glVertex3f( x+34, 30, z+45 );
	  glVertex3f( x+34, 0, z+45 );
	  glEnd();
	  //RIGHT
	  glBegin(GL_POLYGON);
	  glVertex3f( x+34, 30, z+45 );
	  glVertex3f( x+34, 0, z+45 );
	  glVertex3f( x+34, 0, z+27.5 );
	  glVertex3f( x+34, 30, z+27.5 );
	  glEnd();
	  //LEFT
	  glBegin(GL_POLYGON);
	  glVertex3f( x+16.5, 30, z+27.5 );
	  glVertex3f( x+16.5, 30, z+45 );
	  glVertex3f( x+16.5, 0, z+45 );
	  glVertex3f( x+16.5, 0, z+27.5 );
	  glEnd();
	  //TOP
	  glBegin(GL_POLYGON);
	  glVertex3f( x+16.5, 30, z+27.5 );
	  glVertex3f( x+16.5 , 30, z+45 );
	  glVertex3f( x+34, 30, z+45 );
	  glVertex3f( x+34, 30, z+27.5 );
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
	  glVertex3f(  x+5, 20, z+22.5 );
	  glVertex3f( x+22.5, 20, z+22.5 );
	  glVertex3f( x+22.5, 0, z+22.5 );
	  glEnd();
	  //RIGHT
	  glBegin(GL_POLYGON);
	  glVertex3f( x+22.5, 0, z+5 );
	  glVertex3f( x+22.5, 20, z+5 );
	  glVertex3f( x+22.5, 20, z+22.5 );
	  glVertex3f( x+22.5, 0, z+22.5 );
	  glEnd();
	  //LEFT
	  glBegin(GL_POLYGON);
	  glVertex3f( x+5, 0, z+5 );
	  glVertex3f( x+5, 20, z+5 );
	  glVertex3f( x+5, 20, z+22.5 );
	  glVertex3f( x+5, 0, z+22.5 );
	  glEnd();
	  //TOP
	  glBegin(GL_POLYGON);
	  glVertex3f( x+5, 20, z+5 );
	  glVertex3f( x+5 , 20, z+22.5 );
	  glVertex3f( x+22.5, 20, z+22.5 );
	  glVertex3f( x+22.5, 20, z+5 );
	  glEnd();
	  //BOTTOM
	  glBegin(GL_POLYGON);
	  glVertex3f( x+5, 0, z+5 );
	  glVertex3f( x+5, 0, z+22.5 );
	  glVertex3f( x+22.5 , 0, z+22.5 );
	  glVertex3f( x+22.5, 0, z+5 );
	  glEnd();

/*	  //Draw the cylindrical building
	  //Set up transformation matrix resulted from rotation and translation
	  glLoadIdentity();
	  glRotatef(90, 1, 0, 0);
	  glTranslatef(x+36.5, 0, z+13.75);
	  //Draw the cylinder based on the current matrix so it's it the correct position
	  glBegin(GL_POLYGON);
	  GLUquadricObj *obj = gluNewQuadric();
	  gluCylinder(obj, 8.75, 8.75, 55, 50, 50);
	  glEnd();*/
	  //Reset current matrix to identity
	  glLoadIdentity();
	}

  void draw_cylinder(GLfloat radius,
                     GLfloat height)
  {
      GLfloat x              = 0.0;
      GLfloat y              = 0.0;
      GLfloat angle          = 0.0;
      GLfloat angle_stepsize = 0.1;

      float r = 0;

      /** Draw the tube */
      glBegin(GL_TRIANGLE_STRIP);
      angle = 0.0;
          while( angle < 2*M_PI ) {
              x = radius * cos(angle);
              y = radius * sin(angle);
              glColor3f(r, 0.5f, 0.5f);
                  r += 0.005;
              glVertex3f(x, y , height);
              glColor3f(0.86f, 0.86f, 0.86f);
              glVertex3f(x, y , 0.0);
              angle = angle + angle_stepsize;
          }
          glColor3f(0.5f, 0.5f, 0.5f);
          glVertex3f(radius, 0.0, height);
          glColor3f(0.86f, 0.86f, 0.86f);
          glVertex3f(radius, 0.0, 0.0);
      glEnd();

      /** Draw the circle on top of cylinder */
      glColor3f(0.86f, 0.86f, 0.86f);
      glBegin(GL_POLYGON);
      angle = 0.0;
          while( angle < 2*PI ) {
              x = radius * cos(angle);
              y = radius * sin(angle);
              glVertex3f(x, y , height);
              angle = angle + angle_stepsize;
          }
          glVertex3f(radius, 0.0, height);
      glEnd();
}

void draw_environment(GLenum mode){

	// CLEAR THE BUFFER, all drawing code should be after this point
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1 ,0);


		//BLOCK COLORS:::
    glColor4f(0.5, 0.9, 0.8, 1.0);
    glTranslatef(-605, 0, -605);

    glBegin(GL_QUADS);
		for (int i=0; i<20; i++) {
			for (int j=0; j<20; j++) {
                glTexCoord2f(1.0, 1.0); glVertex3f(-50.0+i*60, -5.0, 0.0+j*60);
				glTexCoord2f(0.0, 1.0); glVertex3f(0.0+i*60, -5.0, 0.0+j*60);
                glTexCoord2f(0.0, 0.0); glVertex3f(0.0+i*60, -5.0, -50.0+j*60);
                glTexCoord2f(1.0, 0.0); glVertex3f(-50.0+i*60, -5.0, -50.0+j*60);
			}
		}
		glEnd();

		//ROAD COLORS:::
    glColor4f(0.3, 0.3, 0.3, 0.3);

    glBegin(GL_QUADS);

    for (int i=0; i<21; i++) {
            glTexCoord2f(1.0, 1.0); glVertex3f(-60+i*60, -4.95, 1150.0);
            glTexCoord2f(0.0, 1.0); glVertex3f(-50+i*60, -4.95, 1150.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-50+i*60, -4.95, -60.0);
            glTexCoord2f(1.0, 0.0); glVertex3f(-60+i*60, -4.95, -60.0);
    }

    for (int i=0; i<21; i++) {
        glTexCoord2f(1.0, 0.0); glVertex3f(-60, -4.95, -60+i*60);

        glTexCoord2f(0.0, 0.0); glVertex3f(-60, -4.95, -50+i*60);
        glTexCoord2f(0.0, 1.0); glVertex3f(1150, -4.95, -50+i*60);
        glTexCoord2f(1.0, 1.0); glVertex3f(1150, -4.95, -60+i*60);


    }
    glEnd();


		/*//SKY COLORS:::
    glColor4f(1.0, 1.0, 1.0, 0.0);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0); glVertex3f( 50.0, 5.0, -50.0);

		glTexCoord2f(0.0, 1.0); glVertex3f( 50.0, 5.0,  50.0);

		glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 5.0,  50.0);

		glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 5.0, -50.0);
		glEnd();
	//	glEnd();
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
		glEnd();*/


		glFlush();


}

//Draws the buildings for a block
void drawBuildingC(int x, int z) {
  glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1 ,0);
  glTranslatef(-595, -4.95, -595);
  glColor3f( 1, 0, 0);
  // BACK
  glBegin(GL_POLYGON);
  glVertex3f(  x+5, 0, z+45 );
  glVertex3f(  x+5, 30, z+45 );
  glVertex3f( x+45, 30, z+45 );
  glVertex3f( x+45, 0, z+45 );
  glEnd();
  //RIGHT
  glBegin(GL_POLYGON);
  glVertex3f( x+45, 30, z+45 );
  glVertex3f( x+45, 0, z+45 );
  glVertex3f( x+45, 0, z+5 );
  glVertex3f( x+45, 30, z+5 );
  glEnd();
  //LEFT
  glBegin(GL_POLYGON);
  glVertex3f( x+5, 0, z+5 );
  glVertex3f( x+5, 30, z+5 );
  glVertex3f( x+5, 30, z+45 );
  glVertex3f( x+5, 0, z+45 );
  glEnd();
  //TOP
  glBegin(GL_POLYGON);
  glVertex3f( x+5, 30, z+5 );
  glVertex3f( x+5 , 30, z+45 );
  glVertex3f( x+45, 30, z+45 );
  glVertex3f( x+45, 30, z+5 );
  glEnd();
  //BOTTOM
  glBegin(GL_POLYGON);
  glVertex3f( x+5, 0, z+5 );
  glVertex3f( x+5, 0, z+45 );
  glVertex3f( x+45 , 0, z+45 );
  glVertex3f( x+45, 0, z+5 );
  glEnd();

}

void drawRobot() {
  GLUquadric* neckquad;
  neckquad = gluNewQuadric();
  GLUquadric* antquad;
  antquad = gluNewQuadric();
  gluQuadricTexture(antquad, true);




  //cube begin
  glLoadIdentity();
  gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1 ,0);

  glTranslatef(cx,cy,cz);
  glRotatef(bodyAngle, 0, 1, 0);
  glTranslatef(0, 0, 0);

  //glRotatef(cubeAngle, 0.0f, 1.0f, 0.0f);

  glBegin(GL_TRIANGLES);

  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(-0.8f, -1.3f, -1.01f);
  glVertex3f(0.8f, -1.3f, -1.01f);
  glVertex3f(0.0f, 0.0f, -1.01f);

  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(-0.8f, 0.0f, -1.01f);
  glVertex3f(0.8f, 0.0f, -1.01f);
  glVertex3f(0.0f, 1.3f, -1.01f);

  glEnd();

  glBegin(GL_QUADS);

  //frontdesign

  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(-0.6f, -1.0f,  1.01f);
  glVertex3f( 0.6f, -1.0f,  1.01f);
  glVertex3f( 0.6f,  1.0f,  1.01f);
  glVertex3f(-0.6f,  1.0f,  1.01f);

  //Upper face
  glColor3f(0.86f,0.86f,0.86f);
  glVertex3f(-1.0f, 1.5f, 1.0f);
  glVertex3f(1.0f, 1.5f, 1.0f);
  glVertex3f(1.0f, 1.5f, -1.0f);
  glVertex3f(-1.0f, 1.5f, -1.0f);

  //Bottom face
  glColor3f(0.86f,0.86f,0.86f);
  glVertex3f(-1.0f, -1.5f, 1.0f);
  glVertex3f(1.0f, -1.5f, 1.0f);
  glVertex3f(1.0f, -1.5f, -1.0f);
  glVertex3f(-1.0f, -1.5f, -1.0f);

  //Far face.
  glColor3f(0.86f,0.86f,0.86f);
  glVertex3f(-1.0f, -1.5f, -1.0f);
  glVertex3f(-1.0f,  1.5f, -1.0f);
  glVertex3f( 1.0f,  1.5f, -1.0f);
  glVertex3f( 1.0f, -1.5f, -1.0f);

  // Right face.
  glColor3f(0.86f,0.86f,0.86f);
  glVertex3f( 1.0f, -1.5f, -1.0f);
  glVertex3f( 1.0f,  1.5f, -1.0f);
  glVertex3f( 1.0f,  1.5f,  1.0f);
  glVertex3f( 1.0f, -1.5f,  1.0f);

  //Front face.
  glColor3f(0.86f,0.86f,0.86f);
  glVertex3f(-1.0f, -1.5f,  1.0f);
  glVertex3f( 1.0f, -1.5f,  1.0f);
  glVertex3f( 1.0f,  1.5f,  1.0f);
  glVertex3f(-1.0f,  1.5f,  1.0f);

  // Left Face.
  glColor3f(0.86f,0.86f,0.86f);
  glVertex3f(-1.0f, -1.5f, -1.0f);
  glVertex3f(-1.0f, -1.5f,  1.0f);
  glVertex3f(-1.0f,  1.5f,  1.0f);
  glVertex3f(-1.0f,  1.5f, -1.0f);

  glEnd();

  //neck
  glTranslatef(0.0f, 1.5f, 0.0f);
  glRotatef(90, -1.0f, 0.0f, 0.0f);

  glBegin(GL_TRIANGLE_STRIP);

  glColor3f(0.5f, 0.5f, 0.5f);
  gluCylinder(neckquad, 0.5, 0.5, 0.5, 50, 50);

  glEnd();

  //antenae
  glTranslatef(0.0f, 0.0f, 1.5f);
  glRotatef(-antRot, 0.0f, 0.0f, 1.0f);

  glBegin(GL_TRIANGLE_STRIP);


  glTexCoord2f(0.0f, 0.5f);
  glColor3f(0.86f,0.86f,0.86f);
  draw_cylinder(0.1, 0.8);

  glEnd();

  glLoadIdentity();
  gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1 ,0);

  glTranslatef(cx,cy,cz);
  glRotatef(bodyAngle, 0, 1, 0);
  glTranslatef(0, 0, 0);

  glRotatef(headAngle, 0.0f, 1.0f, 0.0f);

  glBegin(GL_QUADS);
//BEGIN HEAD
  //Left Eye
  glColor3f(1.0f,0.0f,0.0f);
  glVertex3f(-0.3f, 2.9f,  0.71f);
  glVertex3f(-0.5f, 2.9f,  0.71f);
  glVertex3f(-0.5f,  2.7f,  0.71f);
  glVertex3f(-0.3f,  2.7f,  0.71f);

  //Right Eye
  glColor3f(1.0f,0.0f,0.0f);
  glVertex3f(0.3f, 2.9f,  0.71f);
  glVertex3f(0.5f, 2.9f,  0.71f);
  glVertex3f(0.5f,  2.7f,  0.71f);
  glVertex3f(0.3f,  2.7f,  0.71f);

  //Mouth
  glColor3f(0.0f,0.0f,0.0f);
  glVertex3f(0.53f, 2.2f,  0.71f);
  glVertex3f(-0.5f, 2.2f,  0.71f);
  glVertex3f(-0.5f,  2.4f,  0.71f);
  glVertex3f(0.5f,  2.4f,  0.71f);

     //Upper face
  glColor3f(0.86f,0.86f,0.86f);
  glVertex3f(-0.7f, 3.2f, 0.7f);
  glVertex3f(0.7f, 3.2f, 0.7f);
  glVertex3f(0.7f, 3.2f, -0.7f);
  glVertex3f(-0.7f, 3.2f, -0.7f);

  //Bottom face
  glColor3f(0.86f,0.86f,0.86f);
  glVertex3f(-0.8f, 1.9f, 0.7f);
  glVertex3f(0.8f, 1.9f, 0.7f);
  glVertex3f(0.8f, 1.9f, -0.7f);
  glVertex3f(-0.8f, 1.9f, -0.7f);

  //Far face.
  glColor3f(0.86f,0.86f,0.86f);
  glVertex3f(-0.8f, 1.9f, -0.7f);
  glVertex3f(-0.8f,  3.2f, -0.7f);
  glVertex3f( 0.8f,  3.2f, -0.7f);
  glVertex3f( 0.8f, 1.9f, -0.7f);

  // Right face.
  glColor3f(0.86f,0.86f,0.86f);
  glVertex3f( 0.8f, 1.9f, -0.7f);
  glVertex3f( 0.8f,  3.2f, -0.7f);
  glVertex3f( 0.8f,  3.2f,  0.7f);
  glVertex3f( 0.8f, 1.9f,  0.7f);

  //Front face.
  glColor3f(0.86f,0.86f,0.86f);
  glVertex3f(-0.8f, 1.9f,  0.7f);
  glVertex3f( 0.8f, 1.9f,  0.7f);
  glVertex3f( 0.8f,  3.2f,  0.7f);
  glVertex3f(-0.8f,  3.2f,  0.7f);

  // Left Face.
  glColor3f(0.86f,0.86f,0.86f);
  glVertex3f(-0.8f, 1.9f, -0.7f);
  glVertex3f(-0.8f, 1.9f,  0.7f);
  glVertex3f(-0.8f,  3.2f,  0.7f);
  glVertex3f(-0.8f,  3.2f, -0.7f);

  glEnd();

  antRot += 30;
  if (antRot == 360) {
   antRot = 0;
  }
}

void moveCam (int fKey) {
    switch (fKey) {
    case 1:
        if (eyex > (offx + 0)) {
            eyex--;
        }
        if (eyex < (offx + 0)) {
            eyex++;
        }
        if (eyey > 5) {
            eyey--;
        }
        if (eyey < 5) {
            eyey++;
        }
        if (eyez > (offz + -15)) {
            eyez--;
        }
        if (eyez < (offz + -15)) {
            eyez++;
        }
        break;
        case 2:
            if (eyex > (offx + -15)) {
                eyex--;
            }
            if (eyex < (offx + -15)) {
                eyex++;
            }
            if (eyey > 5) {
                eyey--;
            }
            if (eyey < 5) {
                eyey++;
            }
            if (eyez > (offz + 0)) {
                eyez--;
            }
            if (eyez < (offz + 0)) {
                eyez++;
            }
            break;
            case 3:
                if (eyex > (offx + 0)) {
                    eyex--;
                }
                if (eyex < (offx + 0)) {
                    eyex++;
                }
                if (eyey > 5) {
                    eyey--;
                }
                if (eyey < 5) {
                    eyey++;
                }
                if (eyez > (offz + 15)) {
                    eyez--;
                }
                if (eyez < (offz + 15)) {
                    eyez++;
                }
                break;
                case 4:
                    if (eyex > (offx + 15)) {
                        eyex--;
                    }
                    if (eyex < (offx + 15)) {
                        eyex++;
                    }
                    if (eyey > 5) {
                        eyey--;
                    }
                    if (eyey < 5) {
                        eyey++;
                    }
                    if (eyez > (offz + 0)) {
                        eyez--;
                    }
                    if (eyez < (offz + 0)) {
                        eyez++;
                    }
                    break;
    case 5:
        if (eyex > (offx + 10)) {
            eyex--;
        }
        if (eyex < (offx + 10)) {
            eyex++;
        }
        if (eyey > 10) {
            eyey--;
        }
        if (eyey < 10) {
            eyey++;
        }
        if (eyez > (offz + -10)) {
            eyez--;
        }
        if (eyez < (offz + -10)) {
            eyez++;
        }
        break;
    case 6:
        if (eyex > (offx + -10)) {
            eyex--;
        }
        if (eyex < (offx + -10)) {
            eyex++;
        }
        if (eyey > 10) {
            eyey--;
        }
        if (eyey < 10) {
            eyey++;
        }
        if (eyez > (offz + -10)) {
            eyez--;
        }
        if (eyez < (offz + -10)) {
            eyez++;
        }
        break;
    case 7:
        if (eyex > (offx + -10)) {
            eyex--;
        }
        if (eyex < (offx + -10)) {
            eyex++;
        }
        if (eyey > 10) {
            eyey--;
        }
        if (eyey < 10) {
            eyey++;
        }
        if (eyez > (offz + 10)) {
            eyez--;
        }
        if (eyez < (offz + 10)) {
            eyez++;
        }
        break;
    case 8:
        if (eyex > (offx + 10)) {
            eyex--;
        }
        if (eyex < (offx + 10)) {
            eyex++;
        }
        if (eyey > 10) {
            eyey--;
        }
        if (eyey < 10) {
            eyey++;
        }
        if (eyez > (offz + 10)) {
            eyez--;
        }
        if (eyez < (offz + 10)) {
            eyez++;
        }
        break;
    case 9:
        if (eyex > (offx + 200)) {
            eyex--;
        }
        if (eyex < (offx + 200)) {
            eyex++;
        }
        if (eyey > 200) {
            eyey--;
        }
        if (eyey < 200) {
            eyey++;
        }
        if (eyez > (offz + -200)) {
            eyez--;
        }
        if (eyez < (offz + -200)) {
            eyez++;
        }
        break;
    case 10:
        if (eyex > (offx + -200)) {
            eyex--;
        }
        if (eyex < (offx + -200)) {
            eyex++;
        }
        if (eyey > 200) {
            eyey--;
        }
        if (eyey < 200) {
            eyey++;
        }
        if (eyez > (offz + -200)) {
            eyez--;
        }
        if (eyez < (offz + -200)) {
            eyez++;
        }
        break;
    case 11:
        if (eyex > (offx + -200)) {
            eyex--;
        }
        if (eyex < (offx + -200)) {
            eyex++;
        }
        if (eyey > 200) {
            eyey--;
        }
        if (eyey < 200) {
            eyey++;
        }
        if (eyez > (offz + 200)) {
            eyez--;
        }
        if (eyez < (offz + 200)) {
            eyez++;
        }
        break;
    case 12:
        if (eyex > (offx + 200)) {
            eyex--;
        }
        if (eyex < (offx + 200)) {
            eyex++;
        }
        if (eyey > 200) {
            eyey--;
        }
        if (eyey < 200) {
            eyey++;
        }
        if (eyez > (offz + 200)) {
            eyez--;
        }
        if (eyez < (offz + 200)) {
            eyez++;
        }
        break;
    }
}

void bodyRot(bool& robRotR, bool& robRotL) {
if (robRotR) {
    bodyAngle += 3;
    if ((bodyAngle == 90) || (bodyAngle == 180) || (bodyAngle == 270) || (bodyAngle == 360)) {
        if (bodyAngle == 360) {
            bodyAngle = 0;
        }
        robRotR = false;
    }
}
if (robRotL) {
    bodyAngle -= 3;
    if ((bodyAngle == 90) || (bodyAngle == 180) || (bodyAngle == 270) || (bodyAngle == 360)) {
        if (bodyAngle == 360) {
            bodyAngle = 0;
        }
        robRotL = false;
    }
}
}

void headRotate(bool headTurnR, bool headTurnL) {
  if (headAngle == 360) {
   headAngle = 0;
  }
  if (headAngle == -360) {
   headAngle = 0;
  }
  if (headTurnR == true) {
   headAngle -= 2;
  }

  if (headTurnL == true) {
       headAngle += 2;
  }

  if((headAngle != 0) && (headTurnL == false) && (headTurnR == false)) {
       if (headAngle > 0) {
       headAngle -= 2;
       }
       if (headAngle < 0) {
           headAngle += 2;
       }
  }
}
};
#endif
