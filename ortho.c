/**
 * @file     ortho.c
 *           
 *
 * @author   lili  <lilijreey@gmail.com>
 * @date     15/11/14 13:41:29
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <GL/glut.h>
#include <math.h>


void init()
{
    glClearColor(0,0,0,0);
    glColor3f(1,1,1);


}

void reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4,4,-4,4,-4,4);
//    glFrustum(-4,4,-4,4,0,14);

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //平移
//    glTranslatef(0.5,0,0),

//    glRotatef(0.5, 0.5,1,1);

    //摄像机 在１１１，点　指向０００，点
    gluLookAt(0.8,0.8,1, 0,0,0, 0, 1, 0);

    // 生成一个立方体，中心位于原点
    glutWireCube(0.5);
//    glutSolidCube(0.5);
    glutSwapBuffers();

}

int
main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("othro");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    init();
    glutMainLoop();

    return 0;
}				/* ----------  end of function main  ---------- */
