////////Functions to draw all buildings
#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>
#include <string.h>  // For spring operations.

#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h

//Put these files above the drawing function then call each function or building like
//cylinder(0.0, 0.0, 0.0); in the drawing function

void cylinder(float xc_pos, float yc_pos, float zc_pos)
{
    glPushMatrix();

    glTranslatef(xc_pos, yc_pos + 2.0, zc_pos);
    glTranslatef(xw, 0, 0);                              //////////////////Need this extra translation to lock building in place?
                                                         //////////////////Will probably need extra z variable to account for movement in the z-axis
    float radius = 1.0, halfLength = 2.0;
    int slices = 20000;
    for (int i = 0; i < slices; i++)
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

    glTranslatef(xw, 0, 0);                              //////////////////Need this extra translation to lock building in place?
                                                         //////////////////Will probably need extra z variable to account for movement in the z-axis

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
    glTranslatef(xw, 0, 0);                           //////////////////Need this extra translation to lock building in place?
                                                      //////////////////Will probably need extra z variable to account for movement in the z-axis

    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(1.0, 50, 50);


    glRotatef(Y_Rot, 0.0f, 1.0f, 0.0f);
    glTranslatef(-0.3f, 1.10f, 0.0f);
    glRotatef(20.0, 0.0f, 0.0f, 1.0f);

    float radius = 0.5, halfLength = 0.25;
    int slices = 20000;
    for (int i = 0; i < slices; i++)
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
    glTranslatef(xw, 0, 0);                              //////////////////Need this extra translation to lock building in place?
                                                         //////////////////Will probably need extra z variable to account for movement in the z-axis
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
