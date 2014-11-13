
install develp env
=================================
freeglut3
freeglut3-dev
libglew1.5
libglew1.5-dev
libglu1-mesa
libglu1-mesa-dev
libgl1-mesa-glx
libgl1-mesa-dev

Once you have them installed, link to them when you compile:

g++ -lglut -lGL -lGLU -lGLEW example.cpp -o example

In example.cpp, include the OpenGL libraries like so:

```C
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

Then, to enable the more advanced opengl options like shaders, place this after your glutCreateWindow Call:

GLenum err = glewInit();
if (GLEW_OK != err)
{
    fprintf(stderr, "Error %s\n", glewGetErrorString(err));
    exit(1);
}
fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

if (GLEW_ARB_vertex_program)
    fprintf(stdout, "Status: ARB vertex programs available.\n");

if (glewGetExtension("GL_ARB_fragment_program"))
    fprintf(stdout, "Status: ARB fragment programs available.\n");

if (glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite"))
    fprintf(stdout, "Status: ARB point sprites available.\n");
```

GLFW
==============================
GLFW是一个OpenGL的应用框架,支持Linux和Windows。GLFW 主要用来处理特定操作系统下的特定任务，
例如 OpenGL 窗口管理、分辨率切换、键盘、鼠标以及游戏手柄、定时器输入、线程创建等等

GLUT
===============================
是一個使用OpenGL核心API 开发的工具库，用了快速使用 GL


Unofficial OpenGL SDK
================================
是一个开发GL的一个库集合



3D
==============================
对象的三种操作
1. 平
2. 旋转
3. 缩放
    都可以通关使用称矩阵来表示


rendering
-------------------------------
把3D 显示在2D设备上的方法 (透视)


光栅化  rasterization
------------------------------------
计算机三维成像渲染算法，就是指把景物模型的数学描述及其色彩信息转换至计算机屏幕上象素的过程。 
就是将图转化为一个个栅格组成的图象。
本质为坐标变化，几何离散
光栅化”技术的渲染速度跟“辐射度”与“光线追踪”相比极快，不过由于它并非基于对物理光线的传递计算
，因此对于现实中复杂的光照效果的真实模拟方面，“光栅化”就无能为力了


光线追踪 Ray Tracing
--------------------------------------
一种3D成像


shader
------------------------------------
着色器
Vertex Shader 定点渲染引擎
Pixel  Shader 像素渲染引擎
