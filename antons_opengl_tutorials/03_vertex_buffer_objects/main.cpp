/******************************************************************************\
| OpenGL 4 Example Code.                                                       |
| Accompanies written series "Anton's OpenGL 4 Tutorials"                      |
| Email: anton at antongerdelan dot net                                        |
| First version 27 Jan 2014                                                    |
| Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.                |
| See individual libraries for separate legal notices                          |
|******************************************************************************|
| Vertex Buffer Objects and interpolation                                      |
\******************************************************************************/
#include "gl_utils.h" // utility stuff discussed in previous tutorials is here
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#define GL_LOG_FILE "gl.log"

// keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 640;
int g_gl_height = 480;
GLFWwindow* g_window = NULL;

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

glm::mat4 get_mvp()
{
    //定义投影矩阵
    glm::mat4 projection = glm::perspective(45.0f, 4.0f/3.0f, .1f, 100.0f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(4.f,3,3), //camera positon
        glm::vec3(0.f,0,0), //origion position in camera
        glm::vec3(0.f,1,0) //head is up
        );

    glm::mat4 model = glm::mat4(1.0f);

    return projection * view* model;
}

int main () {
	assert (restart_gl_log ());
	// all the start-up code for GLFW and GLEW is called here
	assert (start_gl ());

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"


	/* OTHER STUFF GOES HERE NEXT */
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

  glm::mat4 mvp = glm::mat4(1.0f);
	
	GLuint points_vbo;
	glGenBuffers (1, &points_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
//	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (GLfloat), points, GL_STATIC_DRAW);
	glBufferData (GL_ARRAY_BUFFER, 
                sizeof(g_vertex_buffer_data) * sizeof (GLfloat),
                g_vertex_buffer_data, 
                GL_STATIC_DRAW);
	
	/* create a second VBO, containing the array of colours.
	note that we could also put them both into a single vertex buffer. in this
	case we would use the pointer and stride parameters of glVertexAttribPointer()
	to describe the different data layouts */
	GLuint colours_vbo;
	glGenBuffers (1, &colours_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, colours_vbo);
//	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (GLfloat), colours, GL_STATIC_DRAW);
	glBufferData (GL_ARRAY_BUFFER, 
                sizeof(g_color_buffer_data) * sizeof (GLfloat),
                g_color_buffer_data, 
                GL_STATIC_DRAW);
	
	/* create the VAO.
	we bind each VBO in turn, and call glVertexAttribPointer() to indicate where
	the memory should be fetched for vertex shader input variables 0, and 1,
	respectively. we also have to explicitly enable both 'attribute' variables.
	'attribute' is the older name for vertex shader 'in' variables. */
	GLuint vao;
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer (GL_ARRAY_BUFFER, colours_vbo);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray (0);
	glEnableVertexAttribArray (1);
	
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
  glBindAttribLocation(shader_programme, 0, "vertex_position");
  glBindAttribLocation(shader_programme, 1, "vertex_colour");
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

//pass uniform
    GLint u = glGetUniformLocation(shader_programme, "mvp");
    assert (u > -1);
    glUniformMatrix4fv(u, 1, GL_FALSE, &mvp[0][0]);

	
	glEnable (GL_CULL_FACE); // cull face
	glCullFace (GL_BACK); // cull back face
	glFrontFace (GL_CW); // GL_CCW for counter clock-wise
	
	while (!glfwWindowShouldClose (g_window)) {
		_update_fps_counter (g_window);
		// wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport (0, 0, g_gl_width, g_gl_height);
		
		glUseProgram (shader_programme);
		glBindVertexArray (vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays (GL_TRIANGLES, 0, 12* 3);
		// update other events like input handling 
		glfwPollEvents ();
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
