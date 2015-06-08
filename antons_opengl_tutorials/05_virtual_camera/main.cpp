/******************************************************************************\
| OpenGL 4 Example Code.                                                       |
| Accompanies written series "Anton's OpenGL 4 Tutorials"                      |
| Email: anton at antongerdelan dot net                                        |
| First version 27 Jan 2014                                                    |
| Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.                |
| See individual libraries for separate legal notices                          |
|******************************************************************************|
| Virtual Camera - create and modify VIEW and PROJECTION matrices              |
| keyboard controls: W,S,A,D,left and right arrows                             |
\******************************************************************************/
#include "maths_funcs.h"
#include "gl_utils.h"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define GL_LOG_FILE "gl.log"
#include "stb_image/stb_image.h"


//一个curd 用三角来话，每个face need two trangle
static	const	GLfloat	g_vertex_buffer_data[]	=	{
-1.0f,-1.0f,-1.0f,	//	triangle	1	:	begin
-1.0f,-1.0f,	1.0f,
-1.0f,	1.0f,	1.0f,	//	triangle	1	:	end
1.0f,	1.0f,-1.0f,	//	triangle	2	:	begin
-1.0f,-1.0f,-1.0f,
-1.0f,	1.0f,-1.0f,	//	triangle	2	:	end
1.0f,-1.0f,	1.0f,
-1.0f,-1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
1.0f,	1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f,	1.0f,	1.0f,
-1.0f,	1.0f,-1.0f,
1.0f,-1.0f,	1.0f,
-1.0f,-1.0f,	1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f,	1.0f,	1.0f,
-1.0f,-1.0f,	1.0f,
1.0f,-1.0f,	1.0f,
1.0f,	1.0f,	1.0f,
1.0f,-1.0f,-1.0f,
1.0f,	1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
1.0f,	1.0f,	1.0f,
1.0f,-1.0f,	1.0f,
1.0f,	1.0f,	1.0f,
1.0f,	1.0f,-1.0f,
-1.0f,	1.0f,-1.0f,
1.0f,	1.0f,	1.0f,
-1.0f,	1.0f,-1.0f,
-1.0f,	1.0f,	1.0f,
1.0f,	1.0f,	1.0f,
-1.0f,	1.0f,	1.0f,
1.0f,-1.0f,	1.0f
};

static	const	GLfloat	g_color_buffer_data[]	=	{
0.583f,	0.771f,	0.014f,
0.609f,	0.115f,	0.436f,
0.327f,	0.483f,	0.844f,
0.822f,	0.569f,	0.201f,
0.435f,	0.602f,	0.223f,
0.310f,	0.747f,	0.185f,
0.597f,	0.770f,	0.761f,
0.559f,	0.436f,	0.730f,
0.359f,	0.583f,	0.152f,

0.483f,	0.596f,	0.789f,
0.559f,	0.861f,	0.639f,
0.195f,	0.548f,	0.859f,
0.014f,	0.184f,	0.576f,
0.771f,	0.328f,	0.970f,
0.406f,	0.615f,	0.116f,
0.676f,	0.977f,	0.133f,
0.971f,	0.572f,	0.833f,
0.140f,	0.616f,	0.489f,
0.997f,	0.513f,	0.064f,
0.945f,	0.719f,	0.592f,
0.543f,	0.021f,	0.978f,
0.279f,	0.317f,	0.505f,
0.167f,	0.620f,	0.077f,
0.347f,	0.857f,	0.137f,
0.055f,	0.953f,	0.042f,
0.714f,	0.505f,	0.345f,
0.783f,	0.290f,	0.734f,
0.722f,	0.645f,	0.174f,
0.302f,	0.455f,	0.848f,
0.225f,	0.587f,	0.040f,0.517f,	0.713f,	0.338f,
0.053f,	0.959f,	0.120f,
0.393f,	0.621f,	0.362f,
0.673f,	0.211f,	0.457f,
0.820f,	0.883f,	0.371f,
0.982f,	0.099f,	0.879f
};


static	const	GLfloat	g_uv_buffer_data[]	=	{
				0.000059f,	1.0f-0.000004f,
				0.000103f,	1.0f-0.336048f,
				0.335973f,	1.0f-0.335903f,
				1.000023f,	1.0f-0.000013f,
				0.667979f,	1.0f-0.335851f,
        0.999958f,	1.0f-0.336064f,
				0.667979f,	1.0f-0.335851f,
				0.336024f,	1.0f-0.671877f,
				0.667969f,	1.0f-0.671889f,
				1.000023f,	1.0f-0.000013f,
				0.668104f,	1.0f-0.000013f,
				0.667979f,	1.0f-0.335851f,
				0.000059f,	1.0f-0.000004f,
				0.335973f,	1.0f-0.335903f,
				0.336098f,	1.0f-0.000071f,
				0.667979f,	1.0f-0.335851f,
				0.335973f,	1.0f-0.335903f,
				0.336024f,	1.0f-0.671877f,
				1.000004f,	1.0f-0.671847f,
				0.999958f,	1.0f-0.336064f,
				0.667979f,	1.0f-0.335851f,
				0.668104f,	1.0f-0.000013f,
				0.335973f,	1.0f-0.335903f,
				0.667979f,	1.0f-0.335851f,
				0.335973f,	1.0f-0.335903f,
				0.668104f,	1.0f-0.000013f,
				0.336098f,	1.0f-0.000071f,
				0.000103f,	1.0f-0.336048f,
				0.000004f,	1.0f-0.671870f,
				0.336024f,	1.0f-0.671877f,
				0.000103f,	1.0f-0.336048f,
				0.336024f,	1.0f-0.671877f,
				0.335973f,	1.0f-0.335903f,
				0.667969f,	1.0f-0.671889f,
				1.000004f,	1.0f-0.671847f,
				0.667979f,	1.0f-0.335851f
};

//void load_texture (const char* file_name, GLuint* tex) {
GLint load_texture () {
	int x, y, n;
	int force_channels = 4;
  const char* file_name= "skulluvmap.bmp";
	unsigned char* image_data = stbi_load (file_name, &x, &y, &n, force_channels);
	if (!image_data) {
		fprintf (stderr, "ERROR: could not load %s\n", file_name);
		return -1;
	}
	// NPOT check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
		fprintf (
			stderr, "WARNING: texture %s is not power-of-2 dimensions\n", file_name
		);
	}
  printf("peix width %d hight %d\n", x, y);

  GLuint textureId;
  glGenTextures(1, &textureId);

  //bind new texture, all after texture fn will modify this texture
  glBindTexture(GL_TEXTURE_2D, textureId);

  //send to OpenGL
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_BGR, GL_UNSIGNED_BYTE, file_name);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  stbi_image_free(image_data);
  return textureId;
}

// keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 640;
int g_gl_height = 480;
GLFWwindow* g_window = NULL;

glm::mat4 get_mvp(const glm::vec3 &cam_p)
{
    //定义投影矩阵
    glm::mat4 projection = glm::perspective(45.0f, 4.0f/3.0f, .1f, 100.0f);

    glm::mat4 view = glm::lookAt(
        cam_p,
        glm::vec3(0.f,0,0), //origion position in camera
        glm::vec3(0.f,1,0) //head is up
        );

    glm::mat4 model = glm::mat4(1.0f);

    return projection * view* model;
}

int main () {
	assert (restart_gl_log ());
/*------------------------------start GL context------------------------------*/
	assert (start_gl ());

/*------------------------------create geometry-------------------------------*/
	GLfloat points[] = {
		 0.0f,	0.5f,	0.0f,
		 0.5f, -0.5f,	0.0f,
		-0.5f, -0.5f,	0.0f
	};
	
	GLfloat colours[] = {
		1.0f, 0.0f,  0.0f,
		0.0f, 1.0f,  0.0f,
		0.0f, 0.0f,  1.0f
	};
	
	GLuint points_vbo;
	glGenBuffers (1, &points_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
//	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (GLfloat), points, GL_STATIC_DRAW);
	glBufferData (GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data) * sizeof (GLfloat), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	GLuint colours_vbo;
	glGenBuffers (1, &colours_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, colours_vbo);
//	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (GLfloat), colours, GL_STATIC_DRAW);
	glBufferData (GL_ARRAY_BUFFER, sizeof(g_color_buffer_data) * sizeof (GLfloat), g_color_buffer_data, GL_STATIC_DRAW);
	
	GLuint vao;
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer (GL_ARRAY_BUFFER, colours_vbo);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray (0);
	glEnableVertexAttribArray (1);

/*------------------------------create shaders--------------------------------*/
	char vertex_shader[1024 * 256];
	char fragment_shader[1024 * 256];
	assert (parse_file_into_str ("test_vs.glsl", vertex_shader, 1024 * 256));
	assert (parse_file_into_str ("test_fs.glsl", fragment_shader, 1024 * 256));
	
	GLuint vs = glCreateShader (GL_VERTEX_SHADER);
	const GLchar* p = (const GLchar*)vertex_shader;
	glShaderSource (vs, 1, &p, NULL);
	glCompileShader (vs);
	
	// check for compile errors
	int params = -1;
	glGetShaderiv (vs, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf (stderr, "ERROR: GL shader index %i did not compile\n", vs);
		print_shader_info_log (vs);
		return 1; // or exit or something
	}
	
	GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
	p = (const GLchar*)fragment_shader;
	glShaderSource (fs, 1, &p, NULL);
	glCompileShader (fs);
	
	// check for compile errors
	glGetShaderiv (fs, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf (stderr, "ERROR: GL shader index %i did not compile\n", fs);
		print_shader_info_log (fs);
		return 1; // or exit or something
	}
	
	GLuint shader_programme = glCreateProgram ();
	glAttachShader (shader_programme, fs);
	glAttachShader (shader_programme, vs);
	glLinkProgram (shader_programme);

	
	glGetProgramiv (shader_programme, GL_LINK_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf (
			stderr,
			"ERROR: could not link shader programme GL index %i\n",
			shader_programme
		);
		print_programme_info_log (shader_programme);
		return false;
	}
	
/*--------------------------create camera matrices----------------------------*/
	//[> create PROJECTION MATRIX <]
	//#define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444
	//// input variables
	//float near = 0.1f; // clipping plane
	//float far = 100.0f; // clipping plane
	//float fov = 67.0f * ONE_DEG_IN_RAD; // convert 67 degrees to radians
	//float aspect = (float)g_gl_width / (float)g_gl_height; // aspect ratio
	//// matrix components
	//float range = tan (fov * 0.5f) * near;
	//float Sx = (2.0f * near) / (range * aspect + range * aspect);
	//float Sy = near / range;
	//float Sz = -(far + near) / (far - near);
	//float Pz = -(2.0f * far * near) / (far - near);
	//GLfloat proj_mat[] = {
	//  Sx, 0.0f, 0.0f, 0.0f,
	//  0.0f, Sy, 0.0f, 0.0f,
	//  0.0f, 0.0f, Sz, -1.0f,
	//  0.0f, 0.0f, Pz, 0.0f
	//};
	
	//[> create VIEW MATRIX <]
  float cam_speed = 4.0f; // 1 unit per second
  float cam_yaw_speed = 10.0f; // 10 degrees per second
  glm::vec3 cam_pos(0.0f, 0.0f, 20.0f); // don't start at zero, or we will be too close
  float cam_yaw = 0.0f; // y-rotation in degrees
	//mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2]));
	//mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw);
	//mat4 view_mat = R * T;
	
	/* get location numbers of matrices in shader programme */
	//GLint view_mat_location = glGetUniformLocation (shader_programme, "view");
	//GLint proj_mat_location = glGetUniformLocation (shader_programme, "proj");
  //assert(view_mat_location >  -1);
  //assert(proj_mat_location>  -1);
	//[> use program (make current in state machine) and set default matrix values<]
	//glUseProgram (shader_programme);
	//glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
	//glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, proj_mat);
	
  GLint mvp_h = glGetUniformLocation(shader_programme, "tex");
  assert(mvp_h > -1);
	glUseProgram (shader_programme);
  glm::mat4 mvp = get_mvp(cam_pos);
  GLint tex= load_texture();
	glUniform1d(mvp_h, 1, GL_FALSE, &tex);


/*------------------------------rendering loop--------------------------------*/
	/* some rendering defaults */
//  glEnable (GL_CULL_FACE); // cull face
//  glCullFace (GL_BACK); // cull back face
//  glFrontFace (GL_CW); // GL_CCW for counter clock-wise

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
	
	while (!glfwWindowShouldClose (g_window)) {
		static double previous_seconds = glfwGetTime ();
		double current_seconds = glfwGetTime ();
		double elapsed_seconds = current_seconds - previous_seconds;
		previous_seconds = current_seconds;
	
		_update_fps_counter (g_window);
		// wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport (0, 0, g_gl_width, g_gl_height);
		
		glUseProgram (shader_programme);
		glBindVertexArray (vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays (GL_TRIANGLES, 0, 12 * 3);
		// update other events like input handling 
		glfwPollEvents ();
		
/*-----------------------------move camera here-------------------------------*/
		// control keys
		bool cam_moved = false;
		if (glfwGetKey (g_window, GLFW_KEY_A)) {
			cam_pos.x -= cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if (glfwGetKey (g_window, GLFW_KEY_D)) {
			cam_pos.x += cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if (glfwGetKey (g_window, GLFW_KEY_J)) {
			cam_pos.y += cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if (glfwGetKey (g_window, GLFW_KEY_K)) {
			cam_pos.y -= cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if (glfwGetKey (g_window, GLFW_KEY_W)) {
			cam_pos.z -= cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if (glfwGetKey (g_window, GLFW_KEY_S)) {
			cam_pos.z += cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		/* update view matrix */
    if (cam_moved) {
      glm::mat4 mvp = get_mvp(cam_pos);
      glUniformMatrix4fv (mvp_h, 1, GL_FALSE, &mvp[0][0]);
      printf("cam_p %f %f %f\n", cam_pos.x, cam_pos.y, cam_pos.z);
    }
		
		if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose (g_window, 1);
		}
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers (g_window);
	}
	
	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}
