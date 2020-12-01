#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

FILE* fptr;
static float sample[5][1000000];

class File{
    public:
    
    static void getSample(const char* path)
    {
        char ch;
        int idx = 0, count = 0;
        char str[100];
        fptr = fopen(path, "r");
        memset(str, 0, 100);
        while((ch = fgetc(fptr)) != EOF){
            if(ch != '\n'){
                str[idx++] = ch;
            }
            else{
                idx = 0;
                float a, b, c, d, e;
                sscanf(str, "[%f, %f, %f, %f, %f]", &a, &b, &c, &d, &e);
                sample[0][count] = a;
                sample[1][count] = b;
                sample[2][count] = c;
                sample[3][count] = d;
                sample[4][count] = e;
                count++;
                memset(str, 0, 100);
            }
        }
    }

    static void writeWeigth(const char* path, float* weight, int length){
        fptr = fopen(path, "w+");

        for(int i = 0; i < length; i++){
            fprintf(fptr, "%f\n", weight[i]);
        }

        fclose(fptr);
    }

    // static float* loadWeigth(const char* path){
        
    // }
};