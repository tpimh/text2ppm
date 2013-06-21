#include <stdio.h>

int main() {
	int h = 640;
	int w = 480;

	printf("P6\n");			// file format
	printf("%d %d\n", h, w);	// height and width
	printf("1\n");			// color depth

	for (int k = 0; k < w; k++) {
		for (int i = 0; i < h; i++) {
			if (i * k % 5 == 0) {
				printf("%c%c%c", 0, 0, 0);
			} else {
				printf("%c%c%c", 1, 1, 1);
			}
		}
	}

	return 0;
}
