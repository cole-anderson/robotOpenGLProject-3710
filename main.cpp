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
Robot robot;

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
for (int i = 0; i<20; i++) {
  for (int j = 0; j<20; j++) {
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
      break;
      default:
      robot.drawBuildingA(0 + i*60, 0+j*60);
      break;
    }
}
}

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
   std::cout << robot.atx << " " << robot.eyex << " " << offAddx << std::endl;

   robot.bodyRot(robRotR, robRotL);
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
          recentfKey = 2;
        }
        if (robSouth) {
          recentfKey = 3;
        }
        if (robWest) {
          recentfKey = 4;
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
