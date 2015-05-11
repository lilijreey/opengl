/**
 * @file     test.c
 *           
 *
 * @author   lili  <lilijreey@gmail.com>
 * @date     13/11/14 13:52:39
 *
 */


#include <stdio.h>
#include <unistd.h>
#include <GL/glut.h>
#include <math.h>


// keyborad
static void display()
{
    
    glClear(GL_COLOR_BUFFER_BIT);

// 在指定的范围内绘制图形, 默认为整个winodw
//    glViewport(0, 0, 100, 100); //x,y, w, h

// 绘制矩形　(LT, RD)
//    glRectf(-0.5,0.5, 0.5,-0.5);

    glBegin(GL_POLYGON); //v2 中的已经废弃了
// GL 使用屏幕中点为0.0 点的坐标系
//    glVertex2f(-0.5, -0.5);
//    glVertex2f(-0.5, 0.5);
//    glVertex2f(0.5, 0.5);
//    glVertex2f(0.5, -0.5);
 glVertex3f(0,1,0);
 glVertex3f(0,0,1);
 glVertex3f(1,0,0);
    glEnd();

    glFlush();
} 

static void keycb(unsigned char c, int x, int y)
{
    printf("enter key n%u c:%c x_y %d:%d\n", c, c, x ,y);
}

#if 0
// v1
static void display()
{
    
    glClear(GL_COLOR_BUFFER_BIT);

// 在指定的范围内绘制图形, 默认为整个winodw
//    glViewport(0, 0, 100, 100); //x,y, w, h

// 绘制矩形　(LT, RD)
//    glRectf(-0.5,0.5, 0.5,-0.5);

    glBegin(GL_POLYGON); //v2 中的已经废弃了
    // GL 使用屏幕中点为0.0 点的坐标系
    glVertex2f(-0.5, -0.5);
    glColor3f(1,1,1),
    glVertex2f(-0.5, 0.5);
    glColor3f(1,0,0),
    glVertex2f(0.5, 0.5);
    glColor3f(0,1,0),
    glVertex2f(0.5, -0.5);
    glColor3f(0,0,1),
    glEnd();

    glFlush();
} 
#endif

// divide_triangel 没有使用离散
#if 0
static void triangle(GLfloat *a, GLfloat *b, GLfloat *c)
{
    glBegin(GL_LINE_LOOP); 
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
    glEnd();
}


static void divide_triangel(GLfloat *a, GLfloat *b, GLfloat *c, int m)
{

    GLfloat v[3][2];
    int j;
    if (m <= 0) {
        triangle(a, b, c);
        return;
    }


    for (j=0; j < 2; j++)
        v[0][j] = (a[j] + b[j]) /2;

    for (j=0; j < 2; j++)
        v[1][j] = (a[j] + c[j]) /2;

    for (j=0; j < 2; j++)
        v[2][j] = (b[j] + c[j]) /2;

    divide_triangel(a, v[0], v[1], m-1);
    divide_triangel(v[0], b, v[2], m-1);
    divide_triangel(v[1], v[2], c, m-1);
    divide_triangel(v[0], v[1], v[2], m-1);
}

#endif




// divide_triangel_twist 使用离散 旋转图像
//  旋转的角度
#if 0
static float twist=0.6;

static void triangle(GLfloat *a, GLfloat *b, GLfloat *c, int type)
{
    GLfloat v[2];
    double d;

    glBegin(GL_LINE_LOOP);
    switch (type)
    {
    case 2:
    case 4:
    case 6:
    case 7:
        glEdgeFlag(GL_FALSE);
        break;
    default:
        glEdgeFlag(GL_TRUE);
    }

    d = sqrt(a[0]*a[0]+a[1]*a[1]);
    v[0]=cos(twist *d) * a[0] - sin(twist * d) * a[1];
    v[1]=sin(twist *d) * a[0] + cos(twist * d) * a[1];
    glVertex2fv(v);


    switch (type)
    {
    case 3:
    case 4:
    case 5:
    case 7:
        glEdgeFlag(GL_FALSE);
        break;
    default:
        glEdgeFlag(GL_TRUE);
    }
    d = sqrt(b[0]*b[0]+b[1]*b[1]);
    v[0]=cos(twist *d) * b[0] - sin(twist * d) * b[1];
    v[1]=sin(twist *d) * b[0] + cos(twist * d) * b[1];
    glVertex2fv(v);

    switch (type)
    {
    case 1:
    case 5:
    case 6:
    case 7:
        glEdgeFlag(GL_FALSE);
        break;
    default:
        glEdgeFlag(GL_TRUE);
    }
    d = sqrt(c[0]*c[0]+c[1]*c[1]);
    v[0]=cos(twist *d) * c[0] - sin(twist * d) * c[1];
    v[1]=sin(twist *d) * c[0] + cos(twist * d) * c[1];
    glVertex2fv(v);

    glEnd();
}

static void divide_triangel(GLfloat *a, GLfloat *b, GLfloat *c, int m, int k)
{

    GLfloat v[3][2];
    int j, flag[4];

    if (m <= 0) {
        triangle(a, b, c ,k);
        return;
    }

    for (j=0; j < 2; j++) {
        v[0][j] = (a[j] + b[j]) /2;
        v[1][j] = (a[j] + c[j]) /2;
        v[2][j] = (b[j] + c[j]) /2;
    }

    switch (k)
    {
    case 0:
        flag[0]=3;
        flag[1]=1;
        flag[2]=2;
        break;

    case 1:
        flag[0]=5;
        flag[1]=1;
        flag[2]=6;
        break;

    case 2:
        flag[0]=4;
        flag[1]=6;
        flag[2]=2;
        break;

    case 3:
        flag[0]=3;
        flag[1]=5;
        flag[2]=4;
        break;

    case 4:
        flag[0]=4;
        flag[1]=7;
        flag[2]=4;
        break;

    case 5:
        flag[0]=5;
        flag[1]=5;
        flag[2]=7;
        break;

    case 6:
        flag[0]=7;
        flag[1]=6;
        flag[2]=6;
        break;

    case 7:
        flag[0]=7;
        flag[1]=7;
        flag[2]=7;
        break;
    }

    flag[3]=7;

    divide_triangel(a, v[0], v[1], m-1, flag[0]);
    divide_triangel(v[0], b, v[2], m-1, flag[1]);
    divide_triangel(v[1], v[2], c, m-1, flag[2]);
    divide_triangel(v[0], v[1], v[2], m-1, flag[3]);
}


static void display()
{

    GLfloat a[]={0, 0.5};
    GLfloat b[]={-0.5, -0.5};
    GLfloat c[]={0.5, -0.5};

    glClear(GL_COLOR_BUFFER_BIT);
//    divide_triangel(a,b,c,4,0);
//    triangle(a,b,c);
   glFlush();
    
}

#endif

// 重绘函数
static void myreshape(int w, int h)
{
    static i=0;

    printf("reshape times:%d w %d h %d\n", i++, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    if(w <= h) {
//        gluOrtho2D(-0.2, 0.2, -0.2 *(GLfloat)h/(GLfloat)w,
//                   2.0 * (GLfloat)h/(GLfloat)w);
//    } else {
//
//    }
//
//    glMatrixMode(GL_MODELVIEW);
//    glViewport(0,0,w,h);
}

#if 0

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

// 非常快不停的调用
static void myidle()
{
//    static size_t i=0;
//    printf("idel times:%lu\n", i++);

    theta += 2.0;
    if (theta > 360.0f)
        theta -= 360.0f;

    glutPostRedisplay();

}

#endif

static void init()
{

//    glColor3f(1.0,1.0,0); //set front_color
//    glClearColor(0.0, 0.0, 0.5, 0.5); //set bg color

    // GL_PROJECTION 射影
    // GL_MODELVIEW 视图
    // GL_TEXTURE 纹理
    glMatrixMode(GL_PROJECTION);

    // 把矩阵设为单位矩阵
    glLoadIdentity();

//    glShadeModel(GL_FLAT);

//    glPointSize(1);
    glLineWidth(1); // set line width
    
// 　设置多边形的绘制方式
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    
    // set window 
//    gluOrtho2D(-0.5, 1, -1, 1);

//    glutReshapeFunc(myreshape);

//    glutIdleFunc(myidle);

    glutKeyboardFunc(keycb);
}

int
main(int argc, char *argv[])
{
    glutInit(&argc, argv);

//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 500);

    // left-top window in  screen-left-top
    glutInitWindowPosition(0,0);

    glutCreateWindow("test");
    glutDisplayFunc(display);

    init();
    glutMainLoop();
    return 0;
}				/* ----------  end of function main  ---------- */
