#include <stdio.h>
#include <font8x8_basic.h>

int main() {
	int h = 640;
	int w = 480;

	printf("P6\n");			// file format
	printf("%d %d\n", h, w);	// height and width
	printf("1\n");			// color depth

	char *bitmap = font8x8_basic[65];

	int s[8][8];
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			int set = bitmap[x] & 1 << y;
			s[x][y] = set ? 1 : 0;
		}
	}


	for (int k = 0; k < w; k++) {
		for (int i = 0; i < h; i++) {
			if (i > 19 && i < 28 && k > 19 && k < 28) {
				if (s[k-20][i-20] == 1){
					printf("%c%c%c", 0, 0, 0);
				} else {
					printf("%c%c%c", 1, 1, 1);
				}
			} else { printf("%c%c%c", 1, 1, 1); }
		}
	}

	return 0;
}
