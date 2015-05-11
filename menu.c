/**
 * @file     menu.c
 *           GULT 菜单
 *
 * @author   lili  <lilijreey@gmail.com>
 * @date     14/11/14 18:20:22
 *
 */
#include <GL/glut.h>
#include <math.h>

enum{
    QUIT,
};

int singleb, doubleb;


//使用 double-cache and 旋转正方型
static GLfloat theta = 0.0f;
#define DEG_TO_RAD 0.017453

static void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat rad =  DEG_TO_RAD * theta;
    glBegin(GL_POLYGON); 
    // 正方型的四个定点
    glColor3f(1,0,0),
    glVertex2f(cos(rad), sin(rad));
    glColor3f(0,1,0),
    glVertex2f(-sin(rad), cos(rad));
    glColor3f(0,0,1),
    glVertex2f(-cos(rad), -sin(rad));
    glColor3f(1,1,0),
    glVertex2f(sin(rad), -cos(rad));
    glEnd();

    glutSwapBuffers();
    glFlush();
//    usleep(200);
}


static void idle()
{
    theta += 2.0;
    if (theta > 360.0)
        theta -= 360.0;

    glutSetWindow(singleb);
    glutPostWindowRedisplay(singleb);

    glutSetWindow(doubleb);
    glutPostWindowRedisplay(doubleb);
}

static void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        glutIdleFunc(idle);

    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        glutIdleFunc(NULL);
}

static void reshap(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void mykey(unsigned char key, int x, int y)
{
    if (key == 'Q' || key == 'q')
        exit(0);
}

static void quit_menu(int id)
{
    if (id == QUIT)
    exit(0);
}

static void init()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

}

int
main(int argc, char *argv[])
{
    glutInit(&argc, argv);

//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    singleb = glutCreateWindow("single buffered");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshap);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutKeyboardFunc(mykey);

    // create a double cache window
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(310, 0);
    doubleb = glutCreateWindow("double buffered");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshap);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutCreateMenu(quit_menu);
    glutAddMenuEntry("quit", QUIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}				/* ----------  end of function main  ---------- */
