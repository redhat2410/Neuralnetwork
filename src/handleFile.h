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
        fclose(fptr);
    }

    static void writeWeigth(const char* path, float* weight, int length){
        fptr = fopen(path, "w+");

        for(int i = 0; i < length; i++){
            fprintf(fptr, "%f ", weight[i]);
        }
        fclose(fptr);
    }

    static void writeWeigth(const char* path, float** weigth, int row, int column){
        fptr = fopen(path, "w+");

        for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
                if(j == column - 1) fprintf(fptr, "%f", weigth[i][j]);
                else fprintf(fptr, "%f,", weigth[i][j]);
            }
            fprintf(fptr, "\n");
        }
        fclose(fptr);
    }

    static float** loadWeigth(const char* path, int row, int column){
        char ch;
        int idx = 0, count = 0;
        int _row = 0;
        char str[100];
        fptr = fopen(path, "r");
        memset(str, 0, 100);

        float** ret = (float**)malloc(row * sizeof(float*));
        for(int i = 0; i < row; i++) ret[i] = (float*)malloc(column * sizeof(float));
        
        if(fptr == NULL) {
            printf("Error! Could not open file\n");
            exit(-1);
        }

        while((ch = fgetc(fptr)) != EOF){
            if(ch != '\n'){
                str[idx++] = ch;
            }
            else{
                idx = 0;
                char* token = strtok(str, ",");
                for(int i = 0; i < column; i++){
                    if(token != NULL){
                        ret[_row][i] = atof(token);
                        token = strtok(NULL, ",");
                    }
                }
                free(token);
                _row++;
                memset(str, 0, 100);
            }
        }

        return ret;
    }

    static void makeColor(int percent){
        for(int i = 0; i < percent / 2; i++) printf(".");
        printf("[%d]\n", percent + 1);
    }
};