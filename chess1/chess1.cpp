// chess1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "board.h"
#include "../gl/glut.h"
#include "vkgllib.h"
#include <time.h>
//#include <Windows.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_POS_X 50
#define WINDOW_POS_Y 50

Board board;

float angle1 = 0.0f;				// camera angle 
float radians = 0.0f;			   // camera angle in radians

int mouseX, mouseY;						// mouse coordinates
float cameraX, cameraY, cameraZ;	   // camera coordinates
float lookX, lookY, lookZ;			   // camera look-at coordinates

int icameracycle = 0;
int imvcamera = 0;
int spot_flag = 1;

float camerapos[3][3] = {
    25, 40, 0,
    -25, 40, 0,
    0, 40, 25
};

void lightset();


int initial_time = time(NULL), final_time, frame_count = 0;

void timer(int v)
{
    glutTimerFunc(1000 / 60, timer, v);
}

void initialize()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// clear to black

    glShadeModel(GL_SMOOTH);					   // use smooth shading
    glEnable(GL_DEPTH_TEST);					   // hidden surface removal
    glEnable(GL_CULL_FACE);						   // do not calculate inside of poly's
    glFrontFace(GL_CCW);						      // counter clock-wise polygons are out

    glEnable(GL_TEXTURE_2D);					   // enable 2D texturing
    board.InitializePieces();

    lightset();
}

void lightset()
{
    //glEnable(GL_DEPTH_TEST);

//Spot Light
    if (spot_flag == 1)
    {
        //glDisable(GL_LIGHT0);
        GLfloat diffusePoint[] = { 1, 1, 1, 0.0 };
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffusePoint);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0); // a cutoff angle of 30
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 4.0); // ε = 4.0
        GLfloat dir[] = { 0.0, 0.0, 0.0 }; // the spotlight’s direction
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
        glEnable(GL_LIGHT0);


        /*GLfloat position[] = {0.0, 0.0, 0.0, 1.0};
        GLfloat diffusePoint[] = {1, 1, 1, 1.0};
                glLightfv(GL_LIGHT2, GL_DIFFUSE, diffusePoint);
                glLightfv(GL_LIGHT2, GL_POSITION, position);
            glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0); // a cutoff angle of 30
            //glLightf(GL_LIGHT2,GL_SPOT_EXPONENT, 4.0); // ε = 4.0
            GLfloat dir[] = {1.0, 0.0, 0.0}; // the spotlight’s direction
            glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION, dir);
            glEnable(GL_LIGHT2);*/
    }

}

void displayFunction()
{

    //Render();
    radians = float(PI * (angle1 - 90.0f) / 180.0f);

    // calculate the camera's position
    cameraX = 20 * sin(radians); // multiplying by mouseY makes the
    cameraZ = 20 * cos(radians); // camera get closer/farther away with mouseY
    cameraY = 5 + mouseY / 32; //

    // calculate the camera look-at coordinates as the center of the terrain map
    lookX = (MAP_X * MAP_SCALE) / 2.0f;
    lookY = 25.0f;
    lookZ = -(MAP_Z * MAP_SCALE) / 2.0f;

    // clear screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // set the camera position
    gluLookAt(cameraX, cameraY, cameraZ, lookX - lookX, lookY - lookY, lookZ - lookZ, 0.0, 1.0, 0.0);
    //gluLookAt(cameraX, 0.001, 0, lookX - lookX, lookY - lookY, lookZ - lookZ, 0.0, 1.0, 0.0);
    //gluLookAt(0.001, cameraY,  0, lookX - lookX, lookY - lookY, lookZ - lookZ, 0.0, 1.0, 0.0);
    board.Draw();

    // enable blending
    glEnable(GL_BLEND);

    // enable read-only depth buffer
    glDepthMask(GL_FALSE);

    // set the blend function to what we use for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // set back to normal depth buffer mode (writable)
    glDepthMask(GL_TRUE);

    // disable blending
    glDisable(GL_BLEND);

    glFlush();
    //SwapBuffers(g_HDC);			// bring backbuffer to foreground

    glutSwapBuffers();

    glutPostRedisplay();


    frame_count++;
    final_time = time(NULL);
    if (final_time - initial_time > 0)
    {

        cout << "Frame : " << frame_count / (final_time - initial_time) << endl;
        // printf("Frame %d\n", frame_count);

        frame_count = 0;
        initial_time = final_time;
    }

}


void reshapeFunction(int width, int height)
{

    if (height == 0)					         // don't want a divide by zero
    {
        height = 1;
    }

    glViewport(0, 0, width, height);	   // reset the viewport to new dimensions
    glMatrixMode(GL_PROJECTION);		   // set projection matrix current matrix
    glLoadIdentity();					      // reset projection matrix

    // calculate aspect ratio of window
    //gluPerspective(54.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);
    gluPerspective(50.0f, (GLfloat)width / (GLfloat)height, .10f, 160.0f);

    glMatrixMode(GL_MODELVIEW);			// set modelview matrix
    glLoadIdentity();					      // reset modelview matrix

}

void keyFunction(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        /* Exit program on Escape */
        exit(0);
        break;
    case 32:
        board.setMoveEnable();
        std::cout << "Backspace key is pressed.\n";

        break;
    case 'W' | 'w':
        if (imvcamera)
            mouseY += 10;

        break;
    case 'A' | 'a':
        if (imvcamera)
            angle1 -= 3.0f;
        break;
    case 'S' | 's':
        if (imvcamera)
            mouseY -= 10;
        break;
    case 'D' | 'd':
        if (imvcamera)
            angle1 += 3.0f;
        break;
    case 9:
        imvcamera = imvcamera ? 0 : 1;
        break;

    }


}

void catchKey(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT) {
        printf("Left key is pressed\n");
        icameracycle--;
        if (icameracycle < 0)
            icameracycle = 2;
        icameracycle %= 3;
    }
    else if (key == GLUT_KEY_RIGHT) {
        printf("Right key is pressed\n");
        icameracycle++;
        icameracycle %= 3;
    }
    else if (key == GLUT_KEY_DOWN)
        printf("Down key is pressed\n");
    else if (key == GLUT_KEY_UP)
        printf("Up key is pressed\n");

}

int oldMouseX, oldMouseY;
int mousecnt = 0;
void mouseFunction(int button, int state, int x, int y)
{
    //The button parameter is one of GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON.
    //The state parameter is either GLUT_UP or GLUT_DOWN 

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mousecnt++;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        mousecnt--;

    }


}
void motionFunction(int x, int y)
{
    //The button parameter is one of GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON.
    //The state parameter is either GLUT_UP or GLUT_DOWN 
    oldMouseX = mouseX;
    oldMouseY = mouseY;

    // get mouse coordinates from Windows
    mouseX = x;
    mouseY = y;

    // these lines limit the camera's range
    if (mouseY < -100)
        mouseY = -100;
    if (mouseY > 1050)
        mouseY = 1050;

    if ((mouseX - oldMouseX) > 0)		      // mouse moved to the right
        angle1 += 3.0f;
    else if ((mouseX - oldMouseX) < 0)	   // mouse moved to the left
        angle1 -= 3.0f;

    return;
}

int main(int argc, char* argv[])
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
    glutCreateWindow("Chess");

    initialize();
    glutDisplayFunc(displayFunction);

    glutReshapeFunc(reshapeFunction);
    glutKeyboardFunc(keyFunction);
    glutMouseFunc(mouseFunction);
    glutMotionFunc(motionFunction);
    glutSpecialFunc( catchKey);
    //Sleep(500);
    glutMainLoop();
    return 0;

    std::cout << "Hello World!\n";
}

