#include <stdio.h>
#include "Neural.h"
#include "handleFile.h"

#define TOTAL_SIZE  1000000

int main(void){
    File::getSample("../samples/samples.csv");

    int n_input = 2;
    int n_output = 1;

    uint16_t per = TOTAL_SIZE / 100;

    Neural neural = Neural(2, 1);
    Neural neural_2 = Neural(2, 1);

    for(int i = 0; i < TOTAL_SIZE; i++){
        float input[2] = { sample[0][i], sample[1][i] };
        float target[3] =  { sample[2][i], sample[3][i], sample[4][i] };

        neural.input_data(input);
        neural_2.input_data(input);

        float output = neural.propagation();
        float output_2 = neural_2.propagation();

        float* new_weigth_1 = neural.back_propagation(output, target[0]);
        float* new_weigth_2 = neural_2.back_propagation(output_2, target[1]);

        neural.setWeigth(new_weigth_1);
        neural_2.setWeigth(new_weigth_2);

        if(per != 0){
            if((i % per) == 0){
                printf(".....................[%d%]\n", i / per);
            }
        }

    }

    // printf("Write file \"weight.data\" ...");
    // File::writeWeigth("weigth.data", weigth_1, n_input * n_output);
    // File::writeWeigth("weigth.data", weigth_2, n_input * n_output);
    // printf(" Done.\n");

    printf("====TESTING====\n");
    int option = 0;
    printf("1. Test\n");
    printf("2. Exit\n");
    printf("Enter option (1/2): ");
    scanf("%d", &option);

    float input[2] = { 0.05f, 0.1f };

    while(option == 1){
        for(int i = 0; i < 2; i++){
            printf("Input %d: ", i + 1);
            scanf("%f", &input[i]);
        }

        neural.input_data(input);
        neural_2.input_data(input);

        float t_output = neural.propagation();
        float t_output_2 = neural_2.propagation();

        printf("Output 1: %f\n", t_output);
        printf("Output 2: %f\n", t_output_2);

        printf("1. Test\n");
        printf("2. Exit\n");
        printf("Enter option (1/2): ");
        scanf("%d", &option);

    }

    return 0;
}