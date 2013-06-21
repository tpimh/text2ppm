#include <stdio.h>

int main() {
	int h = 640;
	int w = 480;

	printf("P6\n");			// file format
	printf("%d %d\n", h, w);	// height and width
	printf("255\n");		// color depth

	for (int k = 0; k < w; k++) {
		for (int i = 0; i < h; i++) {
			printf("%c%c%c", 0, 0, 0);
		}
	}

	return 0;
}
