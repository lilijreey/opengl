
all: test menu ortho

test: test.c
	gcc -Wall -o $@ $^ -lm -lglut -lGL -lGLU -lX11
	./$@

menu: menu.c
	gcc -Wall -o $@ $^ -lm -lglut -lGL -lGLU -lX11
	./$@

ortho: ortho.c
	gcc -Wall -o $@ $^ -lm -lglut -lGL -lGLU -lX11
	./$@
