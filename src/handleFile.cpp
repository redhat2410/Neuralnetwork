#include "handleFile.h"

float** File::sample = NULL;
int File::COLUMN = 0;
int File::ROW = 0;

FILE* fptr = NULL;

void File::getSample(const char* path, int column, int row)
{
    char ch;
    int idx = 0, count = 0, _column = 0;
    char str[100];
    fptr = fopen(path, "r");
    memset(str, 0, 100);

    File::COLUMN = column;
    File::ROW = row;

    //khởi tạo mảng theo column và row

    File::sample = (float**)malloc(row * sizeof(float*));
    for(int i = 0; i < row; i++)
        File::sample[i] = (float*)malloc(column * sizeof(float));
    

    while((ch = fgetc(fptr)) != EOF){
        if(ch != '\n'){
            str[idx++] = ch;
            _column = 0;
        }
        else{
            idx = 0;

            char* temp = (char*)malloc( (strlen(str) - 2) * sizeof(char));
            memcpy(temp, &str[1], strlen(str) - 2);

            char* token = strtok(temp, ",");
            for(int i = 0; i < column; i++){
                if(token != NULL){
                    File::sample[count][i] = atof(token);
                    token = strtok(NULL, ",");
                }
            }

            free(token);
            free(temp);
            count++;

            if(count >= row) break;

            memset(str, 0, 100);
        }
    }
    fclose(fptr);
}

void File::writeWeigth(const char* path, float* weight, int length){
    fptr = fopen(path, "w+");

    for(int i = 0; i < length; i++){
        fprintf(fptr, "%f ", weight[i]);
    }
    fclose(fptr);
}

void File::writeWeigth(const char* path, float** weigth, int row, int column){
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

float** File::loadWeigth(const char* path, int row, int column){
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

void File::makeColor(int percent){
    for(int i = 0; i < percent / 2; i++) printf(".");
    printf("[%d]\n", percent + 1);
}