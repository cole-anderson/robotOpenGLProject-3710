#define PROGRAM_TITLE "Fortnite 2 - The Fork Knifening ft. Robot"
#define DISPLAY_INFO "CPSC 3710"
/*
File: main.cpp
Contributors:
  Cole Anderson
  Liam King
  Brayden Ormann
Purpose:
  Main file used to impliment functionality of robot, objects(buildings) and world.
  Robot is able to move around the world limited by intersections and boundaries.
  Robot is able to destroy buildings of which are generated randomly in certain blocks


*/
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
#include "objects.cpp"

#define PI 3.1415927

int Window_ID;
int Window_Width = 600;
int Window_Height = 400;


int recentfKey = 1; //camera angle starts at the '1' position. This position is behind the robots head

bool pausedState ; //game starts unpaused and is controlled by 'p' key to change this state

void moveCam(int); //forward declaration of moveCam function.

bool headTurnR = false; //can head turn right
bool headTurnL = false; // can head turn left
bool robRotR = false; //is robot rotating right
bool robRotL = false; //is robot rotating left
bool robNorth = true; //is robot facing north (starts off north)
bool robEast = false; //is robot facing east
bool robSouth = false; //is robot facing south
bool robWest = false; //is robot facing west
int offAddz = 5; //we start off facing north so we want to be able to move that direction, this is used for movement/camera on z key
int offAddx = 0; //same as offAddz
int randNums[400]; //array to hold random numbers generated for building generation
int buildHits[400]; //sister array to hold hit values of buildings so they can be destroyed.
Robot robot; //robot object to do most functions.

static void PrintString(void *font, char *str)
{
   int i,len=strlen(str);

   for(i=0;i < len; i++)
      glutBitmapCharacter(font,*str++);
}

void drawObjects(GLenum mode)
{
  int counter = 0;
  robot.modeV = mode; //what mode we are currently in
  for (int i = 0; i<20; i++) { //20 blocks by 20 blocks
    for (int j = 0; j<20; j++) {
      int build = randNums[counter];
      switch(build) { //depending on the random numbers generated at program start, we draw buildings into different blocks.
        case 1:
        robot.drawBuildingA(0 + i*60, 0+j*60);
        counter++; //increment through the array of random numbers
        break;
        case 2:
        robot.drawBuildingB(0 + i*60, 0+j*60);
        counter++;
        break;
        case 3:
        robot.drawBuildingC(0+ i*60, 0+j*60);
        counter++;
        break;
        default: //case for if the building is destroyed (its number will be set to 5 and fall here)
        robot.drawBuildingC(20000, 20000); //draws the building out of view to give the illusion it is destroyed
        counter++;
        break;
      }
  }
  }


}

void CallBackRenderScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


   glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glPushMatrix();
robot.draw_environment(GL_RENDER); //draw the ground/blocks
glPopMatrix();

drawObjects(GL_RENDER); //draw buildings into the world


glPushMatrix();
glLoadIdentity();
robot.drawRobot(); //draw robot into the world
glPopMatrix();


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

   robot.headRotate(headTurnR, headTurnL); //function for rotating head if head is supposed to be rotating

   robot.bodyRot(robRotR, robRotL); //function for rotating body if body is supposed to be rotating
   robot.moveCam(recentfKey);       //passing an int to identify what the current camera angle should be, moving there if it already isn't

}
void processHits (GLint hits, GLuint buffer[])
{
   unsigned int i, j;
   GLuint names, *ptr, minZ,*ptrNames, numberOfNames;

   printf ("hits = %d\n", hits);
   ptr = (GLuint *) buffer;
   minZ = 0xffffffff;
   for (i = 0; i < hits; i++) {
      names = *ptr;
	  ptr++;
	  if (*ptr < minZ) {
		  numberOfNames = names;
		  minZ = *ptr;
		  ptrNames = ptr+2;
	  }

	  ptr += names+2;
	}
  printf ("The closest hit names are:");
  ptr = ptrNames;
  if (hits == 0) { //if no building are hit, we get out of this function as nothing more is to be done
    return;
  }
  for (j = 0; j < numberOfNames; j++,ptr++) {
        std::cout << *ptr % 400 << std::endl;
     if (buildHits[*ptr % 400] > 0) { //if we hit a building an the hit counter is still above 0
       buildHits[*ptr % 400]--;       //subtract one from the hit counter
     }
     if (buildHits[*ptr % 400] == 0) { //if the hit counter is now 0, we destroy the building by setting the number to generate it to a different value
       randNums[*ptr % 400] = 5;       //this falls to a different case in our switch statement and draws the building out of view
     }

  }
  printf ("\n");
}


#define SIZE 10000

void mouse(int button, int state, int x, int y)
{
   GLuint selectBuf[SIZE]; // Selection buffer, which is an array of size 512.
   GLint hits;
   GLint viewport[4]; // Current viewport size. See below.
   if(!pausedState){
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)  // When the left mouse button is pressed, we start picking.
   {

   	glGetIntegerv (GL_VIEWPORT, viewport);  // Get the viewport size and put them into the array viewport.

   	glSelectBuffer (SIZE, selectBuf); // Create the selection buffer for preparing picking.
   	glRenderMode(GL_SELECT);          // Enter into the selection mode.

   	glInitNames();    // Initialize the name stack. We need to push our objects into the stack.
   	glPushName(-1);

   	glMatrixMode (GL_PROJECTION);   // Need to create a new projection matrix. We select projection stack first.
   	glPushMatrix ();                // Need to save the old one, which is our projection for rendering on the screen.
   	glLoadIdentity ();              // Start a new projection matrix calculation.

	// Create 5x5 pixel picking region near the current mouse pointer location
	// This is where we need to pay attention to.
	//
	// Note the second parameter of gluPickMatrix. OpenGL has a different origin
	// for its window coordinates than the operation system. The second parameter
	// provides for the conversion between the two systems, i.e. it transforms the
	// origin from the upper left corner, as provided by GLUT (related to the hardware,
	// for this case, the mouse pointer's location), into the bottom left corner,
	// which is the one OpenGL uses.
	//
	// The picking region in this case is a 5x5 window. You may find that it is not
	// appropriate for your application. Do some tests to find an appropriate value
	// if you're finding it hard to pick the right objects.
	//
   	gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),
                  	5.1,5.1, viewport);
    gluPerspective(45.0f, (GLfloat)Window_Width/(GLfloat)Window_Height, 1.0, 250.0f);
    glMatrixMode(GL_MODELVIEW);
  	drawObjects(GL_SELECT);             // See below for the tricks we play here.


   	glMatrixMode (GL_PROJECTION);       // Now that the projection is done,
   	glPopMatrix ();                     // we don't need it any more. We have to
   	glFlush ();                         // retrieve the project matrix for displaying on the screen.

   	hits = glRenderMode (GL_RENDER);    // Leave the selection mode.

    processHits (hits, selectBuf);      // To see which objects are hit. See below

   	glutPostRedisplay();
   }
 }
}



void keyboard(unsigned char key, int x, int y)
{


  if(!pausedState){

   switch (key) {
     case 112: //p key

      glutDisplayFunc(CallBackRenderScene);
       glutIdleFunc(NULL);
       pausedState = true;
       break;

   case 122: // z key
       robot.cz += offAddz; //move the robot forward, the offAddx and offAddz change
       robot.cx += offAddx; //based on the direction the robot is currently facing
       robot.eyez += offAddz; //to keep up with where the robot is
       robot.atz += offAddz;
       robot.atx += offAddx;
       robot.eyex += offAddx;
       robot.offx += offAddx;
       robot.offz += offAddz;
       switch (robot.cx) {
       case 545: //if at the boundary, we cannot go forward
        robot.cx -= 5;
        robot.offx -= 5;
        robot.atx -= 5;
        robot.eyex -= 5;
        break;
       case -665: //if at the boundary, we cannot go forward
        robot.cx += 5;
        robot.offx += 5;
        robot.atx += 5;
        robot.eyex += 5;
        break;
       default:
        break;
       }
       switch(robot.cz) { //if at the boundary, we cannot go forward
       case 545:
        robot.cz -= 5;
        robot.offz -= 5;
        robot.atz -= 5;
        robot.eyez -= 5;
        break;
       case -665: //if at the boundary, we cannot go forward
        robot.cz += 5;
        robot.offz += 5;
        robot.atz += 5;
        robot.eyez += 5;
        break;
       default:
        break;
       }
      break;
   case 97: // a key
   if ((robot.cx % 60 == 0) && (robot.cz % 60 == 0)) { //if robot is at an intersection
   if (robNorth) { //facing north
           if (!robRotL && !robRotR) {
           robRotL = true; //start turning left to eventually face east
           offAddx = -5; //change direction that is being implemented
           offAddz = 0;
           robNorth = false; //no longer facing north
           robEast = true;   //now facing east!
           recentfKey -= 1;
           if (recentfKey == 0) { //changing camera angle relative to direction and robot
             recentfKey = 4;      //this insures the camera turns to be the same lookat view when you turn the robot
             break;               //the rest of the if's for the different direction work identically except with different
           }                      //parameters being changed.
           if (recentfKey == 4) {
             recentfKey = 8;
             break;
           }
           if (recentfKey == 8) {
             recentfKey = 12;
           }
           }
   }
   if (robEast) {
           if (!robRotL && !robRotR) {
           robRotL = true;
           offAddx = 0;
           offAddz = -5;
           robEast = false;
           robSouth = true;
           recentfKey -= 1;
           if (recentfKey == 0) {
             recentfKey = 4;
             break;
           }
           if (recentfKey == 4) {
             recentfKey = 8;
             break;
           }
           if (recentfKey == 8) {
             recentfKey = 12;
           }
           }
   }
   if (robSouth) {
           if (!robRotL && !robRotR) {
           robRotL = true;
           offAddx = 5;
           offAddz = 0;
           robSouth = false;
           robWest = true;
           recentfKey -= 1;
           if (recentfKey == 0) {
             recentfKey = 4;
             break;
           }
           if (recentfKey == 4) {
             recentfKey = 8;
             break;
           }
           if (recentfKey == 8) {
             recentfKey = 12;
           }
           }
   }
   if (robWest) {
           if (!robRotL && !robRotR) {
           robRotL = true;
           offAddx = 0;
           offAddz = 5;
           robWest = false;
           robNorth = true;
           recentfKey -= 1;
           if (recentfKey == 0) {
             recentfKey = 4;
             break;
           }
           if (recentfKey == 4) {
             recentfKey = 8;
             break;
           }
           if (recentfKey == 8) {
             recentfKey = 12;
           }
         }

   }
 }
      break;
   case 113: // q key
   if ((robot.cx % 60 == 0) && (robot.cz % 60 == 0)) { //if the robot is at an intersection
   if (robNorth) { //facing north
           if (!robRotL && !robRotR) { //turn left to face west
           robRotR = true;
           offAddx = 5;
           offAddz = 0; //change what direction is being incremented when moving
           robNorth = false;
           robWest = true;
           recentfKey += 1;
           if (recentfKey == 5) { //changing camera angle relative to direction and robot
             recentfKey = 1;      //this insures the camera turns to be the same lookat view when you turn the robot
           }                      //the rest of the if's for the different direction work identically except with different
           if (recentfKey == 9) { //parameters being changed.
             recentfKey = 5;
           }
           if (recentfKey == 13) {
             recentfKey = 9;
           }
           }
   }
   if (robEast) {
           if (!robRotL && !robRotR) {
           robRotR = true;
           offAddx = 0;
           offAddz = 5;
           robEast = false;
           robNorth = true;
           recentfKey += 1;
           if (recentfKey == 5) {
             recentfKey = 1;
           }
           if (recentfKey == 9) {
             recentfKey = 5;
           }
           if (recentfKey == 13) {
             recentfKey = 9;
           }
           }
   }
   if (robSouth) {
           if (!robRotL && !robRotR) {
           robRotR = true;
           offAddx = -5;
           offAddz = 0;
           robSouth = false;
           robEast = true;
           recentfKey += 1;
           if (recentfKey == 5) {
             recentfKey = 1;
           }
           if (recentfKey == 9) {
             recentfKey = 5;
           }
           if (recentfKey == 13) {
             recentfKey = 9;
           }
           }
   }
   if (robWest) {
           if (!robRotL && !robRotR) {
           robRotR = true;
           offAddx = 0;
           offAddz = -5;
           robWest = false;
           robSouth = true;
           recentfKey += 1;
           if (recentfKey == 5) {
             recentfKey = 1;
           }
           if (recentfKey == 9) {
             recentfKey = 5;
           }
           if (recentfKey == 13) {
             recentfKey = 9;
           }
         }

   }
 }

      break;
   case 114: // r key
       if ((robot.cx == 540) || (robot.cx == -660) || (robot.cz == 540) || (robot.cz == -660)) { //if the key is pressed while the robot is at the boundary
       robot.eyez = -15.0; //reset all positional values
       robot.cz = 0;
       robot.cx = 0;
       robot.atx = 0;
       robot.atz = 0;
       robot.eyex = 0;
       robot.offx = 0;
       robot.offz = 0;
       }
      break;
   default:
      printf ("No case assigned for %d.\n", key);
      break;
    }
  }
  else if(key = 112)
  {
    glutIdleFunc(CallBackRenderScene);
    pausedState = false;
  }


}

void speckeyboard(int key, int x, int y) {
  if(!pausedState){
    if (key == GLUT_KEY_F1) { //depending on what direction the robot is facing we set the camera appropriately for the defined lookats
        if (robNorth) {
          recentfKey = 1; //recent fkey is simply a int specifying what camera angle to use relative to the robot
        }
        if (robEast) {
          recentfKey = 4;
        }
        if (robSouth) {
          recentfKey = 3;
        }
        if (robWest) {
          recentfKey = 2;
        }
    }

    if (key == GLUT_KEY_F2) { //if the f2 key is pressed we begin rotating the robots head to the right
        headTurnR = true;
    }

    if (key == GLUT_KEY_F3) { //if the f3 key is pressed we begin rotating the robots head to the left
        headTurnL = true;
    }

    if (key == GLUT_KEY_F4) {
        if (robNorth) {
          recentfKey = 1; //recent fkey is simply a int specifying what camera angle to use relative to the robot
        }
        if (robEast) {
          recentfKey = 4;
        }
        if (robSouth) {
          recentfKey = 3;
        }
        if (robWest) {
          recentfKey = 2;
        }
    }

    if (key == GLUT_KEY_F6) { //depending on what direction the robot is facing we set the camera appropriately for the defined lookats
      if (robNorth) {
        recentfKey = 6;
      }
      if (robEast) {
        recentfKey = 5;
      }
      if (robSouth) {
        recentfKey = 8;
      }
      if (robWest) {
        recentfKey = 7;
      }
    }

    if (key == GLUT_KEY_F5) { //depending on what direction the robot is facing we set the camera appropriately for the defined lookats
      if (robNorth) {
        recentfKey = 5;
      }
      if (robEast) {
        recentfKey = 8;
      }
      if (robSouth) {
        recentfKey = 7;
      }
      if (robWest) {
        recentfKey = 6;
      }
    }

    if (key == GLUT_KEY_F7) { //depending on what direction the robot is facing we set the camera appropriately for the defined lookats
      if (robNorth) {
        recentfKey = 7;
      }
      if (robEast) {
        recentfKey = 6;
      }
      if (robSouth) {
        recentfKey = 5;
      }
      if (robWest) {
        recentfKey = 8;
      }
    }

    if (key == GLUT_KEY_F8) { //depending on what direction the robot is facing we set the camera appropriately for the defined lookats
      if (robNorth) {
        recentfKey = 8;
      }
      if (robEast) {
        recentfKey = 7;
      }
      if (robSouth) {
        recentfKey = 6;
      }
      if (robWest) {
        recentfKey = 5;
      }
    }

    if (key == GLUT_KEY_F9) { //depending on what direction the robot is facing we set the camera appropriately for the defined lookats
      if (robNorth) {
        recentfKey = 9;
      }
      if (robEast) {
        recentfKey = 12;
      }
      if (robSouth) {
        recentfKey = 11;
      }
      if (robWest) {
        recentfKey = 10;
      }
    }

    if (key == GLUT_KEY_F10) { //depending on what direction the robot is facing we set the camera appropriately for the defined lookats
      if (robNorth) {
        recentfKey = 10;
      }
      if (robEast) {
        recentfKey = 9;
      }
      if (robSouth) {
        recentfKey = 12;
      }
      if (robWest) {
        recentfKey = 11;
      }
    }

    if (key == GLUT_KEY_F11) { //depending on what direction the robot is facing we set the camera appropriately for the defined lookats
      if (robNorth) {
        recentfKey = 11;
      }
      if (robEast) {
        recentfKey = 10;
      }
      if (robSouth) {
        recentfKey = 9;
      }
      if (robWest) {
        recentfKey = 12;
      }
    }

    if (key == GLUT_KEY_F12) { //depending on what direction the robot is facing we set the camera appropriately for the defined lookats
      if (robNorth) {
        recentfKey = 12;
      }
      if (robEast) {
        recentfKey = 11;
      }
      if (robSouth) {
        recentfKey = 10;
      }
      if (robWest) {
        recentfKey = 9;
      }
    }
  }
}

void speckeyboarddown(int key, int x, int y) {

    if (GLUT_KEY_F2) { //case for when the F2 key is released and the robots head should no longer be rotating
        headTurnR = false;
    }
    if (GLUT_KEY_F3) { //case for when the F3 key is released and the robots head should no longer be rotating
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
   //Buildings come into view in distance
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,300.0f);

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
   //INITIALIZATION of class attributes of Robot
  robot.atx = 0; //x position of lookat
  robot.aty = 0.0;//y position of lookat
  robot.atz = 0; //z position of lookat
  robot.eyex = 0; //x position of camera eye
  robot.eyey = 4; //y position of camera eye
  robot.eyez = -15; //z position of camera eye
  robot.cx = 0; //x position of robot
  robot.cy = -3.5; //y position of robot
  robot.cz = 0;  //z position of robot
  robot.bodyAngle = 0; //the angle at which the robot is currently.
  robot.headAngle = 0; //angle the head is currently rotated
  robot.antRot = 0; //angle of antenae rotating
  robot.offz = 0; //x offset from the origin
  robot.offx = 0; //z offset from the origin
  robot.nameCount = 0; //counter for naming the buildings for picking function


 //generate a random array of numbers 1-3 for our building generation. The random seed is based on current system time
 //so it should be different each time you run it

  srand(time(NULL));
for (int i = 0; i<400; i++) {
  randNums[i] = rand() % 3 + 1;
}

/*using the previously generated array of random numbers, we associated a sister array of hit values.
*building 1 is -1 for indestructible
*building 2 is 3 for strong building
*building 3 is 1 for weak building
*this array is later accessed when a building is clicked on and the number is de-incremented until it hits 0 which is then removed from the viewing area
*/

for (int i = 0; i <400; i++) {
  if (randNums[i] == 1) {
    buildHits[i] = -1;
  }
  if (randNums[i] == 2) {
    buildHits[i] = 3;
  }
  if (randNums[i] == 3) {
    buildHits[i] = 1;
  }
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
