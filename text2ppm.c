#include <stdio.h>
#include <string.h>
#include <font8x8_basic.h>

#define CHAR_H	8
#define CHAR_W	8
#define SCR_H	480
#define SCR_W	640
#define ROWS	(SCR_H / CHAR_H) 
#define COLS	(SCR_W / CHAR_W)

void usage (char *exec) {
	fprintf(stderr, "Usage: %s \"STRING\"\n", exec);
}

void render (char str[]) {
	int str_l = strlen(str);

	int s[SCR_H][SCR_W];

	for (int i = 0; i < str_l; i++) {
		char *bitmap = font8x8_basic[str[i]];

		int row = i / COLS;

		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				int set = bitmap[x] & 1 << y;
				s[x + CHAR_H * row][y + CHAR_W * (i - COLS * row)] = set ? 1 : 0;
			}
		}
	}

	// PPM specification: http://netpbm.sourceforge.net/doc/ppm.html
	printf("P6\n");				// file format
	printf("%d %d\n", SCR_W, SCR_H);	// width and height
	printf("255\n");			// maxval 
	
	for (int y = 0; y < SCR_H; y++) {
		for (int x = 0; x < SCR_W; x++) {
			if (s[y][x] == 1) {
				printf("%c%c%c", 0, 0, 0);
			} else {
				printf("%c%c%c", 255, 255, 255);
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
