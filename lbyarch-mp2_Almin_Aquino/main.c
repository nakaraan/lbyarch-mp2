#include <stdio.h>
#include <stdlib.h>

extern imgCvtGrayInttoFloat(int height, int width, int* data, float* gray);


int main() {

	// get user input for [HEIGHT] [WIDTH] and the following data values
	int i, j, height, width;
	int data[10000][10000] = { 0 };
	float gray[10000][10000] = { 0 };

	printf("<height> <width> <data matrix>\n\n");

	scanf("%d %d", &height, &width);

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			scanf("%d", &data[i][j]);
		}
	}

	

	return 0;
}