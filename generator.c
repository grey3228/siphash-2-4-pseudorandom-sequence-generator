#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "siphash.h"

int main() {
    // объявление переменных для хранения ключа и длины генерируемой последовательности
    unsigned char key[16] = {0};
    int bytes;

    // запрос ввода ключа от пользователя из консоли
    printf("Enter 16-byte key:");
    // чтение ключа
    scanf("%s", key);
    // запрос ввода длины генерируемой последовательности из консоли
    printf("Enter amount of bytes to generate:");
    // чтение длины
    scanf("%d", &bytes);
    /* проверка условия: введённая длина генерируемой последовательности
        должна принадлежать промежутку [1, 2^(31) - 1] */
    if (bytes <= 0) {
        printf("Error: enter positive number of bytes lower than 2^(31)");
        return -1;
    }

    /* Объявление массива для хранения входного сообщения хэш-функции.
    Данный массив инициализируется нулями */
    unsigned char in_buffer[8] = {0};
    // Объявление массива для хранения генерируемой псевдослучайной последовательности.
    unsigned char* output = (unsigned char*) malloc(bytes * sizeof(unsigned char));
    // Объявление массива для хранения хэш-значений.
    uint8_t out_uint[8] = {0};

    // Объявление переменной для хранения числа итераций работы хэш-функции.
    int number_of_iterations;
    // Вычисление числа итераций работы хэш-функции.
    if (bytes % 8 == 0) {
        number_of_iterations = bytes / 8;
    } else {
        number_of_iterations = (bytes / 8) + 1;
    }

    /* В данном блоке кода вычисленное число раз запускается хэш-функция,
    результат работы записывается в массив.
    В качестве входного сообщения на каждой итерации хэш-функции передаётся
    хэш-значение, вычисленное на предыдущей итерации.
    В самой первой итерации на вход подаётся сообщение, состоящее из нулей */
    for (int i = 0, j = 0; i < number_of_iterations; i++, j += 8) {
        siphash(in_buffer, 8, key, out_uint);
        memcpy(in_buffer, (unsigned char*) out_uint, 8);
        /* в последней итерации работы хэш-функции могут быть выработаны
        лишние байты псевдослучайной последовательности. Такие байты
        отбрасываются */
        if (i == number_of_iterations - 1 && bytes % 8 != 0) {
            memcpy(&output[j], in_buffer, bytes % 8);
            break;
        }
        memcpy(&output[j], in_buffer, 8);
    }

    /* Запись в файл "result.txt" в текущей директории (если файла не было,
     он создаётся, в противном случае - перезаписывается)
     сгенерированной последовательности */
    FILE *file = fopen("result.txt", "w");
    int results = fwrite(output, sizeof(unsigned char), bytes, file);
    // в случае невозможности записи в файл, в консоль выводится ошибка
    if (results == EOF) {
        printf("Error: cannot write to file");
        return -1;
    }
    // закрытие файла после записи
    fclose(file);
    // освобождение памяти
    free(output);
    return 0;
}