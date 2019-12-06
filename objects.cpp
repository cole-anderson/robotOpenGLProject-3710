#ifndef ROBOT_H
#define ROBOT_H
/*
File: objects.cpp
Contributors:
  Cole Anderson
  Liam King
  Brayden Ormann
Purpose:
  Data for creation of
  robot, buildings and the world.




*/
#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415927

void moveCam(int);
void headRotate(bool, bool);
static GLuint skybox;
static GLuint hor;

class Robot
{
public:
  // all explained in main where we initialize them in the main function
  float atx;
  float aty;
  float atz;
  float eyex;
  float eyey;
  float eyez;
  int cx;
  int cy;
  int cz;
  int bodyAngle;
  int headAngle;
  int antRot;
  float offz;
  float offx;
  int nameCount;
  GLenum modeV; // current GL_MODE (either GL_RENDER or GL_SELECT)

  // Draws the buildings for b block
  void drawBuildingB(int x, int z)
  {
    // Draw the one cylindrical building on the block

    // BLACK CYLINDER
    glColor3f(0.0f, 0.0f, 0.0f);
    //  glTranslatef(-605 + x, 0, -605 + z);
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1, 0);
    glTranslatef(-660, 0, -660);
    glTranslatef(x + 30, -4.95, z + 30);
    glRotatef(90, -1, 0, 0);
    // Draw the cylinder based on the current matrix so it's it the correct
    // position
    if (modeV == GL_SELECT)
    {
      glLoadName(nameCount);
      nameCount++;
    }
    glBegin(GL_TRIANGLE_STRIP);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 15, 15, 30, 10, 10);
    glEnd();
    // Reset current matrix to identity
    glLoadIdentity();
  }

  // Draws the buildings for a block
  void drawBuildingA(int x, int z)
  {

    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1, 0);
    glTranslatef(-655, -4.95, -655);
    // GREY X2 BUILDINGS
    glColor3f(0.5f, 0.5f, 0.5f);
    // Top Building
    // BACK
    if (modeV == GL_SELECT)
    {
      glLoadName(nameCount);
      nameCount++;
    }
    glBegin(GL_QUADS);
    glVertex3f(x + 16.5, 0, z + 45);
    glVertex3f(x + 16.5, 30, z + 45);
    glVertex3f(x + 34, 30, z + 45);
    glVertex3f(x + 34, 0, z + 45);

    // RIGHT

    glVertex3f(x + 34, 30, z + 45);
    glVertex3f(x + 34, 0, z + 45);
    glVertex3f(x + 34, 0, z + 27.5);
    glVertex3f(x + 34, 30, z + 27.5);

    // LEFT

    glVertex3f(x + 16.5, 30, z + 27.5);
    glVertex3f(x + 16.5, 30, z + 45);
    glVertex3f(x + 16.5, 0, z + 45);
    glVertex3f(x + 16.5, 0, z + 27.5);

    // TOP

    glVertex3f(x + 16.5, 30, z + 27.5);
    glVertex3f(x + 16.5, 30, z + 45);
    glVertex3f(x + 34, 30, z + 45);
    glVertex3f(x + 34, 30, z + 27.5);

    // BOTTOM

    glVertex3f(x + 16.5, 0, z + 27.5);
    glVertex3f(x + 16.5, 0, z + 45);
    glVertex3f(x + 34, 0, z + 45);
    glVertex3f(x + 34, 0, z + 27.5);
    glEnd();

    // Bottom Left Building
    // BACK
    glBegin(GL_QUADS);
    glVertex3f(x + 5, 0, z + 22.5);
    glVertex3f(x + 5, 20, z + 22.5);
    glVertex3f(x + 22.5, 20, z + 22.5);
    glVertex3f(x + 22.5, 0, z + 22.5);

    // RIGHT

    glVertex3f(x + 22.5, 0, z + 5);
    glVertex3f(x + 22.5, 20, z + 5);
    glVertex3f(x + 22.5, 20, z + 22.5);
    glVertex3f(x + 22.5, 0, z + 22.5);

    // LEFT

    glVertex3f(x + 5, 0, z + 5);
    glVertex3f(x + 5, 20, z + 5);
    glVertex3f(x + 5, 20, z + 22.5);
    glVertex3f(x + 5, 0, z + 22.5);

    // TOP

    glVertex3f(x + 5, 20, z + 5);
    glVertex3f(x + 5, 20, z + 22.5);
    glVertex3f(x + 22.5, 20, z + 22.5);
    glVertex3f(x + 22.5, 20, z + 5);

    // BOTTOM

    glVertex3f(x + 5, 0, z + 5);
    glVertex3f(x + 5, 0, z + 22.5);
    glVertex3f(x + 22.5, 0, z + 22.5);
    glVertex3f(x + 22.5, 0, z + 5);
    glEnd();

    // Reset current matrix to identity
    glLoadIdentity();
  }
  // antenna
  void draw_cylinder(GLfloat radius,
                     GLfloat height) // function that can be used to draw a
                                     // custom cylinder with different colors
                                     // (this is only used for the antenna)
  {
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

    float r = 0;

    /** Draw the tube */
    glBegin(GL_TRIANGLE_STRIP);
    angle = 0.0;
    while (angle < 2 * M_PI)
    {
      x = radius * cos(angle);
      y = radius * sin(angle);
      glColor3f(r, 0.3f, 0.3f);
      r += 0.005;
      glVertex3f(x, y, height);
      glColor3f(0.86f, 0.86f, 0.86f);
      glVertex3f(x, y, 0.0);
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
    while (angle < 2 * PI)
    {
      x = radius * cos(angle);
      y = radius * sin(angle);
      glVertex3f(x, y, height);
      angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
  }

  void draw_environment(GLenum mode)
  {

    // CLEAR THE BUFFER, all drawing code should be after this point
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1, 0);

    // BLOCK COLORS:::
    glColor4f(0.5, 0.9, 0.8, 1.0);
    glTranslatef(-605, 0, -605);

    glBegin(GL_QUADS);
    for (int i = 0; i < 20; i++)
    {
      for (int j = 0; j < 20; j++)
      {
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-50.0 + i * 60, -5.0, 0.0 + j * 60);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(0.0 + i * 60, -5.0, 0.0 + j * 60);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(0.0 + i * 60, -5.0, -50.0 + j * 60);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-50.0 + i * 60, -5.0, -50.0 + j * 60);
      }
    }
    glEnd();

    // ROAD COLORS:::
    glColor4f(0.3, 0.3, 0.3, 0.3);

    glBegin(GL_QUADS);

    for (int i = 0; i < 21; i++)
    {
      glTexCoord2f(1.0, 1.0);
      glVertex3f(-60 + i * 60, -4.95, 1150.0);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(-50 + i * 60, -4.95, 1150.0);
      glTexCoord2f(0.0, 0.0);
      glVertex3f(-50 + i * 60, -4.95, -60.0);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(-60 + i * 60, -4.95, -60.0);
    }

    for (int i = 0; i < 21; i++)
    {
      glTexCoord2f(1.0, 0.0);
      glVertex3f(-60, -4.95, -60 + i * 60);

      glTexCoord2f(0.0, 0.0);
      glVertex3f(-60, -4.95, -50 + i * 60);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(1150, -4.95, -50 + i * 60);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(1150, -4.95, -60 + i * 60);
    }
    glEnd();

    /*
    Was unable to impliment a skybox after changes to our lookat

    */
    // SKY COLORS:::
    /*
    glColor4f(1.0, 0.6, 0.3, 0.0);
    glBindTexture(GL_TEXTURE_2D, skybox);
                glBegin(GL_QUADS);

                glTexCoord2f(0.0, 0.0); glVertex3f( 50.0, 5.0, -50.0);

                glTexCoord2f(0.0, 1.0); glVertex3f( 50.0, 5.0,  50.0);

                glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 5.0,  50.0);

                glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 5.0, -50.0);
                glEnd();

                glBindTexture(GL_TEXTURE_2D, hor);
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

*/
    glFlush();
  }

  // Draws the buildings for a block
  void drawBuildingC(int x, int z)
  {
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1, 0);
    glTranslatef(-655, -4.95, -655);
    glColor3f(0.1f, 0.2f, 0.0f);
    // BACK
    if (modeV == GL_SELECT)
    {
      glLoadName(nameCount);
      nameCount++;
    }
    glBegin(GL_QUADS);
    glVertex3f(x + 5, 0, z + 45);
    glVertex3f(x + 5, 30, z + 45);
    glVertex3f(x + 45, 30, z + 45);
    glVertex3f(x + 45, 0, z + 45);

    // RIGHT

    glVertex3f(x + 45, 30, z + 45);
    glVertex3f(x + 45, 0, z + 45);
    glVertex3f(x + 45, 0, z + 5);
    glVertex3f(x + 45, 30, z + 5);

    // LEFT

    glVertex3f(x + 5, 0, z + 5);
    glVertex3f(x + 5, 30, z + 5);
    glVertex3f(x + 5, 30, z + 45);
    glVertex3f(x + 5, 0, z + 45);

    // TOP

    glVertex3f(x + 5, 30, z + 5);
    glVertex3f(x + 5, 30, z + 45);
    glVertex3f(x + 45, 30, z + 45);
    glVertex3f(x + 45, 30, z + 5);

    // BOTTOM

    glVertex3f(x + 5, 0, z + 5);
    glVertex3f(x + 5, 0, z + 45);
    glVertex3f(x + 45, 0, z + 45);
    glVertex3f(x + 45, 0, z + 5);
    glEnd();
  }

  void drawRobot()
  { // function for drawing the robot into the world
    GLUquadric *neckquad;
    neckquad = gluNewQuadric();
    GLUquadric *antquad;
    antquad = gluNewQuadric();
    gluQuadricTexture(antquad, true); // making a cylinder object

    // cube begin
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1,
              0); // lookat view for the robot

    glTranslatef(cx, cy, cz);      // translate to robots current position
    glRotatef(bodyAngle, 0, 1, 0); // for when robot is turning to left or right
    glTranslatef(0, 0, 0); // translate to 0, 0, 0 first for if robot is turning

    glBegin(
        GL_TRIANGLES); // this is the triangle design on the back of the robot
    // included on the body
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-0.8f, -1.3f, -1.01f);
    glVertex3f(0.8f, -1.3f, -1.01f);
    glVertex3f(0.0f, 0.0f, -1.01f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-0.8f, 0.0f, -1.01f);
    glVertex3f(0.8f, 0.0f, -1.01f);
    glVertex3f(0.0f, 1.3f, -1.01f);

    glEnd();

    // begin the body of the robot
    glBegin(GL_QUADS);

    // frontdesign
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-0.6f, -1.0f, 1.01f);
    glVertex3f(0.6f, -1.0f, 1.01f);
    glVertex3f(0.6f, 1.0f, 1.01f);
    glVertex3f(-0.6f, 1.0f, 1.01f);

    // Upper face
    glColor3f(0.86f, 0.86f, 0.86f);
    glVertex3f(-1.0f, 1.5f, 1.0f);
    glVertex3f(1.0f, 1.5f, 1.0f);
    glVertex3f(1.0f, 1.5f, -1.0f);
    glVertex3f(-1.0f, 1.5f, -1.0f);

    // Bottom face
    glColor3f(0.86f, 0.86f, 0.86f);
    glVertex3f(-1.0f, -1.5f, 1.0f);
    glVertex3f(1.0f, -1.5f, 1.0f);
    glVertex3f(1.0f, -1.5f, -1.0f);
    glVertex3f(-1.0f, -1.5f, -1.0f);

    // Far face.
    glColor3f(0.86f, 0.86f, 0.86f);
    glVertex3f(-1.0f, -1.5f, -1.0f);
    glVertex3f(-1.0f, 1.5f, -1.0f);
    glVertex3f(1.0f, 1.5f, -1.0f);
    glVertex3f(1.0f, -1.5f, -1.0f);

    // Right face.
    glColor3f(0.86f, 0.86f, 0.86f);
    glVertex3f(1.0f, -1.5f, -1.0f);
    glVertex3f(1.0f, 1.5f, -1.0f);
    glVertex3f(1.0f, 1.5f, 1.0f);
    glVertex3f(1.0f, -1.5f, 1.0f);

    // Front face.
    glColor3f(0.86f, 0.86f, 0.86f);
    glVertex3f(-1.0f, -1.5f, 1.0f);
    glVertex3f(1.0f, -1.5f, 1.0f);
    glVertex3f(1.0f, 1.5f, 1.0f);
    glVertex3f(-1.0f, 1.5f, 1.0f);

    // Left Face.
    glColor3f(0.86f, 0.86f, 0.86f);
    glVertex3f(-1.0f, -1.5f, -1.0f);
    glVertex3f(-1.0f, -1.5f, 1.0f);
    glVertex3f(-1.0f, 1.5f, 1.0f);
    glVertex3f(-1.0f, 1.5f, -1.0f);

    glEnd();

    // neck of robot
    glTranslatef(0.0f, 1.5f, 0.0f);
    glRotatef(90, -1.0f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLE_STRIP);

    glColor3f(0.5f, 0.5f, 0.5f);
    gluCylinder(neckquad, 0.5, 0.5, 0.5, 50,
                50); // cylinder gluquadric defined earlier

    glEnd();

    // antenae
    glRotatef(-antRot, 0.0f, 0.0f, 1.0f); // constantly rotate
    glTranslatef(0.1f, 0.0f,
                 1.5f); // translate it on top of its head and slightly to the
                        // side so we can see it rotating better

    glBegin(GL_TRIANGLE_STRIP);

    glTexCoord2f(0.0f, 0.5f);
    glColor3f(0.86f, 0.86f, 0.86f);
    draw_cylinder(0.1, 0.8); // use our custom cylinder function for this

    glEnd();

    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1, 0);

    glTranslatef(cx, cy, cz);
    glRotatef(bodyAngle, 0, 1,
              0); // do all the same things we do for the body for the head
    glTranslatef(0, 0, 0); // the head is separate since it can rotate on its
                           // own when F2 or F3 are pressed.

    glRotatef(headAngle, 0.0f, 1.0f, 0.0f); // for if the head is rotating

    glBegin(GL_QUADS);
    // BEGIN HEAD
    // Left Eye
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.3f, 2.9f, 0.71f);
    glVertex3f(-0.5f, 2.9f, 0.71f);
    glVertex3f(-0.5f, 2.7f, 0.71f);
    glVertex3f(-0.3f, 2.7f, 0.71f);

    // Right Eye
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3f, 2.9f, 0.71f);
    glVertex3f(0.5f, 2.9f, 0.71f);
    glVertex3f(0.5f, 2.7f, 0.71f);
    glVertex3f(0.3f, 2.7f, 0.71f);

    // Mouth
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.53f, 2.2f, 0.71f);
    glVertex3f(-0.5f, 2.2f, 0.71f);
    glVertex3f(-0.5f, 2.4f, 0.71f);
    glVertex3f(0.5f, 2.4f, 0.71f);

    // Upper face
    glColor3f(0.86f, 0.86f, 0.86f);
    glVertex3f(-0.7f, 3.2f, 0.7f);
    glVertex3f(0.7f, 3.2f, 0.7f);
    glVertex3f(0.7f, 3.2f, -0.7f);
    glVertex3f(-0.7f, 3.2f, -0.7f);

    // Bottom face
    glColor3f(0.86f, 0.86f, 0.86f);
    glVertex3f(-0.8f, 1.9f, 0.7f);
    glVertex3f(0.8f, 1.9f, 0.7f);
    glVertex3f(0.8f, 1.9f, -0.7f);
    glVertex3f(-0.8f, 1.9f, -0.7f);

    // Far face.
    glColor3f(0.86f, 0.86f, 0.86f);
    glVertex3f(-0.8f, 1.9f, -0.7f);
    glVertex3f(-0.8f, 3.2f, -0.7f);
    glVertex3f(0.8f, 3.2f, -0.7f);
    glVertex3f(0.8f, 1.9f, -0.7f);

    // Right face.
    glColor3f(0.86f, 0.86f, 0.86f);
    glVertex3f(0.8f, 1.9f, -0.7f);
    glVertex3f(0.8f, 3.2f, -0.7f);
    glVertex3f(0.8f, 3.2f, 0.7f);
    glVertex3f(0.8f, 1.9f, 0.7f);

    // Front face.
    glColor3f(0.86f, 0.86f, 0.86f);
    glVertex3f(-0.8f, 1.9f, 0.7f);
    glVertex3f(0.8f, 1.9f, 0.7f);
    glVertex3f(0.8f, 3.2f, 0.7f);
    glVertex3f(-0.8f, 3.2f, 0.7f);

    // Left Face.
    glColor3f(0.86f, 0.86f, 0.86f);
    glVertex3f(-0.8f, 1.9f, -0.7f);
    glVertex3f(-0.8f, 1.9f, 0.7f);
    glVertex3f(-0.8f, 3.2f, 0.7f);
    glVertex3f(-0.8f, 3.2f, -0.7f);

    glEnd();

    antRot += 30;
    if (antRot == 360)
    { // rotating antenna constantly, bringing back to 0 if it his 360 so it
      // doesn't eventually overflow
      antRot = 0;
    }
  }

  void moveCam(int fKey)
  { // function that handles the camera angles.
    switch (fKey)
    {
    case 1:
      if (eyex > (offx + 0))
      { // this is default view of robot
        eyex--;
      }
      if (eyex < (offx + 0))
      { // each on of these if statements basically is checking if the eye is in
        // the right position
        eyex++; // relative to the robots offset for the desired camera angle.
      } // this is standard across all cases (1-12) for every camera angle
        // required
      if (eyey > 5)
      { // 1-4 are the behind view of the robot (depending on what direction he
        // is facing)
        eyey--; // 5-8 are the angled camera views of the robot
      }         // 9-12 are the farther out angled camera views of the robot
      if (eyey < 5)
      { // All of these use offx and offz to determine how far offset the robot
        // currently is from the origin
        eyey++;
      }
      if (eyez > (offz + -15))
      {
        eyez--;
      }
      if (eyez < (offz + -15))
      {
        eyez++;
      }
      break;
    case 2:
      if (eyex > (offx + -15))
      {
        eyex--;
      }
      if (eyex < (offx + -15))
      {
        eyex++;
      }
      if (eyey > 5)
      {
        eyey--;
      }
      if (eyey < 5)
      {
        eyey++;
      }
      if (eyez > (offz + 0))
      {
        eyez--;
      }
      if (eyez < (offz + 0))
      {
        eyez++;
      }
      break;
    case 3:
      if (eyex > (offx + 0))
      {
        eyex--;
      }
      if (eyex < (offx + 0))
      {
        eyex++;
      }
      if (eyey > 5)
      {
        eyey--;
      }
      if (eyey < 5)
      {
        eyey++;
      }
      if (eyez > (offz + 15))
      {
        eyez--;
      }
      if (eyez < (offz + 15))
      {
        eyez++;
      }
      break;
    case 4:
      if (eyex > (offx + 15))
      {
        eyex--;
      }
      if (eyex < (offx + 15))
      {
        eyex++;
      }
      if (eyey > 5)
      {
        eyey--;
      }
      if (eyey < 5)
      {
        eyey++;
      }
      if (eyez > (offz + 0))
      {
        eyez--;
      }
      if (eyez < (offz + 0))
      {
        eyez++;
      }
      break;
    case 5:
      if (eyex > (offx + 10))
      {
        eyex--;
      }
      if (eyex < (offx + 10))
      {
        eyex++;
      }
      if (eyey > 10)
      {
        eyey--;
      }
      if (eyey < 10)
      {
        eyey++;
      }
      if (eyez > (offz + -10))
      {
        eyez--;
      }
      if (eyez < (offz + -10))
      {
        eyez++;
      }
      break;
    case 6:
      if (eyex > (offx + -10))
      {
        eyex--;
      }
      if (eyex < (offx + -10))
      {
        eyex++;
      }
      if (eyey > 10)
      {
        eyey--;
      }
      if (eyey < 10)
      {
        eyey++;
      }
      if (eyez > (offz + -10))
      {
        eyez--;
      }
      if (eyez < (offz + -10))
      {
        eyez++;
      }
      break;
    case 7:
      if (eyex > (offx + -10))
      {
        eyex--;
      }
      if (eyex < (offx + -10))
      {
        eyex++;
      }
      if (eyey > 10)
      {
        eyey--;
      }
      if (eyey < 10)
      {
        eyey++;
      }
      if (eyez > (offz + 10))
      {
        eyez--;
      }
      if (eyez < (offz + 10))
      {
        eyez++;
      }
      break;
    case 8:
      if (eyex > (offx + 10))
      {
        eyex--;
      }
      if (eyex < (offx + 10))
      {
        eyex++;
      }
      if (eyey > 10)
      {
        eyey--;
      }
      if (eyey < 10)
      {
        eyey++;
      }
      if (eyez > (offz + 10))
      {
        eyez--;
      }
      if (eyez < (offz + 10))
      {
        eyez++;
      }
      break;
    case 9:
      if (eyex > (offx + 50))
      {
        eyex--;
      }
      if (eyex < (offx + 50))
      {
        eyex++;
      }
      if (eyey > 50)
      {
        eyey--;
      }
      if (eyey < 50)
      {
        eyey++;
      }
      if (eyez > (offz + -50))
      {
        eyez--;
      }
      if (eyez < (offz + -50))
      {
        eyez++;
      }
      break;
    case 10:
      if (eyex > (offx + -50))
      {
        eyex--;
      }
      if (eyex < (offx + -50))
      {
        eyex++;
      }
      if (eyey > 50)
      {
        eyey--;
      }
      if (eyey < 50)
      {
        eyey++;
      }
      if (eyez > (offz + -50))
      {
        eyez--;
      }
      if (eyez < (offz + -50))
      {
        eyez++;
      }
      break;
    case 11:
      if (eyex > (offx + -50))
      {
        eyex--;
      }
      if (eyex < (offx + -50))
      {
        eyex++;
      }
      if (eyey > 50)
      {
        eyey--;
      }
      if (eyey < 50)
      {
        eyey++;
      }
      if (eyez > (offz + 50))
      {
        eyez--;
      }
      if (eyez < (offz + 50))
      {
        eyez++;
      }
      break;
    case 12:
      if (eyex > (offx + 50))
      {
        eyex--;
      }
      if (eyex < (offx + 50))
      {
        eyex++;
      }
      if (eyey > 50)
      {
        eyey--;
      }
      if (eyey < 50)
      {
        eyey++;
      }
      if (eyez > (offz + 50))
      {
        eyez--;
      }
      if (eyez < (offz + 50))
      {
        eyez++;
      }
      break;
    }
  }

  void bodyRot(bool &robRotR, bool &robRotL)
  {
    if (robRotR)
    {
      bodyAngle +=
          3; // if the robot is supposed to be rotating right, we add 3 until we
             // hit a 90 degree angle (which is north/east/south/west)
      if ((bodyAngle == 90) || (bodyAngle == 180) || (bodyAngle == 270) ||
          (bodyAngle == 360) || (bodyAngle == 0))
      { // we only want to rotate to a 90 degree direction
        if (bodyAngle == 360)
        { // to prevent overflow we reset to 0 when we hit 360
          bodyAngle = 0;
        }
        robRotR = false; // when we hit a 90 degree angle we set it to no longer
                         // be rotating
      }
      if ((bodyAngle == -90) || (bodyAngle == -180) || (bodyAngle == -270) ||
          (bodyAngle == -360) || (bodyAngle == 0))
      {
        if (bodyAngle == -360)
        { // still must account for if the robot was previously rotated to the
          // left, checking for 90 degree angles in the negative direction as
          // well
          bodyAngle = 0;
        }
        robRotR = false;
      }
    }
    if (robRotL)
    {
      bodyAngle -= 3; // identical to previous if statement but reversed for
                      // rotating to the left instead
      if ((bodyAngle == -90) || (bodyAngle == -180) || (bodyAngle == -270) ||
          (bodyAngle == -360) || (bodyAngle == 0))
      {
        if (bodyAngle == -360)
        {
          bodyAngle = 0;
        }
        robRotL = false;
      }
      if ((bodyAngle == 90) || (bodyAngle == 180) || (bodyAngle == 270) ||
          (bodyAngle == 360) || (bodyAngle == 0))
      {
        if (bodyAngle == -360)
        {
          bodyAngle = 0;
        }
        robRotL = false;
      }
    }
  }

  void headRotate(bool headTurnR, bool headTurnL)
  {
    if (headAngle == 360)
    { // if the angle rotates a full 360 we reset it to prevent overflow
      headAngle = 0;
    }
    if (headAngle == -360)
    { // if the angle rotates a full 360 we reset it to prevent overflow
      headAngle = 0;
    }
    if (headTurnR == true)
    { // if the head turn right key is pressed down we rotate the head until it
      // no longer is
      headAngle -= 2;
    }

    if (headTurnL == true)
    { // if the head turn left key is pressed down we rotate the head until it
      // no longer is
      headAngle += 2;
    }

    if ((headAngle != 0) && (headTurnL == false) && (headTurnR == false))
    { // when we are no longer turning we reset the head to forward position
      if (headAngle > 0)
      {
        headAngle -= 2;
      }
      if (headAngle < 0)
      {
        headAngle += 2;
      }
    }
  }
};
#endif
