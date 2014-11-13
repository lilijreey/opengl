
all: test

test: test.c
	gcc -Wall -o $@ $^ -lglut -lGL -lGLU -lX11
	./$@
