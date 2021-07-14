#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>
#include <string.h>  // For spring operations.
#include <stdbool.h>

#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h>

int window_width = 600;
int window_height = 500;

static bool paused = false;

float pos_x = 0.0f;
float pos_y = 0.0f;
float pos_z = 0.0f;

float camera_x;
float camera_y;
float camera_z;

float look_x;
float look_y;
float look_z;

float turnLook_x = 0.0f;
float turnLook_y = 1.0f;
float turnLook_z = 1.2f;

float outLook_x = 0.0f;
float outLook_y = 1.7;
float outLook_z = -4.0f;

float angle = 0.0;

int view_mode = 4;

float cube_z = 0.0f;

float antenna_rot = 0.1f;

float Y_Speed = 0.3f;
float Y_Rot = 0.0f;

void initGL()
{
    glClearColor(0, 0, 1, 1);
    glClearDepth(1.0);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3, 3, -3, 3, -1000, 1000);
    glutPostRedisplay();
}

void GLSetup()
{
    glClearColor(0.0f, 0.9f, 1.0f, 1.0f);
    glViewport(0, 0, window_width, window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, window_width/window_height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void cylinder(float xc_pos, float yc_pos, float zc_pos)
{
    glPushMatrix();

    glTranslatef(xc_pos, yc_pos + 2.0, zc_pos);
                                                         //////////////////Need this extra translation to lock building in place?
                                                         //////////////////Will probably need extra z variable to account for movement in the z-axis
    float radius = 1.0, halfLength = 2.0;
    int slices = 20000;
    int i;
    for ( i = 0; i < slices; i++)
    {
        float theta = ((float)i) * 2.0 * 3.14;
        float nextTheta = ((float)i + 1) * 2.0 * 3.14;
        glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(0.0, halfLength, 0.0); /*vertex at middle of end */
        glVertex3f(radius * cos(theta), halfLength, radius * sin(theta));/*vertices at edges of circle*/
        glVertex3f(radius * cos(nextTheta), halfLength, radius * sin(nextTheta));
        /* the same vertices at the bottom of the cylinder*/
        glVertex3f(radius * cos(nextTheta), -halfLength, radius * sin(nextTheta));
        glVertex3f(radius * cos(theta), -halfLength, radius * sin(theta));
        glVertex3f(0.0, -halfLength, 0.0);
        glEnd();
    }
    glPopMatrix();
    glPushMatrix();

    // Rotate the calculated amount.
    glTranslatef(xc_pos, yc_pos + 5.0f, zc_pos);


    glRotatef(Y_Rot, 0.0f, 1.0f, 0.0f);
    // OK, let's start drawing our planer quads.
    glBegin(GL_QUADS);

    // Far face.  Red
    glNormal3f(0.0f, 0.0f, -1.0f);
    glColor4f(1.0, 0.0, 0.0, 1.0);

    glTexCoord2f(0.995f, 0.005f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(2.995f, 2.995f); glVertex3f(-1.0f, 1.0f, -1.0);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.005f, 0.005f); glVertex3f(1.0f, -1.0f, -1.0f);

    // Right face.  Blue
    glNormal3f(1.0f, 0.0f, 0.0f);
    glColor4f(0.0, 0.0, 1.0, 1.0);

    glTexCoord2f(0.995f, 0.005f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.995f, 0.995f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.005f, 0.005f); glVertex3f(1.0f, -1.0f, 1.0f);

    // Front face. Yellow  
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

    glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.995f, 0.005f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.995f, 0.995f); glVertex3f(1.0f, 1.0f, 1.0);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.0f, 1.0f, 1.0f);

    // Left Face.  Green
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glColor4f(0.0, 1.0, 0.0, 1.0);

    glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.995f, 0.005f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.995f, 0.995f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.0f, 1.0f, -1.0f);

    // Top Face Mixed
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor4f(1.0, 0.0, 0.0, 0.0);

    glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glColor4f(1.0, 0.0, 1.0, 0.66);
    glTexCoord2f(0.995f, 0.005f); glVertex3f(1.0f, 1.0f, -1.0f);
    glColor4f(0.0, 1.0, 1.0, 1.0);
    glTexCoord2f(0.995f, 0.995f); glVertex3f(1.0f, 1.0f, 1.0f);
    glColor4f(1.0, 1.0, 0.0, 0.33);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.0f, 1.0f, 1.0f);

    //Bottom Face Yellow
    glNormal3f(0.0f, -1.0f, 0.0f);
    glColor4f(0.9, 0.9, 0.2, 0.0);

    glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glColor4f(0.9, 0.9, 0.2, 0.66);
    glTexCoord2f(0.995f, 0.005f); glVertex3f(1.0f, -1.0f, -1.0f);
    glColor4f(0.9, 0.9, 0.2, 1.0);
    glTexCoord2f(0.995f, 0.995f); glVertex3f(1.0f, -1.0f, 1.0f);
    glColor4f(0.9, 0.9, 0.2, 0.33);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.0f, -1.0f, 1.0f);

    // All polygons have been drawn.
    glEnd();

    Y_Rot += Y_Speed;
    glPopMatrix();
}

void circle(float xci_pos, float yci_pos, float zci_pos)
{
    glPushMatrix();

    glTranslatef(xci_pos, yci_pos + 1.0, zci_pos);
    
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(1.0, 50, 50);


    glRotatef(Y_Rot, 0.0f, 1.0f, 0.0f);
    glTranslatef(-0.3f, 1.10f, 0.0f);
    glRotatef(20.0, 0.0f, 0.0f, 1.0f);

    float radius = 0.5, halfLength = 0.25;
    int slices = 20000;
    int i;
    for ( i = 0; i < slices; i++)
    {
        float theta = ((float)i) * 2.0 * 3.14;
        float nextTheta = ((float)i + 1) * 2.0 * 3.14;


        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, halfLength, 0.0); /*vertex at middle of end */
        glVertex3f(radius * cos(theta), halfLength, radius * sin(theta));/*vertices at edges of circle*/
        glVertex3f(radius * cos(nextTheta), halfLength, radius * sin(nextTheta));
        /* the same vertices at the bottom of the cylinder*/
        glVertex3f(radius * cos(nextTheta), -halfLength, radius * sin(nextTheta));
        glVertex3f(radius * cos(theta), -halfLength, radius * sin(theta));
        glVertex3f(0.0, -halfLength, 0.0);
        glEnd();
    }
    glPopMatrix();

    // Now let's do the motion calculations.
    Y_Rot += Y_Speed;
}

void square_building(float x_pos, float y_pos, float z_pos)
{
    glPushMatrix();

    // Move the object back from the screen.
    glTranslatef(x_pos, y_pos + 1.0, z_pos);

    // OK, let's start drawing our planer quads.
    glBegin(GL_QUADS);

    // Far face.  Red
    glNormal3f(0.0f, 0.0f, -1.0f);
    glColor4f(1.0, 0.0, 0.0, 1.0);

    glTexCoord2f(0.995f, 0.005f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(2.995f, 2.995f); glVertex3f(-1.0f, 2.0f, -1.0);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(1.0f, 2.0f, -1.0f);
    glTexCoord2f(0.005f, 0.005f); glVertex3f(1.0f, -1.0f, -1.0f);

    //Window Far Teal
    glNormal3f(0.0f, 0.0f, -1.0f);
    glColor4f(0.0, 1.0, 1.0, 1.0);

    glTexCoord2f(0.995f, 0.005f); glVertex3f(-0.60f, -0.75f, -1.01f);
    glTexCoord2f(2.995f, 2.995f); glVertex3f(-0.60f, 0.75f, -1.01);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(0.60f, 0.75f, -1.01f);
    glTexCoord2f(0.005f, 0.005f); glVertex3f(0.60f, -0.75f, -1.01f);

    // Right face.  Blue
    glNormal3f(1.0f, 0.0f, 0.0f);
    glColor4f(0.0, 0.0, 1.0, 1.0);

    glTexCoord2f(0.995f, 0.005f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.995f, 0.995f); glVertex3f(1.0f, 2.0f, -1.0f);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(1.0f, 2.0f, 1.0f);
    glTexCoord2f(0.005f, 0.005f); glVertex3f(1.0f, -1.0f, 1.0f);

    //Window Right Teal
    glNormal3f(1.0f, 0.0f, 0.0f);
    glColor4f(0.0, 1.0, 1.0, 1.0);

    glTexCoord2f(0.995f, 0.005f); glVertex3f(1.01f, 1.0f, -0.99f);
    glTexCoord2f(2.995f, 2.995f); glVertex3f(1.01f, 1.75f, -0.99f);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(1.01f, 1.75f, 0.99f);
    glTexCoord2f(0.005f, 0.005f); glVertex3f(1.01f, 1.0f, 0.99);

    // Front face. Yellow  
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

    glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.995f, 0.005f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.995f, 0.995f); glVertex3f(1.0f, 2.0f, 1.0);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.0f, 2.0f, 1.0f);

    //Window Front Teal
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor4f(0.0, 1.0, 1.0, 1.0);

    glTexCoord2f(0.995f, 0.005f); glVertex3f(-0.60f, -0.75f, 1.01f);
    glTexCoord2f(2.995f, 2.995f); glVertex3f(0.60f, -0.75f, 1.01f);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(0.60f, 0.75f, 1.01f);
    glTexCoord2f(0.005f, 0.005f); glVertex3f(-0.60f, 0.75f, 1.01f);

    // Left Face.  Green
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glColor4f(0.0, 1.0, 0.0, 1.0);

    glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.995f, 0.005f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.995f, 0.995f); glVertex3f(-1.0f, 2.0f, 1.0f);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.0f, 2.0f, -1.0f);

    //Window Left Teal
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glColor4f(0.0, 1.0, 1.0, 1.0);

    glTexCoord2f(0.995f, 0.005f); glVertex3f(-1.01f, 1.0f, -0.99f);
    glTexCoord2f(2.995f, 2.995f); glVertex3f(-1.01f, 1.0f, 0.99);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.01f, 1.75f, 0.99f);
    glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.01f, 1.75f, -0.99f);

    // Top Face Mixed
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor4f(1.0, 0.0, 0.0, 0.0);

    glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.0f, 2.0f, -1.0f);
    glColor4f(1.0, 0.0, 1.0, 0.66);
    glTexCoord2f(0.995f, 0.005f); glVertex3f(1.0f, 2.0f, -1.0f);
    glColor4f(0.0, 1.0, 1.0, 1.0);
    glTexCoord2f(0.995f, 0.995f); glVertex3f(1.0f, 2.0f, 1.0f);
    glColor4f(1.0, 1.0, 0.0, 0.33);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.0f, 2.0f, 1.0f);

    //Bottom Face Yellow
    glNormal3f(0.0f, -1.0f, 0.0f);
    glColor4f(0.9, 0.9, 0.2, 0.0);

    glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glColor4f(0.9, 0.9, 0.2, 0.66);
    glTexCoord2f(0.995f, 0.005f); glVertex3f(1.0f, -1.0f, -1.0f);
    glColor4f(0.9, 0.9, 0.2, 1.0);
    glTexCoord2f(0.995f, 0.995f); glVertex3f(1.0f, -1.0f, 1.0f);
    glColor4f(0.9, 0.9, 0.2, 0.33);
    glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.0f, -1.0f, 1.0f);

    // All polygons have been drawn.
    glEnd();

    glPopMatrix();
}

void xRoad(float zposition)
{
    glPushMatrix();
    glTranslatef(0, 0.01, 0);

    glBegin(GL_QUADS);

    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(-100, 0.0, zposition - 1.25);   //Back edge of road
    glVertex3f(-100, 0.0, zposition - 0.50);
    glVertex3f(100, 0.0, zposition - 0.50);
    glVertex3f(100, 0.0, zposition - 1.25);

    glColor3f(1.0, 0.75, 0.0);
    glVertex3f(-100, 0.01, zposition - 0.55);
    glVertex3f(-100, 0.01, zposition - 0.45);
    glVertex3f(100, 0.01, zposition - 0.45);
    glVertex3f(100, 0.01, zposition - 0.55);

    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(-100, 0.0, zposition - 0.50);  //front edge of road
    glVertex3f(-100, 0.0, zposition + 0.25);
    glVertex3f(100, 0.0, zposition + 0.25);
    glVertex3f(100, 0.0, zposition - 0.50);

    glEnd();

    glPopMatrix();

}

void zRoad(float xposition)
{
    glPushMatrix();
    glTranslatef(0, 0.001, 0);

    glBegin(GL_QUADS);

    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(xposition - 0.25, 0.0, -100);         //Left edge
    glVertex3f(xposition + 0.50, 0.0, -100);
    glVertex3f(xposition + 0.50, 0.0, 100);
    glVertex3f(xposition - 0.25, 0.0, 100);

    glColor3f(1.0, 0.75, 0.0);
    glVertex3f(xposition + 0.45, 0.01, -100);
    glVertex3f(xposition + 0.55, 0.01, -100);
    glVertex3f(xposition + 0.55, 0.01, 100);
    glVertex3f(xposition + 0.45, 0.01, 100);

    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(xposition + 0.50, 0.0, -100);      //Right edge
    glVertex3f(xposition + 1.25, 0.0, -100);
    glVertex3f(xposition + 1.25, 0.0, 100);
    glVertex3f(xposition + 0.50, 0.0, 100);

    glEnd();

    glPushMatrix();
}

void Road_all()
{
    glTranslatef(-0.45f, 0.0f, 0.45f);     //translates roads so that the middle line is at 0,0,0

    xRoad(0.0);                      //Roads in the x-axis

    xRoad(10.0);

    xRoad(20.0);

    xRoad(30.0);

    xRoad(40.0);

    xRoad(50.0);

    xRoad(60.0);

    xRoad(70.0);

    xRoad(80.0);

    xRoad(90.0); 

    xRoad(100.0); 

    xRoad(-10.0);

    xRoad(-20.0);

    xRoad(-30.0);

    xRoad(-40.0);

    xRoad(-50.0);

    xRoad(-60.0);

    xRoad(-70.0);

    xRoad(-80.0);

    xRoad(-90.0);

    xRoad(-100.0);

    zRoad(0.0);                     //Roads in the z-axis

    zRoad(10.0);

    zRoad(20.0);

    zRoad(30.0);

    zRoad(40.0);

    zRoad(50.0);

    zRoad(60.0);

    zRoad(70.0);

    zRoad(80.0);

    zRoad(90.0);

    zRoad(100.0);

    zRoad(-10.0);

    zRoad(-20.0);

    zRoad(-30.0);

    zRoad(-40.0);

    zRoad(-50.0);

    zRoad(-60.0);

    zRoad(-70.0);

    zRoad(-80.0);

    zRoad(-90.0);

    zRoad(-100.0);

}

void drawScene()
{
    //camera setup
    camera_x = pos_x + outLook_x;
    camera_y = pos_y + outLook_y + 1.0f;
    camera_z = pos_z + outLook_z + 0.5f;
    //look at point setup
    look_x = pos_x + turnLook_x;
    look_y = pos_y + turnLook_y;
    look_z = pos_z + turnLook_z;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLSetup();
    glClearColor(0.0f, 0.9f, 1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();
    gluLookAt(camera_x, camera_y, camera_z, look_x, look_y, look_z, 0.0f, 1.0f, 0.0f);
    glTranslatef(pos_x, pos_y, pos_z);
    glRotatef(angle, 0.0, 1.0, 0.0);
    drawCarBody();
    glPopMatrix();

    antenna_rot += 0.1f;
////Circles
        glLoadIdentity();
        gluLookAt(camera_x, camera_y, camera_z, look_x, look_y, look_z, 0.0f, 1.0f, 0.0f);
        circle(5.0f, 0.0f, -5.0f);
       
        circle(25.0f, 0.0f, 5.0f);
      
        circle(-45.0f, 0.0f, -5.0f);

        circle(35.0f, 0.0f, 15.0f);

    ////Squares
        square_building(3.0f, 0.0f, -8.0f);

        square_building(8.0f, 0.0f, -13.0f);

        square_building(8.0f, 0.0f, 23.0f);

        square_building(3.0f, 0.0f, 48.0f);

        square_building(-18.0f, 0.0f, 3.0f);

        square_building(-3.0f, 0.0f, -8.0f);

        square_building(-3.0f, 0.0f, -28.0f);

        square_building(-8.0f, 0.0f, -63.0f);

        square_building(8.0f, 0.0f, 3.0f);

        square_building(3.0f, 0.0f, 8.0f);
    
    ///Cylinders

        cylinder(3.0f, 0.0f, -3.0f);

        cylinder(-3.0f, 0.0f, 13.0f);
      
        cylinder(-28.0f, 0.0f, -8.0f);
     
        cylinder(33.0f, 0.0f, 3.0f);           
    

    glLoadIdentity();               ////////////////////////Road function that draws all roads 
    gluLookAt(camera_x, camera_y, camera_z, look_x, look_y, look_z, 0.0f, 1.0f, 0.0f);
    Road_all();
    
    glLoadIdentity();
    gluLookAt(camera_x, camera_y, camera_z, look_x, look_y, look_z, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glPushMatrix();
    glTranslatef(0.0, -0.01, 0.0);
    glColor3f(0.1, 0.4, 0);
    glVertex3f(-100, 0.0, -100);
    glVertex3f(-100, 0.0, 100);         //a green surroundings
    glVertex3f(100, 0.0, 100);
    glVertex3f(100, 0.0, -100);
    glPopMatrix();
    glEnd();
    
    glutSwapBuffers();
}

void drawCarBody()
{
    
    glTranslatef(0.0f, 0.15f, 0.0f);     ///////////////////////added translation because the tires passed
                                         //////////////////////throught the road at y = 0.0
    
    //********************************main body**************************
    glBegin(GL_QUADS);
    //front
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5, 0, 1);
    glVertex3f(-0.5, 0.7, 1);
    glVertex3f(0.5, 0.7, 1);
    glVertex3f(0.5, 0, 1);
    //back
    glVertex3f(-0.5, 0, -1);
    glVertex3f(-0.5, 0.7, -1);
    glVertex3f(0.5, 0.7, -1);
    glVertex3f(0.5, 0, -1);
    //right side
    glColor3f(0.2, 0.2, 0.3);
    glVertex3f(-0.5, 0, -1);
    glVertex3f(-0.5, 0.7, -1);
    glVertex3f(-0.5, 0.7, 1);
    glVertex3f(-0.5, 0, 1);
    //left side
    glColor3f(0.2, 0.2, 0.3);
    glVertex3f(0.5, 0, -1);
    glVertex3f(0.5, 0.7, -1);
    glVertex3f(0.5, 0.7, 1);
    glVertex3f(0.5, 0, 1);
    //bottom side
    glColor3f(0.2, 0.2, 1.0);
    glVertex3f(-0.5, 0, -1);
    glVertex3f(-0.5, 0, 1);
    glVertex3f(0.5, 0, 1);
    glVertex3f(0.5, 0, -1);
    //top side
    glColor3f(0.2, 0.2, 1.0);
    glVertex3f(-0.5, 0.7, -1);
    glVertex3f(-0.5, 0.7, 1);
    glVertex3f(0.5, 0.7, 1);
    glVertex3f(0.5, 0.7, -1);
    //*******************************cabin***********************************
    //top face
    glColor3f(0.3, 0.4, 0);
    glVertex3f(-0.5, 1.2, 0.7);
    glVertex3f(-0.5, 1.2, 0.1);
    glVertex3f(0.5, 1.2, 0.1);
    glVertex3f(0.5, 1.2, 0.7);

    //front window:
    //left side window
    glVertex3f(-0.5, 1.2, 0.7);
    glVertex3f(-0.5, 0.7, 1);
    glVertex3f(-0.4, 0.7, 1);
    glVertex3f(-0.4, 1.2, 0.7);
    //right side window
    glVertex3f(0.5, 1.2, 0.7);
    glVertex3f(0.5, 0.7, 1);
    glVertex3f(0.4, 0.7, 1);
    glVertex3f(0.4, 1.2, 0.7);
    //top side window
    glVertex3f(-0.5, 1.2, 0.7);
    glVertex3f(-0.5, 1.15, 0.73);
    glVertex3f(0.5, 1.15, 0.73);
    glVertex3f(0.5, 1.2, 0.7);
    //bottom side window
    glVertex3f(-0.5, 0.75, 0.97);
    glVertex3f(-0.5, 0.7, 1);
    glVertex3f(0.5, 0.7, 1);
    glVertex3f(0.5, 0.75, 0.97);

    //back window:
    glColor3f(0.0, 0.0, 0.6);
    //left side window
    glVertex3f(-0.5, 1.2, 0.1);
    glVertex3f(-0.5, 0.7, -0.2);
    glVertex3f(-0.4, 0.7, -0.2);
    glVertex3f(-0.4, 1.2, 0.1);
    //right side window
    glVertex3f(0.5, 1.2, 0.1);
    glVertex3f(0.5, 0.7, -0.2);
    glVertex3f(0.4, 0.7, -0.2);
    glVertex3f(0.4, 1.2, 0.1);
    //top side window
    glVertex3f(-0.5, 1.2, 0.1);
    glVertex3f(-0.5, 1.15, 0.07);
    glVertex3f(0.5, 1.15, 0.07);
    glVertex3f(0.5, 1.2, 0.1);
    //bottom side window
    glVertex3f(-0.5, 0.7, -0.23);
    glVertex3f(-0.5, 0.75, -0.2);
    glVertex3f(0.5, 0.75, -0.2);
    glVertex3f(0.5, 0.7, -0.23);

    //right window:
    //bottom side window
    glColor3f(0.3, 0.4, 0);
    glVertex3f(-0.5, 0.7, 0.1);
    glVertex3f(-0.5, 0.78, 0.1);
    glVertex3f(-0.5, 0.78, 0.7);
    glVertex3f(-0.5, 0.7, 0.7);
    //top side window
    glVertex3f(-0.5, 1.12, 0.1);
    glVertex3f(-0.5, 1.2, 0.1);
    glVertex3f(-0.5, 1.2, 0.7);
    glVertex3f(-0.5, 1.12, 0.7);

    //left window:
    //bottom side window
    glVertex3f(0.5, 0.7, 0.1);
    glVertex3f(0.5, 0.78, 0.1);
    glVertex3f(0.5, 0.78, 0.7);
    glVertex3f(0.5, 0.7, 0.7);
    //top side window
    glVertex3f(0.5, 1.12, 0.1);
    glVertex3f(0.5, 1.2, 0.1);
    glVertex3f(0.5, 1.2, 0.7);
    glVertex3f(0.5, 1.12, 0.7);

    //**************************body features******************************
    //license plate
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-0.25, 0.2, -1.01);
    glVertex3f(-0.25, 0.4, -1.01);
    glVertex3f(0.25, 0.4, -1.01);
    glVertex3f(0.25, 0.2, -1.01);

    //grill
    glColor3f(0.4, 0.4, 0.4);
    glVertex3f(-0.25, 0.15, 1.01);
    glVertex3f(-0.25, 0.35, 1.01);
    glVertex3f(0.25, 0.35, 1.01);
    glVertex3f(0.25, 0.15, 1.01);

    //grill lines:
    //line 1:
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-0.25, 0.15, 1.01);
    glVertex3f(-0.25, 0.35, 1.01);
    glVertex3f(-0.22, 0.35, 1.01);
    glVertex3f(-0.22, 0.15, 1.01);
    //line 2
    glVertex3f(-0.16, 0.15, 1.01);
    glVertex3f(-0.16, 0.35, 1.01);
    glVertex3f(-0.13, 0.35, 1.01);
    glVertex3f(-0.13, 0.15, 1.01);
    //line 3
    glVertex3f(-0.06, 0.15, 1.01);
    glVertex3f(-0.06, 0.35, 1.01);
    glVertex3f(-0.03, 0.35, 1.01);
    glVertex3f(-0.03, 0.15, 1.01);
    //line 4
    glVertex3f(0.03, 0.15, 1.01);
    glVertex3f(0.03, 0.35, 1.01);
    glVertex3f(0.06, 0.35, 1.01);
    glVertex3f(0.06, 0.15, 1.01);
    //line 5
    glVertex3f(0.13, 0.15, 1.01);
    glVertex3f(0.13, 0.35, 1.01);
    glVertex3f(0.16, 0.35, 1.01);
    glVertex3f(0.16, 0.15, 1.01);
    //line 6
    glVertex3f(0.22, 0.15, 1.01);
    glVertex3f(0.22, 0.35, 1.01);
    glVertex3f(0.25, 0.35, 1.01);
    glVertex3f(0.25, 0.15, 1.01);

    glEnd();

    //***************************side windows***************************
    glBegin(GL_TRIANGLES);
    //right window:
    //left side window
    glColor3f(0.3, 0.4, 0);
    glVertex3f(-0.5, 1.2, 0.1);
    glVertex3f(-0.5, 0.7, -0.2);
    glVertex3f(-0.5, 0.7, 0.1);
    //right side window
    glVertex3f(-0.5, 0.7, 0.7);
    glVertex3f(-0.5, 1.2, 0.7);
    glVertex3f(-0.5, 0.7, 1);

    //left window:
    //left side window
    glVertex3f(0.5, 1.2, 0.1);
    glVertex3f(0.5, 0.7, -0.2);
    glVertex3f(0.5, 0.7, 0.1);
    //right side window
    glVertex3f(0.5, 0.7, 0.7);
    glVertex3f(0.5, 1.2, 0.7);
    glVertex3f(0.5, 0.7, 1);

    glEnd();

    //*****************************lights************************
    //left front
    glColor3f(0.95, 0.95, 0.4);
    glTranslatef(-0.35, 0.5, 1.0);
    glutSolidSphere(0.1, 15, 15);
    //right front
    glTranslatef(0.7, 0.0, 0.0);
    glutSolidSphere(0.1, 15, 15);
    //left back
    glTranslatef(0.0, 0.0 , -2.0);
    glutSolidSphere(0.1, 15, 15);
    //right back
    glTranslatef(-0.7, 0.0, 0.0);
    glutSolidSphere(0.1, 15, 15);

    //*********************antenna****************************
    glTranslatef(0.35, 0.2, 0.3);
    glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
    glColor3f(0.5, 0.5, 0.5);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 0.05f, 0.05f, 0.8f, 10.0, 10.0);
    glRotatef(90.0, 1.0f, 0.0f, 0.0f);

    glTranslatef(0.0, 0.8, 0.0);
    glRotatef(antenna_rot, 0.0, 1.0, 0.0);

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.6, 0.0);
    glVertex3f(-0.4, 0, 0.0);
    glVertex3f(0.0, 0.6, 0.0);
    glVertex3f(0.4, 0, 0.0);
    glEnd();

    glRotatef(-antenna_rot, 0.0, 1.0, 0.0);

    //****************************wheels**************************
    glColor3f(0.3, 0.3, 0.3);
    glRotatef(90.0, 0.0, 0.1, 0.0);
    glTranslatef(-0.1, -1.5, 0.6);
    glutSolidTorus(0.1, 0.1, 50, 50);

    glTranslatef(-1.1, 0.0, 0.0);
    glutSolidTorus(0.1, 0.1, 50, 50);

    glTranslatef(0.0, 0.0, -1.2);
    glutSolidTorus(0.1, 0.1, 50, 50);

    glTranslatef(1.1, 0.0, 0.0);
    glutSolidTorus(0.1, 0.1, 50, 50);
    
    //**************************rocket launchers********************
    glColor3f(0.0, 1.0, 0.0);
    glTranslatef(-1.3, 0.53, 0.0);
    glRotatef(90.0, 0.0f, 1.0f, 0.0f);
    GLUquadricObj *obj2 = gluNewQuadric();
    gluCylinder(obj2, 0.08f, 0.08f, 0.2f, 10.0, 10.0);

    glTranslatef(-1.2, 0.0, 0.0);
    GLUquadricObj *obj3 = gluNewQuadric();
    gluCylinder(obj3, 0.08f, 0.08f, 0.2f, 10.0, 10.0);
}

void myControlKey(unsigned char key, int x, int y)
{
    if(!paused)
    {


   if (key == 'a')
    {
        if(pos_z<99 && pos_z>-99 && pos_x<99 && pos_x>-99)
        {
          if(angle == 0.0)
            pos_z += 1.0f;
        else if (angle == 180.0 || angle == -180.0)
            pos_z -= 1.0f;
        else if (angle >= 90.0)
            pos_x += 1.0f;
        else if (angle <= -90.0)
            pos_x -= 1.0f;
        }
        else
        {

        }

    }
    if(key == 'z')
    {
        if(pos_z>-99&& pos_z<99 && pos_x<99 && pos_x>-99)
        {
            if(angle == 0.0)
            pos_z -= 1.0f;
        else if (angle == 180.0 || angle == -180.0)
            pos_z += 1.0f;
        else if (angle >= 90.0)
            pos_x -= 1.0f;
        else if (angle <= -90.0)
            pos_x += 1.0f;
        }

    }
    if(key == 'q' && (pos_x == 0 || pos_x == 10 || pos_x == -10 || pos_x == 20 || pos_x == -20
        || pos_x == 30 || pos_x == -30 || pos_x == 40 || pos_x == -40 || pos_x == 50 || pos_x == -50
        || pos_x == 60 || pos_x == -60 || pos_x == 70 || pos_x == -70 || pos_x == 80 || pos_x == -80 
        || pos_x == 90 || pos_x == -90 || pos_x == 100 || pos_x == -100)
        && (pos_z == 0 || pos_z == 10 || pos_z == -10 || pos_z == 20 || pos_z == -20
            || pos_z == 30 || pos_z == -30 || pos_z == 40 || pos_z == -40 || pos_z == 50 || pos_z == -50
            || pos_z == 60 || pos_z == -60 || pos_z == 70 || pos_z == -70 || pos_z == 80|| pos_z == -80 
            || pos_z == 90 || pos_z == -90 || pos_z == 100 || pos_z == -100) )
    {
        if(angle == 0.0)
        {
            angle = 90.0;
        }
        else if(angle == 90.0)
        {
            angle = 180.0;
        }
        else if(angle == 180.0)
        {
            angle = -90.0;
        }
        else if(angle == -90.0)
        {
            angle = 0.0;
        }
        changeView();
    }
    if(key == 'w' && (pos_x == 0 || pos_x == 10 || pos_x == -10 || pos_x == 20 || pos_x == -20
        || pos_x == 30 || pos_x == -30 || pos_x == 40 || pos_x == -40 || pos_x == 50 || pos_x == -50
        || pos_x == 60 || pos_x == -60 || pos_x == 70 || pos_x == -70 || pos_x == 80 || pos_x == -80 
        || pos_x == 90 || pos_x == -90 || pos_x == 100 || pos_x == -100)
        && (pos_z == 0 || pos_z == 10 || pos_z == -10 || pos_z == 20 || pos_z == -20
            || pos_z == 30 || pos_z == -30 || pos_z == 40 || pos_z == -40 || pos_z == 50 || pos_z == -50
            || pos_z == 60 || pos_z == -60 || pos_z == 70 || pos_z == -70 || pos_z == 80|| pos_z == -80 
            || pos_z == 90 || pos_z == -90 || pos_z == 100 || pos_z == -100) )
    {
        if(angle == 0.0)
        {
            angle = -90.0;
        }
        else if(angle == -90.0)
        {
            angle = -180.0;
        }
        else if(angle == -180.0)
        {
            angle = 90.0;
        }
        else if(angle == 90.0)
        {
            angle = 0.0;
        }
        changeView();
    }
     if ((key == 'r' && pos_z ==99) || (key == 'r' && pos_x ==99) ||(key == 'r' && pos_z ==-99) || (key == 'r' && pos_x ==-99) )
    {
        pos_x=0;
        pos_z=0;
    }
    }
    if (key == 'p')
    {
        paused = !paused;

    }

}

void myViewKey(unsigned char key, int x, int y)
{
    if(key == GLUT_KEY_F1)
    {
        view_mode = 1;
        changeView();
    }
    if(key == GLUT_KEY_F2)
    {
        view_mode = 2;
        changeView();
    }
    if(key == GLUT_KEY_F3)
    {
        view_mode = 3;
        changeView();
    }
    if(key == GLUT_KEY_F4)
    {
        view_mode = 4;
        changeView();
    }
    if(key == GLUT_KEY_F5)
    {
        view_mode = 5;
        changeView();
    }
    if(key == GLUT_KEY_F9)
    {
        view_mode = 9;
        changeView();
    }
    if(key == GLUT_KEY_F6)
    {
        view_mode = 6;
        changeView();
    }
    if(key == GLUT_KEY_F10)
    {
        view_mode = 10;
        changeView();
    }
    if(key == GLUT_KEY_F7)
    {
        view_mode = 7;
        changeView();
    }
    if(key == GLUT_KEY_F11)
    {
        view_mode = 11;
        changeView();
    }
    if(key == GLUT_KEY_F8)
    {
        view_mode = 8;
        changeView();
    }
    if(key == GLUT_KEY_F12)
    {
        view_mode = 12;
        changeView();
    }
}

void changeView()
{
        if(angle == 90.0)
        {
            if(view_mode == 1)
            {
                turnLook_x = 1.2f; turnLook_y = 1.0f; turnLook_z = 0.0f; outLook_x = 0.5f; outLook_y = 0.0f; outLook_z = -0.5f;
            }
            if(view_mode == 2)
            {
                turnLook_x = 0.0f; turnLook_y = 1.0f; turnLook_z = -46.2f; outLook_x = 0.5f; outLook_y = 0.0f; outLook_z = -0.5f;
            }
            if(view_mode == 3)
            {
                turnLook_x = 0.0f; turnLook_y = 1.0f; turnLook_z = 43.8f; outLook_x = 0.5f; outLook_y = 0.0f; outLook_z = -0.5f;
            }
            if(view_mode == 4)
            {
                turnLook_x = 1.0f; turnLook_y = 1.4f; turnLook_z = 0.0f; outLook_x = -3.5f; outLook_y = 1.7f; outLook_z = -0.5f;
            }
            if(view_mode == 5)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -4.5f; outLook_y = 2.5f; outLook_z = 3.5f;
            }
            if(view_mode == 6)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 5.5f; outLook_y = 2.5f; outLook_z = 3.5f;
            }
            if(view_mode == 7)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 5.5f; outLook_y = 2.5f; outLook_z = -4.5f;
            }
            if(view_mode == 8)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -4.5f; outLook_y = 2.5f; outLook_z = -4.5f;
            }
            if(view_mode == 9)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -6.5f; outLook_y = 4.5f; outLook_z = 5.5f;
            }
            if(view_mode == 10)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 7.5f; outLook_y = 4.5f; outLook_z = 5.5f;
            }
            if(view_mode == 11)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 7.5f; outLook_y = 4.5f; outLook_z = -6.5f;
            }
            if(view_mode == 12)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -6.5f; outLook_y = 4.5f; outLook_z = -6.5f;
            }
        }
        else if(angle == 180.0)
        {
            if(view_mode == 1)
            {
                turnLook_x = 0.0f; turnLook_y = 1.0f; turnLook_z = -1.2f; outLook_x = 0.0f; outLook_y = 0.0f; outLook_z = -1.0f;
            }
            if(view_mode == 2)
            {
                turnLook_x = -45.0f; turnLook_y = 1.0f; turnLook_z = -1.2f; outLook_x = 0.0f; outLook_y = 0.0f; outLook_z = -1.0f;
            }
            if(view_mode == 3)
            {
                turnLook_x = 45.0f; turnLook_y = 1.0f; turnLook_z = 1.2f; outLook_x = 0.0f; outLook_y = 0.0f; outLook_z = -1.0f;
            }
            if(view_mode == 4)
            {
                turnLook_x = 0.0f; turnLook_y = 1.4f; turnLook_z = -1.2f; outLook_x = 0.0f; outLook_y = 1.7f; outLook_z = 3.0f;
            }
            if(view_mode == 5)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 4.0f; outLook_y = 2.5f; outLook_z = 4.0f;
            }
            if(view_mode == 6)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 4.0f; outLook_y = 2.5f; outLook_z = -6.0f;
            }
            if(view_mode == 7)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -4.0f; outLook_y = 2.5f; outLook_z = -6.0f;
            }
            if(view_mode == 8)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -4.0f; outLook_y = 2.5f; outLook_z = 4.0f;
            }
            if(view_mode == 9)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 6.0f; outLook_y = 4.5f; outLook_z = 6.0f;
            }
            if(view_mode == 10)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 6.0f; outLook_y = 4.5f; outLook_z = -8.0f;
            }
            if(view_mode == 11)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -6.0f; outLook_y = 4.5f; outLook_z = -8.0f;
            }
            if(view_mode == 12)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -6.0f; outLook_y = 4.5f; outLook_z = 6.0f;
            }
        }
        else if(angle == -90.0)
        {
            if(view_mode == 1)
            {
                turnLook_x = -1.2f; turnLook_y = 1.0f; turnLook_z = 0.0f; outLook_x = -0.5f; outLook_y = 0.0f; outLook_z = -0.5f;
            }
            if(view_mode == 2)
            {
                turnLook_x = 0.0f; turnLook_y = 1.0f; turnLook_z = 43.8f; outLook_x = -0.5f; outLook_y = 0.0f; outLook_z = -0.5f;
            }
            if(view_mode == 3)
            {
                turnLook_x = 0.0f; turnLook_y = 1.0f; turnLook_z = -46.2f; outLook_x = -0.5f; outLook_y = 0.0f; outLook_z = -0.5f;
            }
            if(view_mode == 4)
            {
                turnLook_x = -1.0f; turnLook_y = 1.4f; turnLook_z = 0.0f; outLook_x =  3.5f; outLook_y = 1.7f; outLook_z = -0.5f;
            }
            if(view_mode == 5)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 4.5f; outLook_y = 2.5f; outLook_z = -4.5f;
            }
            if(view_mode == 6)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -5.5f; outLook_y = 2.5f; outLook_z = -4.5f;
            }
            if(view_mode == 7)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -5.5f; outLook_y = 2.5f; outLook_z = 3.5f;
            }
            if(view_mode == 8)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 4.5f; outLook_y = 2.5f; outLook_z = 3.5f;
            }
            if(view_mode == 9)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 6.5f; outLook_y = 4.5f; outLook_z = -6.5f;
            }
            if(view_mode == 10)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -7.5f; outLook_y = 4.5f; outLook_z = -6.5f;
            }
            if(view_mode == 11)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -7.5f; outLook_y = 4.5f; outLook_z = 5.5f;
            }
            if(view_mode == 12)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 6.5f; outLook_y = 4.5f; outLook_z = 5.5f;
            }
        }
        else if(angle == 0.0)
        {
            if(view_mode == 1)
            {
                turnLook_x = 0.0f; turnLook_y = 1.0f; turnLook_z = 1.2f; outLook_x = 0.0f; outLook_y = 0.0f; outLook_z = 0.0f;
            }
            if(view_mode == 2)
            {
                turnLook_x = 45.0f; turnLook_y = 1.0f; turnLook_z = 1.2f; outLook_x = 0.0f; outLook_y = 0.0f; outLook_z = 0.0f;
            }
            if(view_mode == 3)
            {
                turnLook_x = -45.0f; turnLook_y = 1.0f; turnLook_z = 1.2f; outLook_x = 0.0f; outLook_y = 0.0f; outLook_z = 0.0f;
            }
            if(view_mode == 4)
            {
                turnLook_x = 0.0f; turnLook_y = 1.4f; turnLook_z = 1.2f; outLook_x = 0.0f; outLook_y = 1.7f; outLook_z = -4.0f;
            }
            if(view_mode == 5)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -4.0f; outLook_y = 2.5f; outLook_z = -5.0f;
            }
            if(view_mode == 6)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -4.0f; outLook_y = 2.5f; outLook_z = 5.0f;
            }
            if(view_mode == 7)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 4.0f; outLook_y = 2.5f; outLook_z = 5.0f;
            }
            if(view_mode == 8)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 4.0f; outLook_y = 2.5f; outLook_z = -5.0f;
            }
            if(view_mode == 9)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -6.0f; outLook_y = 4.5f; outLook_z = -7.0f;
            }
            if(view_mode == 10)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -6.0f; outLook_y = 4.5f; outLook_z = 7.0f;
            }
            if(view_mode == 11)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 6.0f; outLook_y = 4.5f; outLook_z = 7.0f;
            }
            if(view_mode == 12)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 6.0f; outLook_y = 4.5f; outLook_z = -7.0f;
            }
        }
        else if(angle == -180.0)
        {
            if(view_mode == 1)
            {
                turnLook_x = 0.0f; turnLook_y = 1.0f; turnLook_z = -1.2f; outLook_x = 0.0f; outLook_y = 0.0f; outLook_z = -1.0f;
            }
            if(view_mode == 2)
            {
                turnLook_x = -45.0f; turnLook_y = 1.0f; turnLook_z = -1.2f; outLook_x = 0.0f; outLook_y = 0.0f; outLook_z = -1.0f;
            }
            if(view_mode == 3)
            {
                turnLook_x = 45.0f; turnLook_y = 1.0f; turnLook_z = 1.2f; outLook_x = 0.0f; outLook_y = 0.0f; outLook_z = -1.0f;
            }
            if(view_mode == 4)
            {
                turnLook_x = 0.0f; turnLook_y = 1.4f; turnLook_z = -1.2f; outLook_x = 0.0f; outLook_y = 1.7f; outLook_z = 3.0f;
            }
            if(view_mode == 5)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 4.0f; outLook_y = 2.5f; outLook_z = 4.0f;
            }
            if(view_mode == 6)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 4.0f; outLook_y = 2.5f; outLook_z = -6.0f;
            }
            if(view_mode == 7)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -4.0f; outLook_y = 2.5f; outLook_z = -6.0f;
            }
            if(view_mode == 8)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -4.0f; outLook_y = 2.5f; outLook_z = 4.0f;
            }
            if(view_mode == 9)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 6.0f; outLook_y = 4.5f; outLook_z = 6.0f;
            }
            if(view_mode == 10)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = 6.0f; outLook_y = 4.5f; outLook_z = -8.0f;
            }
            if(view_mode == 11)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f; turnLook_z = 0.0f; outLook_x = -6.0f; outLook_y = 4.5f; outLook_z = -8.0f;
            }
            if(view_mode == 12)
            {
                turnLook_x = 0.0f; turnLook_y = 0.8f;turnLook_z = 0.0f; outLook_x = -6.0f; outLook_y = 4.5f; outLook_z = 6.0f;
            }
        }
}

void resizeScene(int width, int height)
{
    if (height == 0)
        height = 1;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

    window_width = width;
    window_height = height;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(window_width,window_height);
    glutCreateWindow("THE BATTLE HUMMER");
    printf("Controls and camera settings -\n");
    printf("'a' - Move forward\n");
    printf("'z' - Move Backwards\n");
    printf("'q' - turn Left\n");
    printf("'w' - turn Right\n");
    printf("'r' - return to starting position\n");
    printf("USE F1 - F12 for different Camera settings\n");
    printf("Enjoy the game");
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutReshapeFunc(resizeScene);
    // glutMouseFunc(myControlMouse);
    glutKeyboardFunc(myControlKey);
    glutSpecialFunc(myViewKey);
    initGL();
    glutMainLoop();
    return 0;
}
