#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// External assembly function declaration
extern void imgCvtGrayInttoFloat(int height, int width, unsigned char* intPixels, float* floatPixels);

// Printing integer pixel array
void printIntegerPixels(unsigned char* pixels, int height, int width) {
    printf("\n[INPUT (Integer Pixel Values)]\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%3d", pixels[i * width + j]);
            if (j < width - 1) printf(", ");
        }
        printf("\n");
    }
}

// Printing float pixel array
void printFloatPixels(float* pixels, int height, int width) {
    printf("\n[OUTPUT (Float Pixel Values)]\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%.2f", pixels[i * width + j]);
            if (j < width - 1) printf(" ");
        }
        printf("\n");
    }
}

// Input validation function
int validatePixelValue(int value) {
    return (value >= 0 && value <= 255);
}

// Performance testing (30 iterations)
void performanceTest() {
    printf("\n[PERFORMANCE TESTING]\n\n");
    printf("TESTING: Different img sizes, 30 iterations each\n\n");

    int testSizes[][2] = { {10, 10}, {100, 100}, {1000, 1000} };
    int numSizes = sizeof(testSizes) / sizeof(testSizes[0]);

    for (int s = 0; s < numSizes; s++) {
        int height = testSizes[s][0];
        int width = testSizes[s][1];
        int size = height * width;

        // Allocate memory
        unsigned char* intPixels = (unsigned char*)malloc(size * sizeof(unsigned char));
        float* floatPixels = (float*)malloc(size * sizeof(float));

        if (!intPixels || !floatPixels) {
            printf("Memory allocation failed for %dx%d image\n", height, width);
            if (intPixels) free(intPixels);
            if (floatPixels) free(floatPixels);
            continue;
        }

        // Generate test data
        srand((unsigned int)time(NULL));
        for (int i = 0; i < size; i++) {
            intPixels[i] = rand() % 256;
        }

        // Measure performance (30 iterations)
        clock_t start = clock();
        for (int i = 0; i < 30; i++) {
            imgCvtGrayInttoFloat(height, width, intPixels, floatPixels);
        }
        clock_t end = clock();

        double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
        double avgTime = totalTime / 30.0;

        printf("Image size %dx%d (%d pixels):\n", width, height, size);
        printf("  Average execution time: %.6f seconds\n", avgTime);

        free(intPixels);
        free(floatPixels);
    }
}

int main() {
    int height, width;

    // Get image dimensions from user
    printf("Enter image dimensions:\n");
    printf("Height: ");
    if (scanf_s("%d", &height) != 1 || height <= 0 || height > 1000) {
        printf("Error: Invalid height. Please enter a positive integer (1-1000).\n");
        return 1;
    }

    printf("Width: ");
    if (scanf_s("%d", &width) != 1 || width <= 0 || width > 1000) {
        printf("Error: Invalid width. Please enter a positive integer (1-1000).\n");
        return 1;
    }

    int size = height * width;

    // Allocate memory for pixel arrays
    unsigned char* intPixels = (unsigned char*)malloc(size * sizeof(unsigned char));
    float* floatPixels = (float*)malloc(size * sizeof(float));

    if (!intPixels || !floatPixels) {
        printf("Error: Memory allocation failed.\n");
        if (intPixels) free(intPixels);
        if (floatPixels) free(floatPixels);
        return 1;
    }

    // Get pixel values from user
    printf("\nEnter %d integer pixel values (0-255):\n", size);

    for (int i = 0; i < size; i++) {
        int pixelValue;

        // Skip commas if present
        char c;
        while ((c = getchar()) == ',' || c == ' ' || c == '\n' || c == '\t') {
            // Skip whitespace and commas
        }
        ungetc(c, stdin);  // Put the character back

        if (scanf_s("%d", &pixelValue) != 1) {
            printf("Error: Invalid input. Please enter integers only.\n");
            free(intPixels);
            free(floatPixels);
            return 1;
        }

        if (!validatePixelValue(pixelValue)) {
            printf("Error: Pixel value %d is out of range. Values must be 0-255.\n", pixelValue);
            free(intPixels);
            free(floatPixels);
            return 1;
        }
        intPixels[i] = (unsigned char)pixelValue;
    }

    // Display input
    printIntegerPixels(intPixels, height, width);

    // Convert using assembly function
    printf("\nConverting using x86-64 assembly function...\n");
    imgCvtGrayInttoFloat(height, width, intPixels, floatPixels);

    // Display output
    printFloatPixels(floatPixels, height, width);

    // Ask user if they want to see performance testing
    printf("\nWould you like to run performance testing? (y/n): ");
    char choice;
    scanf_s(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        performanceTest();
    }

    // Clean up
    free(intPixels);
    free(floatPixels);

    printf("Press any key to exit...\n");
    getchar();
    getchar(); // newline collector

    return 0;
}