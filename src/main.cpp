#include <stdio.h>
#include "Neural.h"
#include "handleFile.h"

#define TOTAL_SIZE  1000

int main(void){
    File::getSample("../samples/samples.csv");

    Node node = Node(2);
    float input[2] = { 0.05f, 0.1f };
    float weigth[6] = { 0.001f, 0.005f, 0.011f, 0.015f, 0.101f, 0.105f };
    float target = 1;


    for(int i = 0; i < TOTAL_SIZE; i++){
        float input[2] = { sample[0][i], sample[1][i] };
        float target[3] =  { sample[2][i], sample[3][i], sample[4][i] };

        printf("Target: ");
        for(int i = 0; i < 3; i++){
            printf("%f ", target[i]);
        }
        printf("\n\n");

        Neural neural = Neural(input, weigth, 2, 3);

        float* output = neural.propagation();

        float* new_weigth = neural.back_propagation(output, target);

        memcpy(weigth, new_weigth, 6 * sizeof(float));

        if((i % 100) == 0){
            printf(".....................[%d%]\n", i / 100);
        }

    }

    printf("====TESTING====\n");
    int option = 0;
    printf("1. Test\n");
    printf("2. Exit\n");
    printf("Enter option (1/2): ");
    scanf("%d", &option);

    while(option == 1){
        for(int i = 0; i < 2; i++){
            printf("Input %d: ", i + 1);
            scanf("%f", &input[i]);
        }

        Neural neural = Neural(input, weigth, 2, 3);

        float* t_output = neural.propagation();

        printf("Output: %f\t%f\t%f\n", t_output[0], t_output[1], t_output[2]);

        printf("1. Test\n");
        printf("2. Exit\n");
        printf("Enter option (1/2): ");
        scanf("%d", &option);

    }
    return 0;
}