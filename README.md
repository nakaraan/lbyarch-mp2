


# [LBYARCH MP2] x86-to-C Interface Programming Project
### Almin, Wesner III Aquino, Mark Daniel
#### Section: LBYARCH S13A

An x86-64 and C programming project in fulfillment of the requirements of LBYARCH.

### Correctness Check

It can be seen in the screenshot above that the screen output matches the sample run in the project specifications.

<img width="2704" height="1500" alt="image" src="https://github.com/user-attachments/assets/3e98504e-0618-4ace-9f0b-183445676fe0" />

To confirm this, attached is another screenshot to show the values lining up:

<img width="2098" height="1218" alt="image" src="https://github.com/user-attachments/assets/c98e06cc-9e40-43f5-b2ef-0da91a60a37f" />


### Execution Time

```
[PERFORMANCE TESTING]

TESTING: Different img sizes, 30 iterations each

Image size 10x10 (100 pixels):
  Average execution time: 0.000000 seconds
Image size 100x100 (10000 pixels):
  Average execution time: 0.000067 seconds
Image size 1000x1000 (1000000 pixels):
  Average execution time: 0.005767 seconds
Press any key to exit...
```

### Analysis
The following code snippets highlights the function used to simulate 3 different test cases (10x10 px, 100x100 px, 1000x1000 px), and runs through each test case 30 times before getting the average execution time.

For 100x100 px images, the average execution time was negligible. For 100x100, it averaged around 0.000067 seconds per run. For 1000x1000 px images, the average was 0.005767 seconds. 

The performance metrics highlight that the function is highly scalable with an increasing size, and remains highly performant. 

Attached below is the code for running the performance tests:
```
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
```



