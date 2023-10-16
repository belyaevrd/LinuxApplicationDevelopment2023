#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    long M, N, S;
    switch(argc) {
    case 1: 
        printf("Программа-генератор арифметической прогрессии, принимающую от одного до трёх параметров:\n"
                "С одним параметром N — выводит в столбик последовательность [0, 1, … N-1]\n"
                "С двумя — M, N — последовательность [M, M+1, … N-1]\n"
                "С тремя — M, N, S — последовательность [M, M+S, M+2S, … N-1]\n");
        exit(EXIT_SUCCESS); 
    case 2:
        M = 0;
        N = strtol(argv[1], NULL, 10);
        S = 1;
        break;
    case 3:
        M = strtol(argv[1], NULL, 10);
        N = strtol(argv[2], NULL, 10);
        S = 1;
        break;
    default:
        M = strtol(argv[1], NULL, 10);
        N = strtol(argv[2], NULL, 10);
        S = strtol(argv[3], NULL, 10);
        break;
    }
    if (errno) {
        abort();
    }
    for (long i = M; i < N; i += S) {
        printf("%ld ", i);
    }
    printf("\n");
}
