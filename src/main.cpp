#include <stdio.h>
#include "Neural.h"
#include "handleFile.h"

#define TOTAL_SIZE  1000000

int main(void){
    File::getSample("../samples/samples.csv");

    Node node = Node(2);
    // float input[2] = { 0.05f, 0.1f };
    float weigth[2] = { 0.001f, 0.005f};
    float target = 1;

    int n_input = 2;
    int n_output = 1;

    uint16_t per = TOTAL_SIZE / 100;

    for(int i = 0; i < TOTAL_SIZE; i++){
        float input[2] = { sample[0][i], sample[1][i] };
        float target[3] =  { sample[2][i], sample[3][i], sample[4][i] };

        Neural neural = Neural(input, weigth, n_input, n_output);

        float output = neural.propagation();

        float* new_weigth = neural.back_propagation(output, target[0]);

        memcpy(weigth, new_weigth, (n_input * n_output) * sizeof(float));


        if(per != 0){
            if((i % per) == 0){
                printf(".....................[%d%]\n", i / per);
            }
        }

    }

    printf("Write file \"weight.data\" ...");
    File::writeWeigth("weigth.data", weigth, n_input * n_output);
    printf(" Done.\n");

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

        Neural neural = Neural(input, weigth, 2, 3);

        float t_output = neural.propagation();

        // printf("Output: %f\t%f\t%f\n", t_output[0], t_output[1], t_output[2]);

        // printf("Output: ");
        // for(int i = 0; i < n_output; i++){
        //     printf("%f ", t_output[i]);
        // }
        printf("Output: %f\n", t_output);

        printf("1. Test\n");
        printf("2. Exit\n");
        printf("Enter option (1/2): ");
        scanf("%d", &option);

    }

    return 0;
}