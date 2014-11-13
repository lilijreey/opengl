/**
 * @file     test.c
 *           
 *
 * @author   lili  <lilijreey@gmail.com>
 * @date     13/11/14 13:52:39
 *
 */


#include <GL/glut.h>

static void display()
{
    
    glColor3f(1.0,1.0,0); //set front_color
    glClearColor(0.0, 0.0, 0.5, 0.5); //set bg color

    glClear(GL_COLOR_BUFFER_BIT);
//    glViewport(100, 400, 100, 200);
    glBegin(GL_POLYGON); //v2 中的已经废弃了
    // GL 使用屏幕中点为0.0 点的坐标系
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
//    glVertex2f(0.7, -0.2);
    glEnd();

    glFlush();
}

int
main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 300);
    // left-top window in  screen-left-top
    glutInitWindowPosition(0,0);



    glutCreateWindow("test");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}				/* ----------  end of function main  ---------- */
