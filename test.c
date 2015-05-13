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


#define	RX 100
#define	LX -RX
#define	TY 100
#define	BY -TY
#define	NZ 100
#define	FZ -NZ


/* 
 *  
 *  Qus.
 *  1. 
    glutReshapeFunc 
    glutDisplayFunc 区别

    2. 
       glOrtho 负责视图区域的裁剪,也就是定义能看见区域大小
         并不负责图像的呈现和在窗口上的显示

       glViewport
         负责把取景区域怎样显示在屏幕上, 也就是说
         glOrtho 等于是整个viewprot, glViewport 用来定义和窗口的映射比例

         比如，　如果我们的viewport 是(-50, 50, -50, 50, -1, 1)
             WindowSize 的大小是100 x 100
             glViewport(0,0, winWight, winHight)
             则这个viewprot 在显示到window上就被放大了 4被

    3. 抗锯齿
          
 */

static void draw_point()
{
    
    //EE 3D Draw
    //  使用OpenGL 画图时，并不关心实际的物理坐标(屏幕上的)，
    //  只关心OpenGl中的, 设置3D 画布
    //  glPointSize/1
      
    //EE 获得支持点大小的范围
    GLfloat sizes[2]; //存储范围 [min, max]
    GLfloat step;

    glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
    GLfloat curSize = sizes[0];
    printf("min %f max %f step %f\n", sizes[0], sizes[1], step);
    
    //EE point 
    // glVertex2f
    // glVertex3f

    //EE 绘制图形，　使用顶点定义
    /*glBegin(GL_POLYGON); //v2 中的已经废弃了*/
    /*    glVertex3f(LX/2,TY/2,0);                   */
    /*    glVertex3f(LX/2,BY/2,10);                  */
    /*    glVertex3f(RX/2,TY/2,0);                   */
    /*glEnd();                                       */


        float z = -50;
        float x, y, angle;
        for (angle = 0; angle  < (2 * M_PI) * 3; angle += 0.05f)
        {
            //Qus. 为何是反的
            x = 50 * sin(angle);
            y = 50 * cos(angle);
            glBegin(GL_POINTS);
            {
                glVertex3f(x, y, z);

            }glEnd();
            z += 0.5f;

            glPointSize(curSize/10);
            curSize += step;
        }

}

static void draw_line()
{
    float x, y ,z, angle;

    //EE glBegin(GL_LINE_STRIP 经过所有点
    //EE glBegin(GL_LINE_LOOP 最后一个点会连接第一个点
    glBegin(GL_LINE_STRIP);
    {
        for (angle = 0; angle <= M_PI+0.3; angle+= (M_PI/20)) {
            // 圆的上半部分
            x = 50 * sin(angle);
            y = 50 * cos(angle);
            glVertex3f(x, y, z);


            // 圆的下半部分
            x = 50 * sin(angle + M_PI);
            y = 50 * cos(angle + M_PI);
            glVertex3f(x, y, z);

        }


    }glEnd();


}


#if 1
static void display()
{
    
    //EE 刷新整窗口的buffer, 使用glClearColor 设置的颜色
    //如果不调用，　OpenGL只会把新的内容绘制在原来的图像上
    //
    glClear(GL_COLOR_BUFFER_BIT); 

    glPushMatrix();

    glRotatef(30, 20, 30, 0);
    
//    draw_point();
    draw_line();


    glPopMatrix();

    //EE 导致所有未执行的GL 命令被执行,
    // GL 的命令通常都在命令队列中，知道同时一起处理多个命令；
    glutSwapBuffers();
} 

#endif

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

static void myreshape(int w, int h)
{
    static int i=0;

    printf("reshape times:%d w %d h %d\n", i++, w, h);
    h = h ? h : 1; //0 

    //EE 把显示区域设置为窗口大小
    // 也就是设置viewport viewport 对应为GL 中能够显示的大小
    // 0 ,0 是指定viewprot 左下角在window 中的坐标
    glViewport(0, 0, w, h);
//    glViewport(0, 0, w/2, h/2); 这时viewprot 占window 的四分之一
//    glViewport(0, 0, w*2, h*2); 这时window 只显示viewport的四分之一

    //EE 重置投影模式
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double aspectRatio = (double)w / h;

    //设置观察矩阵 glOrtho(left, right, bottom, top, near, far)
    //这里的坐标和绘图的坐标系一致,负责摄像机的取景大小
    if(w <= h) { //这段代码的作用是不管window的形状是什么，都会按原始图像比例放大缩小
        glOrtho(LX, RX, TY / aspectRatio, BY / aspectRatio,
                NZ, FZ);
    } else {
        glOrtho(LX * aspectRatio, RX * aspectRatio,
                TY, BY,
                NZ, FZ);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glFlush();
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

//static void _get_gl_version()
//{
//    //EE 得到GL 版本 -> const char *
//    printf("OepnGL Version: %s\n", glGetString(GL_VERSION));
//}

static void init()
{
//    _get_gl_version();
    

//    glColor3f(1.0,1.0,0); //set front_color
//    //EE set clear color 就是调用 glClear(GL_COLOR_BUFFER_BIT) 时的填充色彩
    glClearColor(0.0, 0.0, 0.5, .5); //set bg color

    // GL_PROJECTION 射影
    // GL_MODELVIEW 视图
    // GL_TEXTURE 纹理
    glMatrixMode(GL_PROJECTION);

    // 把矩阵设为单位矩阵
    glLoadIdentity();

//    glShadeModel(GL_FLAT);

//    glPointSize(1);
//    glLineWidth(1); // set line width
    
// 　设置多边形的绘制方式
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    
    // set window 
//    gluOrtho2D(-0.5, 1, -1, 1);

// 当窗口大小改变时调用
    glutReshapeFunc(myreshape);

//    glutIdleFunc(myidle);

    glutKeyboardFunc(keycb);
}

int
main(int argc, char *argv[])
{
    //EE 初始化 glut
    glutInit(&argc, argv);

    //EE 指定创建窗口是使用那种显示模式 
    //- GLUT_RGB RGB 颜色模式
    //- GLUT_RGBA RGBA 带透明度的RGB模式
    //- GLUT_SINGLE 单缓冲模块
    //-   绘制是在显示buf中进行的
    //- GLUT_DOUBLE 双缓冲，　
    //　　绘制在后台buf中，绘制好后快速替换显示buf, 显示效果号
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // 必须配合gl glutSwapBuffers()
//    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutInitWindowSize(500, 500);
    // left-top window in  screen-left-top
    glutInitWindowPosition(0,0);

    //EE 创建窗口 title
    glutCreateWindow("test");

    //EE 设定显示回调, 何时回调??
    glutDisplayFunc(display);

    init();

    //EE 运行glut 框架
    glutMainLoop();
    return 0;
}				/* ----------  end of function main  ---------- */
