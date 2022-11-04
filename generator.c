#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "siphash.h"

int main() {
    unsigned char key[16] = {0};
    int bytes;

    printf("Enter 16-byte key:");
    scanf("%s", key);
    printf("Enter amount of bytes to generate:");
    scanf("%d", &bytes);
    if (bytes > 99999999) {
        printf("Too large amount of bytes");
        return -1;
    } else if (bytes <= 0) {
        printf("Enter positive number of bytes");
        return -1;
    }
    unsigned char in_buffer[8] = {0};
    unsigned char* output = (unsigned char*) malloc(bytes * sizeof(unsigned char));
    uint8_t out_uint[8] = {0};

    int number_of_iterations;
    if (bytes % 8 == 0) {
        number_of_iterations = bytes / 8;
    } else {
        number_of_iterations = (bytes / 8) + 1;
    }

    for (int i = 0, j = 0; i < number_of_iterations; i++, j += 8) {
        siphash(in_buffer, 8, key, out_uint);
        memcpy(in_buffer, (unsigned char*) out_uint, 8);
        if (i == number_of_iterations - 1 && bytes % 8 != 0) {
            memcpy(&output[j], in_buffer, bytes % 8);
            break;
        }
        memcpy(&output[j], in_buffer, 8);
    }

    FILE *file = fopen("result.txt", "w");
    int results = fwrite(output, sizeof(unsigned char), bytes, file);
    if (results == EOF) {
        printf("Cannot write to file");
        return -1;
    }
    fclose(file);
    free(output);
    return 0;
}