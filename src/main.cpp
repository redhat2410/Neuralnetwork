#include <stdio.h>
#include "Neural.h"
#include "handleFile.h"

#define TOTAL_SIZE  1000000

int main(void){
    File::getSample("../samples/samples.csv");

    Node node = Node(2);
    // float input[2] = { 0.05f, 0.1f };
    float weigth_hidden_1[2] = { 0.001f, 0.005f};
    float weigth_hidden_2[2] = { 0.001f, 0.005f};
    float weigth_output[2] = { 0.001f, 0.005f};
    float target = 1;

    int n_input = 2;
    int n_output = 1;

    uint16_t per = TOTAL_SIZE / 100;

    for(int i = 0; i < TOTAL_SIZE; i++){
        float input[2] = { sample[0][i], sample[1][i] };
        float target[3] =  { sample[2][i], sample[3][i], sample[4][i] };

        Neural neural = Neural(input, weigth_hidden_1, weigth_hidden_2, weigth_output, 2);

        float output = neural.propagation_level2();

        neural.back_propagation_level2(output, target[0]);

        memcpy(weigth_hidden_1, neural.weigth_hidden_1, 2 * sizeof(float));
        memcpy(weigth_hidden_2, neural.weigth_hidden_2, 2 * sizeof(float));
        memcpy(weigth_output, neural.weigth_output, 2 * sizeof(float));


        if(per != 0){
            if((i % per) == 0){
                printf(".....................[%d%]\n", i / per);
            }
        }

    }

    // printf("Write file \"weight.data\" ...");
    // File::writeWeigth("weigth.data", weigth, n_input * n_output);
    // printf(" Done.\n");

    printf("====TESTING====\n");
    int option = 0;
    printf("1. Test\n");
    printf("2. Exit\n");
    printf("Enter option (1/2): ");
    scanf("%d", &option);

    float input[2] = { 0.05f, 0.1f };

    printf("Weigth_hidden 1: %f %f\n", weigth_hidden_1[0], weigth_hidden_1[1]);
    printf("Weigth_hidden 2: %f %f\n", weigth_hidden_2[0], weigth_hidden_2[1]);
    printf("Weigth output: %f %f\n", weigth_output[0], weigth_output[1]);



    while(option == 1){
        for(int i = 0; i < 2; i++){
            printf("Input %d: ", i + 1);
            scanf("%f", &input[i]);
        }

        Neural neural = Neural(input, weigth_hidden_1, weigth_hidden_2, weigth_output, 2);

        float t_output = neural.propagation_level2();

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


    // float input[2] = { 0.05f, 0.1f };
    // float weigth_hidden_1[2] = { 0.001f, 0.005f};
    // float weigth_hidden_2[2] = { 0.001f, 0.005f};
    // float weigth_output[2] = { 0.001f, 0.005f};

    // float target = 1.0f;

    // Neural neural = Neural(input, weigth_hidden_1, weigth_hidden_2, weigth_output, 2);
    
    // float output = neural.propagation_level2();

    // printf("%f\n", output);

    // neural.back_propagation_level2(output, target);

    // printf("Weigth_hidden 1: %f %f\n", neural.weigth_hidden_1[0], neural.weigth_hidden_1[1]);
    // printf("Weigth_hidden 2: %f %f\n", neural.weigth_hidden_2[0], neural.weigth_hidden_2[1]);
    // printf("Weigth output: %f %f\n", neural.weigth_output[0], neural.weigth_output[1]);


    return 0;
}