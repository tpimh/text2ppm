all: text2ppm

text2ppm:
	${CROSS_COMPILE}gcc -std=c99 -I. -o text2ppm text2ppm.c
clean:
	rm -f text2ppm

