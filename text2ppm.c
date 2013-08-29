#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <font8x8_basic.h>

#define CHAR_H	8
#define CHAR_W	8
#define SCR_H	480
#define SCR_W	640
#define ROWS	(SCR_H / CHAR_H) 
#define COLS	(SCR_W / CHAR_W)
#define	TOTAL	(ROWS * COLS)

#define SPACES_IN_A_TAB 4

void usage (char *exec) {
	fprintf(stderr, "Usage: %s \"STRING\"\n", exec);
}

void render (char str[]) {
	size_t str_l = strlen(str);

	int s[SCR_H][SCR_W];

	for (int i = 0; i < str_l; i++) {
		unsigned char *bitmap = font[0];

		if (str[i] >= 32 && str[i] <= 127) {
			bitmap = font[(unsigned char)str[i]];
		} else if (str[i] == '\t') {
			char *tmp = malloc(str_l + SPACES_IN_A_TAB);

			strncpy(tmp, str, i);
			for (int j = 0; j < SPACES_IN_A_TAB; j++) {
				strcpy(tmp + i + j, " ");
			}
			strncpy(tmp + i + SPACES_IN_A_TAB, str + i + 1, str_l - i);

			strcpy(str, tmp);
			free(tmp);
			str_l = strlen(str);

			bitmap = font[(unsigned char)str[i]];
		} else if (str[i] == '\n') {
			int spaces = COLS - (i - (i / COLS) * COLS);

			char *tmp = malloc(str_l + spaces);

			strncpy(tmp, str, i);
			for (int j = 0; j < spaces; j++) {
				strcpy(tmp + i + j, " ");
			}
			strncpy(tmp + i + spaces, str + i + 1, str_l - i);

			strcpy(str, tmp);
			free(tmp);
			str_l = strlen(str);

			bitmap = font[(unsigned char)str[i]];
			
		} else {
			fprintf(stderr, "warn: unknown char (pos:%d, hex:%X), space used instead\n", i, str[i]);
		}

		if (i < TOTAL) {
			fprintf(stderr, "info: char '%c' (pos:%d, hex:%X)\n", str[i], i, str[i]);

			int row = i / COLS;

			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {
					int set = bitmap[x] & 1 << y;
					s[x + CHAR_H * row][y + CHAR_W * (i - COLS * row)] = set ? 1 : 0;
				}
			}
		}
	}

	if ((int)str_l > TOTAL) {
		fprintf(stderr, "warn: %d ending chars omitted\n", (int)str_l - TOTAL);
	}

	fprintf(stderr, "info: last (pos:%d, hex:%X)\n", (int)str_l, str[str_l]);

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
