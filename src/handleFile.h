#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


// static float sample[5][1000000];


class File{
    public:
    static float** sample;
    static int COLUMN;
    static int ROW;
    static void getSample(const char* path, int column, int row);

    static void writeWeigth(const char* path, float* weight, int length);

    static void writeWeigth(const char* path, float** weigth, int row, int column);

    static float** loadWeigth(const char* path, int row, int column);

    static void makeColor(int percent);
};
