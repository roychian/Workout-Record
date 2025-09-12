all:
	gcc -I src/include -L src/lib -o run FP_MAIN.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image