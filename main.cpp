#define PROGRAM_TITLE "Fortnite 2 Ft Robot"
#define DISPLAY_INFO "CPSC 3710"

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


int recentfKey = 1;

void moveCam(int);

bool headTurnR = false; //can head turn right
bool headTurnL = false; // can head turn left
bool robRotR = false;
bool robRotL = false;
bool robNorth = true;
bool robEast = false;
bool robSouth = false;
bool robWest = false;
int offAddz = 5;
int offAddx = 0;
int randNums[400];
int buildHits[400];
Robot robot;

static void PrintString(void *font, char *str)
{
   int i,len=strlen(str);

   for(i=0;i < len; i++)
      glutBitmapCharacter(font,*str++);
}

void drawObjects(GLenum mode)
{
  int counter = 0;
  robot.modeV = mode;
  for (int i = 0; i<20; i++) {
    for (int j = 0; j<20; j++) {
      int build = randNums[counter];
      switch(build) {
        case 1:
        robot.drawBuildingA(0 + i*60, 0+j*60);
        counter++;
        break;
        case 2:
        robot.drawBuildingB(0 + i*60, 0+j*60);
        counter++;
        break;
        case 3:
        robot.drawBuildingC(0+ i*60, 0+j*60);
        counter++;
        break;
        default:
        robot.drawBuildingC(20000, 20000);
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
robot.draw_environment(GL_RENDER);
glPopMatrix();
//glTranslatef(605, 0, 605);
drawObjects(GL_RENDER);
//drawBuildingA(0,0);


glPushMatrix();
glLoadIdentity();
robot.drawRobot();
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

   robot.headRotate(headTurnR, headTurnL);

   robot.bodyRot(robRotR, robRotL);
   robot.moveCam(recentfKey);

}
void processHits (GLint hits, GLuint buffer[])
{
   unsigned int i, j;
   GLuint names, *ptr, minZ,*ptrNames, numberOfNames;

   printf ("hits = %d\n", hits);
   std::cout << robot.nameCount << std::endl;
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
  for (j = 0; j < numberOfNames; j++,ptr++) {
     printf ("%d ", *ptr);
     std::cout << *ptr % 400 << std::endl;
     std::cout << randNums[*ptr % 400] << std::endl;
     std::cout << buildHits[*ptr % 400] << std::endl;
     if (buildHits[*ptr % 400] > 0) {
       buildHits[*ptr % 400]--;
     }
     if (buildHits[*ptr % 400] == 0) {
       randNums[*ptr % 400] = 5;
     }

          std::cout << buildHits[*ptr % 400] << std::endl;
  }
  printf ("\n");
}


#define SIZE 10000

void mouse(int button, int state, int x, int y)
{
   GLuint selectBuf[SIZE]; // Selection buffer, which is an array of size 512.
   GLint hits;
   GLint viewport[4]; // Current viewport size. See below.

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
//   	glOrtho (-20.0, 20.0, -20.0, 20.0, -500.0, 600.0);  // This also related how sensitive we want our picking to be.
    gluPerspective(45.0f, (GLfloat)Window_Width/(GLfloat)Window_Height, 1.0, 150.0f);
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



void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   case 122: // z key
       robot.cz += offAddz;
       robot.cx += offAddx;
       robot.eyez += offAddz;
       robot.atz += offAddz;
       robot.atx += offAddx;
       robot.eyex += offAddx;
       robot.offx += offAddx;
       robot.offz += offAddz;
      break;
   case 97: // a key
   if ((robot.cx % 60 == 0) && (robot.cz % 60 == 0)) {
   if (robNorth) {
           if (!robRotL && !robRotR) {
           robRotL = true;
           offAddx = -5;
           offAddz = 0;
           robNorth = false;
           robEast = true;
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
   if ((robot.cx % 60 == 0) && (robot.cz % 60 == 0)) {
   if (robNorth) {
           if (!robRotL && !robRotR) {
           robRotR = true;
           offAddx = 5;
           offAddz = 0;
           robNorth = false;
           robWest = true;
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
   case 32: // space bar
      break;
   default:
      printf ("No case assigned for %d.\n", key);
      break;
    }
}

void speckeyboard(int key, int x, int y) {
    if (key == GLUT_KEY_F1) {
        if (robNorth) {
          recentfKey = 1;
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
    if (key == GLUT_KEY_F2) {
        headTurnR = true;
    }
    if (key == GLUT_KEY_F3) {
        headTurnL = true;
    }

    if (key == GLUT_KEY_F6) {
      if (robNorth) {
        recentfKey = 6;
      }
      if (robEast) {
        recentfKey = 7;
      }
      if (robSouth) {
        recentfKey = 8;
      }
      if (robWest) {
        recentfKey = 5;
      }
    }

    if (key == GLUT_KEY_F5) {
      if (robNorth) {
        recentfKey = 5;
      }
      if (robEast) {
        recentfKey = 6;
      }
      if (robSouth) {
        recentfKey = 7;
      }
      if (robWest) {
        recentfKey = 8;
      }
    }

    if (key == GLUT_KEY_F7) {
      if (robNorth) {
        recentfKey = 7;
      }
      if (robEast) {
        recentfKey = 8;
      }
      if (robSouth) {
        recentfKey = 5;
      }
      if (robWest) {
        recentfKey = 6;
      }
    }

    if (key == GLUT_KEY_F8) {
      if (robNorth) {
        recentfKey = 8;
      }
      if (robEast) {
        recentfKey = 5;
      }
      if (robSouth) {
        recentfKey = 6;
      }
      if (robWest) {
        recentfKey = 7;
      }
    }
    if (key == GLUT_KEY_F9) {
      if (robNorth) {
        recentfKey = 9;
      }
      if (robEast) {
        recentfKey = 10;
      }
      if (robSouth) {
        recentfKey = 11;
      }
      if (robWest) {
        recentfKey = 12;
      }
    }
    if (key == GLUT_KEY_F10) {
      if (robNorth) {
        recentfKey = 10;
      }
      if (robEast) {
        recentfKey = 11;
      }
      if (robSouth) {
        recentfKey = 12;
      }
      if (robWest) {
        recentfKey = 9;
      }
    }

    if (key == GLUT_KEY_F11) {
      if (robNorth) {
        recentfKey = 11;
      }
      if (robEast) {
        recentfKey = 12;
      }
      if (robSouth) {
        recentfKey = 9;
      }
      if (robWest) {
        recentfKey = 10;
      }
    }

    if (key == GLUT_KEY_F12) {
      if (robNorth) {
        recentfKey = 12;
      }
      if (robEast) {
        recentfKey = 9;
      }
      if (robSouth) {
        recentfKey = 10;
      }
      if (robWest) {
        recentfKey = 11;
      }
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
   //INITIALIZATION
  robot.atx = 0;
  robot.aty = 0.0;
  robot.atz = 0; //floats for the at coordinates in our LookAt
  robot.eyex = 0;
  robot.eyey = 4;
  robot.eyez = -15; //the xyz coords for the eye location in our LookAt, starting at 0 0 5
  robot.cx = 0;
  robot.cy = -3.5;
  robot.cz = 0;  //floats for defining coords of the center of cube, cube starts centered at 0 0 0
  robot.bodyAngle = 0; //the angle at which the cube is currently.
  robot.headAngle = 0;
  robot.antRot = 0;
  robot.offz = 0;
  robot.offx = 0;
  robot.nameCount = 0;


  srand(time(NULL));
for (int i = 0; i<400; i++) {
  randNums[i] = rand() % 3 + 1;
}

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
