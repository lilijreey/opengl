#Anton's OpenGL 4 Tutorials book demo code#

This series of demos accompanies the e-book "Anton's OpenGL 4 Tutorials":
http://www.amazon.com/gp/product/B00LAMQYF2

Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland. June 2014.
email: anton at antongerdelan dot net


##Compiling##
The libraries reside in the common/ folder

* common/include - header files
* common/linux_i386 - 32-bit linux libraries
* common/linux_x86_64 - 64-bit linux libraries
* common/msvc110 - 32-bit Windows visual studio libraries
* common/osx_64 - 64-bit apple OS X libraries
* common/win32 - 32-bit Windows GCC (mingw) libraries

###Linux###

* install the GNU Compiler Collection - usually by installing a
"build-essentials" package via the package manager on your distribution.
* open a terminal and cd to the demo of choice

64-bit systems:

`make -f Makefile.linux64`

32-bit systems:

`make -f Makefile.linux32`

###64-bit Apple OS X###

I don't have an Apple machine so these may not all have a Makefile available
right away. I'll do my best to update this and test all the projects - check
back for updates. The Apple drivers are not great - expect bugs in some demos.

* install the GNU Compiler Collection - usually by installing XCode
* open a terminal and cd to the demo of choice

`make -f Makefile.osx`

###Windows with GCC###

I only provided 32-bit versions of the Makefile and libraries here. If you want
to add a 64-bit build it's pretty easy to copy the 32-bit Makefile and change
the folder. You will need to recompile GLFW, GLEW, AssImp, and Freetype though.
The 32-bit builds will run on all Windows machines - I use 32-bit builds on my
64-bit Windows.

* install the GNU Compiler Collection - usually by installing the MinGW toolkit.
http://www.mingw.org/
* open a console and cd to the demo of choice

`make -f Makefile.win32`

* copy the .dll files from the main folder to the demo folder

###Windows with Visual Studio###

I provided some Visual Studio 2012 project files.
You can find an overarching solution file in the main folder. This should
convert well to most versions of visual studio. I used 32-bit versions of the
libraries, but there's no reason that you can't add 64-bit versions if you
prefer.

##SDL2 Port##

Dr Aidan Delaney at the University of Brighton has made an SDL2 port (as an alternative to using GLFW), which you can find on GitHub https://github.com/AidanDelaney/antons_opengl_tutorials_book/tree/sdl2-port/00_hello_triangle
(see Makefile.linux64)


```c

//EE get fps and print to windows title;
/* we will use this function to update the window title with a frame rate */
void _update_fps_counter (GLFWwindow* window) {
	double current_seconds;
	double elapsed_seconds;
	
	current_seconds = glfwGetTime ();
	elapsed_seconds = current_seconds - previous_seconds;
	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		char tmp[128];
		double fps = (double)frame_count / elapsed_seconds;
		sprintf (tmp, "opengl @ fps: %.2f", fps);
		glfwSetWindowTitle (window, tmp);
		frame_count = 0;
	}
	frame_count++;
}
```
