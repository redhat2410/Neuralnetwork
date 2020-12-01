#include <stdio.h>
#include "Neural.h"
#include "handleFile.h"

#define TOTAL_SIZE  1000000

#define NUMBER_INPUT    2
#define NUMBER_OUTPUT   2

int main(void){
    File::getSample("../samples/samples.csv");

    int n_input = 2;
    int n_output = 1;

    uint16_t per = TOTAL_SIZE / 100;

    Neural neural = Neural(NUMBER_INPUT, NUMBER_OUTPUT);

    for(int i = 0; i < TOTAL_SIZE; i++){
        float input[2] = { sample[0][i], sample[1][i] };
        float target[3] =  { sample[2][i], sample[3][i], sample[4][i] };

        neural.input_data(input);

        (void)neural.propagation();

        (void)neural.back_propagation(target);

        if(per != 0){
            if((i % per) == 0){
                printf(".....................[%d%]\n", i / per);
            }
        }

    }

    float** new_weigth = neural.getWeigth();

    printf("Write file \"weight.data\" ...");
    File::writeWeigth("weigth.data", new_weigth, NUMBER_OUTPUT, NUMBER_INPUT);
    printf(" Done.\n");

    printf("====TESTING====\n");
    int option = 0;
    printf("1. Test\n");
    printf("2. Exit\n");
    printf("Enter option (1/2): ");
    scanf("%d", &option);

    float input[2] = { 0.05f, 0.1f };



    while(option == 1){
        for(int i = 0; i < NUMBER_INPUT; i++){
            printf("Input %d: ", i + 1);
            scanf("%f", &input[i]);
        }
        Neural neural_test = Neural(NUMBER_INPUT, NUMBER_OUTPUT);

        neural_test.setWeigth(new_weigth);
        
        neural_test.input_data(input);

        float* t_output = neural_test.propagation();

        for(int i = 0; i < NUMBER_OUTPUT; i++){
            printf("Output %d: %f\n", i + 1, t_output[i]);
        }

        printf("1. Test\n");
        printf("2. Exit\n");
        printf("Enter option (1/2): ");
        scanf("%d", &option);

    }

    return 0;
}