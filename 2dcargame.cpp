#include "shared/gltools.h" // OpenGL toolkit
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
 
using namespace std;
 
#define carX_CENTRE -150.0      /* centre point of the car */
#define carY_CENTRE -150.0
#define X_CENTRE 0.0            /* 0,0 */
#define Y_CENTRE 0.0
 
#define LENGTH   20.0 
 
 
 
int Wwidth;
int Wheight;
 
int xOffset = 0, yOffset = 0;   //initializes the amount to move the car at 0
float angle = 0.0;      //the angle that the car will be rotated
 
boolean goingUp = false;
boolean goingDown = false;
boolean goingLeft = false;
boolean goingRight = false;
 
 
/* reshape callback function executed when window is moved or resized */
void reshape(int width, int height)
{
Wwidth = width;
Wheight = height;
//set the matrix mode to PROJECTION
glMatrixMode( GL_PROJECTION );
glLoadIdentity();
glViewport(0, 0, width, height);
// use orthographic (parallel) projection
glOrtho(-200.0, 200.0, -200.0, 200.0, -200.0, 200.0);
//set the matrix mode to MODEL
glMatrixMode( GL_MODELVIEW );
 
}
 
 
int GetRandomNumberX(int nLow, int nHigh)   //This generates a random number "x" between the passed range nLow-nHigh
{
return (rand() % (nHigh - nLow + 1)) + nLow;
}
 
int GetRandomNumberY(int nLow, int nHigh)           //This generates a random number "y" between the passed range nLow-nHigh
{
return (rand() % (nHigh - nLow + 1)) + nLow;
}
 
 
struct collisionBox {
float x, y; // Horizontal and vertical position, respectively.  These refer to the upper left corner of the sprite for consistency.
float w, h; //Width and height of box, respectively.
};
 
 
void drawBoundary(float length,float x,float y)
{
 
 glBegin(GL_LINE_LOOP);
 glColor3f(1.0,1.0,1.0);
  glVertex2f( X_CENTRE - length - 20, Y_CENTRE - length);   //these 4 points draw the game boundary
  glVertex2f( X_CENTRE - length - 20, Y_CENTRE + length);   //these 4 points draw the game boundary
  glVertex2f( X_CENTRE + length + 20, Y_CENTRE + length);   //these 4 points draw the game boundary
  glVertex2f( X_CENTRE + length + 20, Y_CENTRE - length);   //these 4 points draw the game boundary
glEnd();
 
glFlush();     /* execute drawing commands in buffer */
 
  struct collisionBox boundaryTop;
boundaryTop.x=-190;
boundaryTop.y=200;
boundaryTop.w=380;
boundaryTop.h=10;
}
 
const float obstacle1x = GetRandomNumberX( -20,20);
const float obstacle1y = GetRandomNumberY( -120,-80);
const float obstacle2x = GetRandomNumberX( -120,-100);
const float obstacle2y = GetRandomNumberY( 30,80);
const float obstacle3x = GetRandomNumberX( 0,60);
const float obstacle3y = GetRandomNumberY( 0,30);
const float obstacle4x = GetRandomNumberX( 100,110);
const float obstacle4y = GetRandomNumberY( 90,100);
const float obstacle5x = GetRandomNumberX( -150,-160);
const float obstacle5y = GetRandomNumberY( -70,-110);
 
void drawObstacle1()
{
 
float x = obstacle1x;
float y = obstacle1y;
 
 
glBegin(GL_POLYGON);
glColor3f(0.0,1.0,0.0);
  glVertex2f( x, y);    
  glVertex2f( x, y + 30);
  glVertex2f( x + 30, y + 30);
  glVertex2f( x + 30, y);
glEnd();
glFlush();     /* execute drawing commands in buffer */
 
 
 
 
struct collisionBox obstacle1;
obstacle1.x=x;
obstacle1.y=y;
obstacle1.w=30;
obstacle1.h=30;
 
}
 
 
 
void drawObstacle2()
{
float x = obstacle2x;
float y = obstacle2y;
 
glBegin(GL_POLYGON);
glColor3f(0.0,1.0,0.0);
glVertex2f( x, y);  
  glVertex2f( x, y + 30);
  glVertex2f( x + 30, y + 30);
  glVertex2f( x + 30, y);
glEnd();
 
glFlush();     /* execute drawing commands in buffer */
 
struct collisionBox obstacle2;
obstacle2.x=x;
obstacle2.y=y;
obstacle2.w=30;
obstacle2.h=30;
 
}
 
void drawObstacle3()
{
 
float x = obstacle3x;
float y = obstacle3y;
 
glBegin(GL_POLYGON);
glColor3f(0.0,1.0,0.0);
   glVertex2f( x, y);   
  glVertex2f( x, y + 30);
  glVertex2f( x + 30, y + 30);
  glVertex2f( x + 30, y);
glEnd();
 
glFlush();     /* execute drawing commands in buffer */
 
struct collisionBox obstacle3;
obstacle3.x=x;
obstacle3.y=y;
obstacle3.w=30;
obstacle3.h=30;
}
 
void drawObstacle4()
{
 
float x = obstacle4x;
float y = obstacle4y;
 
glBegin(GL_POLYGON);
glColor3f(0.0,1.0,0.0);
     glVertex2f( x, y); 
  glVertex2f( x, y + 30);
  glVertex2f( x + 30, y + 30);
  glVertex2f( x + 30, y);
glEnd();
 
glFlush();     /* execute drawing commands in buffer */
 
struct collisionBox obstacle4;
obstacle4.x=x;
obstacle4.y=y;
obstacle4.w=30;
obstacle4.h=30;
}
 
void drawObstacle5()
{
 
    float x = obstacle5x;
float y = obstacle5y;
 
glBegin(GL_POLYGON);
glColor3f(0.0,1.0,0.0);
      glVertex2f( x, y);    
  glVertex2f( x, y + 30);
  glVertex2f( x + 30, y + 30);
  glVertex2f( x + 30, y);
glEnd();
 
glFlush();     /* execute drawing commands in buffer */
 
struct collisionBox obstacle5;
obstacle5.x=x;
obstacle5.y=y;
obstacle5.w=30;
obstacle5.h=30;
}
 
void drawRedGate()
{
glBegin(GL_POLYGON);
glColor3f(1.0,0.0,0.0);
  glVertex2f( -160, -170);  //these 4 points draw the red entry gate
  glVertex2f( -160, -160);  //these 4 points draw the red entry gate
  glVertex2f( -100, -160);  //these 4 points draw the red entry gate
  glVertex2f( -100, -170);  //these 4 points draw the red entry gate
 glEnd();
 
 
}
 
void drawGreenGate()
{
glBegin(GL_POLYGON);
glColor3f(0.0,1.0,0.0);
  glVertex2f( 160, 170);    //these 4 points draw the green exit gate
  glVertex2f( 160, 160);    //these 4 points draw the green exit gate
  glVertex2f( 100, 160);    //these 4 points draw the green exit gate
  glVertex2f( 100, 170);    //these 4 points draw the green exit gate
  glEnd();
 
 struct collisionBox exitGate;
exitGate.x=100;
exitGate.y=170;
exitGate.w=60;
exitGate.h=10;
 
}
 
 
void drawCar(float length,float x,float y, int xOffset, int yOffset, float angle)
{
 
glPushMatrix();
glLoadIdentity();
glTranslatef(xOffset,yOffset,0);
    glTranslatef(carX_CENTRE,carY_CENTRE,0.0);
glRotatef(angle,0,0,1);
glTranslatef(-carX_CENTRE,-carY_CENTRE,0.0);
 glBegin(GL_POLYGON);
  glColor3f(0.8, 1.0, 0.8);
  glVertex2f( carX_CENTRE - LENGTH / 2, carY_CENTRE - LENGTH / 2);   //these 4 points draw the middle of the car
  glVertex2f( carX_CENTRE - LENGTH / 2, carY_CENTRE + LENGTH / 2);  //these 4 points draw the middle of the car
  glVertex2f( carX_CENTRE + 20, carY_CENTRE + LENGTH / 2);  //these 4 points draw the middle of the car
  glVertex2f( carX_CENTRE + 20, carY_CENTRE - LENGTH / 2);  //these 4 points draw the middle of the car
  glEnd();
  glPopMatrix();
  glFlush();
 
 glPushMatrix();
  glLoadIdentity();
glTranslatef(xOffset,yOffset,0);
glTranslatef(carX_CENTRE,carY_CENTRE,0.0);
glRotatef(angle,0,0,1);
glTranslatef(-carX_CENTRE,-carY_CENTRE,0.0);
  glBegin(GL_POLYGON);
  glColor3f(1.0, 1.0, 1.0);
  glVertex2f( carX_CENTRE + 20, carY_CENTRE - LENGTH / 2);  //these 4 points draw the front of the car
  glVertex2f( carX_CENTRE + 20, carY_CENTRE + LENGTH / 2);  //these 4 points draw the front of the car
  glVertex2f( carX_CENTRE + 30, carY_CENTRE + LENGTH / 2);  //these 4 points draw the front of the car
  glVertex2f( carX_CENTRE + 30, carY_CENTRE - LENGTH / 2);  //these 4 points draw the front of the car
  glEnd();
 glPopMatrix();
glFlush();
 
 glPushMatrix();
 glLoadIdentity();
glTranslatef(xOffset,yOffset,0);
    glTranslatef(carX_CENTRE,carY_CENTRE,0.0);
glRotatef(angle,0,0,1);
glTranslatef(-carX_CENTRE,-carY_CENTRE,0.0);
  glBegin(GL_POLYGON);
  glColor3f(1.0, 1.0, 1.0);
  glVertex2f( carX_CENTRE - 20, carY_CENTRE - LENGTH / 2);  //these 4 points draw the back of the car
  glVertex2f( carX_CENTRE - 20, carY_CENTRE + LENGTH / 2);  //these 4 points draw the back of the car
  glVertex2f( carX_CENTRE - LENGTH / 2, carY_CENTRE + LENGTH / 2);  //these 4 points draw the back of the car
  glVertex2f( carX_CENTRE - LENGTH / 2, carY_CENTRE - LENGTH / 2);  //these 4 points draw the back of the car
 glEnd();
glPopMatrix();
 
 
glFlush();
 
  glPushMatrix();
  glLoadIdentity();
glTranslatef(xOffset,yOffset,0);
    glTranslatef(carX_CENTRE,carY_CENTRE,0.0);
glRotatef(angle,0,0,1);
glTranslatef(-carX_CENTRE,-carY_CENTRE,0.0);
  glBegin(GL_POLYGON);
  glColor3f(1.0, 1.0, 0.0);
  glVertex2f( carX_CENTRE - 28, carY_CENTRE - LENGTH / 2);  //these 4 points draw the exhaust
  glVertex2f( carX_CENTRE - 28, carY_CENTRE - LENGTH / 2 + 3);  //these 4 points draw the exhaust
  glVertex2f( carX_CENTRE - 20, carY_CENTRE - LENGTH / 2 + 3);  //these 4 points draw the exhaust
  glVertex2f( carX_CENTRE - 20, carY_CENTRE - LENGTH / 2);  //these 4 points draw the exhaust
 glEnd();
 glPopMatrix();
 glFlush();
 
 struct collisionBox car;
car.x=carX_CENTRE + 30;
car.y=carY_CENTRE + LENGTH / 2;
car.w=20;
car.h=50;
 
}
 
 
void doCollisionDetection(collisionBox car, collisionBox obstacle1, collisionBox obstacle2, collisionBox obstacle3, collisionBox obstacle4,collisionBox obstacle5, collisionBox boundaryTop){
 
 
 
    if (((car.x >= obstacle1.x && car.x <= (obstacle1.x + obstacle1.w))
    || ((car.x + car.w) >= obstacle1.x && (car.x + car.w) <= (obstacle1.x + obstacle1.w))))
 
    {
        if (((car.y >= obstacle1.y && car.y <= (obstacle1.y + obstacle1.h))
             || ((car.y + car.h) >= obstacle1.y && (car.y + car.h) <= (obstacle1.y + obstacle1.h))))
        {
 
        } 
 
    }
 
}
    /*     {
 
 
 
/* display callback function called whenever contents of window need to be re-displayed     */
void display(void)
{
glClear (GL_COLOR_BUFFER_BIT);   /* clear window */
glLoadIdentity();
 
drawBoundary(170,0,0);  
 
drawRedGate();
 
drawGreenGate();
 
drawCar(50,0,0,xOffset,yOffset,angle);
 
drawParticles();
 
 
drawObstacle1();
drawObstacle2();
drawObstacle3();
drawObstacle4();
drawObstacle5();
 
 
glutSwapBuffers();
 
 
}
 
 
GLvoid IdleFunc(GLvoid)
{
glutPostRedisplay();
}
 
 /* graphics initialisation */ 
void init(void)
{
glClearColor (0.0, 0.0, 0.0, 0.0);   /* window will be cleared to black */
}
 
 
int main(int argc, char* argv[])//standard c entry signature
{
/* window management code ... */
/* initialises GLUT and processes any command line arguments */  
glutInit(&argc, argv);
/* use double-buffered window and RGBA colour model */
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
/* window width = 400 pixels, height = 400 pixels */
glutInitWindowSize (400, 400);
/* window upper left corner at (100, 100) */
glutInitWindowPosition (100, 100);
/* creates an OpenGL window and set its title bar*/
glutCreateWindow("Coursework 1");   
init(); 
 
glutDisplayFunc(display);
 
glutSpecialFunc(specialKeys);
 //  glutSpecialUpFunc(keyGoneUp);
 
glutReshapeFunc(reshape);
 //  SetupRC();
glutIdleFunc(IdleFunc);
glutMainLoop();
 
 
 
return 0;
 
 
}