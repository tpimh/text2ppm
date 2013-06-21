#include <stdio.h>
#include <string.h>
#include <font8x8_basic.h>

#define CHAR_H 8
#define CHAR_W 8

void usage (char *exec) {
	fprintf(stderr, "Usage: %s \"STRING\"\n", exec);
}

void render (char str[]) {
	int str_l = strlen(str);

	int s[CHAR_H][CHAR_W * str_l];

	for (int i = 0; i < str_l; i++) {
		char *bitmap = font8x8_basic[str[i]];

		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				int set = bitmap[x] & 1 << y;
				s[x][y + CHAR_W * i] = set ? 1 : 0;
			}
		}
	}

	int h = 480;
	int w = 640;

	// PPM specification: http://netpbm.sourceforge.net/doc/ppm.html
	printf("P6\n");			// file format
	printf("%d %d\n", w, h);	// width and height
	printf("1\n");			// maxval 
	
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (x > sizeof(s[x]) / 4 - 1 || y > CHAR_H - 1) {
				printf("%c%c%c", 1, 1, 1);
			} else {
				if (s[y][x] == 1) {
					printf("%c%c%c", 0, 0, 0);
				} else {
					printf("%c%c%c", 1, 1, 1);
				}
			}
		}
	}
}

int main (int argc, char *argv[]) {

	if (argc != 2) {
		usage(argv[0]);
		return 1;
	} else {
		render(argv[1]);
		return 0;
	}
}
