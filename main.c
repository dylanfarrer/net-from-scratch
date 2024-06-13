#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GET_MACRO(_1,_2,NAME,...) NAME
#define DEBUG_PRINT(...) GET_MACRO(__VA_ARGS__, DEBUG_PRINT2, DEBUG_PRINT1)(__VA_ARGS__)

#define DEBUG_PRINT1(msg) \
    fprintf(stderr, "DEBUG: %s:%d:%s(): " msg, __FILE__, __LINE__, __FUNCTION__)

#define DEBUG_PRINT2(msg, ...) \
    fprintf(stderr, "DEBUG: %s:%d:%s(): " msg, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

#define TRAIN_CSV "dataset/mnist_train.csv"
#define TEST_CSV "dataset/mnist_test.csv"
#define IMAGE_SIZE 784
#define TRAIN_LENGTH 60000
#define TEST_LENGTH 10000

typedef struct {
    unsigned char label;
    unsigned char image[IMAGE_SIZE];
} MNIST_Image;

void read_csv(const char* filename, MNIST_Image* images, int size) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char line[2048];
    for (int i = 0; i < size && fgets(line, sizeof(line), fp); ++i) {
        char *token = strtok(line, ",");
        images[i].label = (unsigned char)atoi(token);
        
        for (int j = 0; j < IMAGE_SIZE; ++j) {
            token = strtok(NULL, ",");
            if (token == NULL) {
                break;
            }
            images[i].image[j] = (unsigned char)atoi(token);
        }
    }

    fclose(fp);
}

int main() {
    DEBUG_PRINT("At the start of main.\n");

    MNIST_Image *train_images = malloc(TRAIN_LENGTH * sizeof(MNIST_Image));
    MNIST_Image *test_images = malloc(TEST_LENGTH * sizeof(MNIST_Image));

    if (train_images == NULL || test_images == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return EXIT_FAILURE;
    }
    DEBUG_PRINT("train and test images have been allocated memory.\n");

    read_csv(TRAIN_CSV, train_images, TRAIN_LENGTH);

    DEBUG_PRINT("train csv has been read.\n");

    read_csv(TEST_CSV, test_images, TEST_LENGTH);

    DEBUG_PRINT("test csv has been read.\n");

    printf("First train image label: %d\n", train_images[0].label);
    for (int i = 0; i < IMAGE_SIZE; i++) {
        if (train_images[0].image[i] != 0) {
            printf("  ");
        } else {
            printf("%d ", train_images[0].image[i]);
        }
        if ((i + 1) % 28 == 0) printf("\n");
    }

    printf("\nFirst test image label: %d\n", test_images[0].label);
    for (int i = 0; i < IMAGE_SIZE; i++) {
        if (test_images[0].image[i] != 0) {
            printf("  ");
        } else {
            printf("%d ", test_images[0].image[i]);
        }
        if ((i + 1) % 28 == 0) printf("\n");
    }

    free(train_images);
    free(test_images);

    return 0;
}
