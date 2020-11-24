#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

FILE* fptr;
static float sample[3][1000];

class File{
    public:
    
    static void getSample(const char* path)
    {
        char ch;
        int idx = 0, count = 0;
        char str[50];
        fptr = fopen(path, "r");
        memset(str, 0, 50);
        while((ch = fgetc(fptr)) != EOF){
            if(ch != '\n'){
                str[idx++] = ch;
            }
            else{
                idx = 0;
                float a, b, c;
                sscanf(str, "[%f, %f, %f]", &a, &b, &c);
                sample[0][count] = a;
                sample[1][count] = b;
                sample[2][count] = c;
                count++;
                memset(str, 0, 50);
            }
        }
    }
};