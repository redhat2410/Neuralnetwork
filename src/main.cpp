#include <stdio.h>
#include "Neural.h"
#include "handleFile.h"

int main(void){
    // float input[] = { 2.3, 3.1};
    // float w_in[] = { 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    // float w_out[] = { 0.1, 0.1, 0.1};

    // Neural neural = Neural(2, 3);
    // float out = neural.propagation(input, w_in, w_out);
    // neural.backpropagation(w_in, w_out, input, 1.0);

    // for(int i = 0; i < 6; i++) printf("%f ", w_in[i]);
    // printf("\n");
    // for(int i = 0; i < 3; i++) printf("%f ", w_out[i]);
    // printf("\n");
    File::getSample("../samples/sample_larger.csv");
    // Neural neural = Neural(2, 3);
    // for(int i = 0; i < 1000; i++){
    //     float input[2] = { sample[0][i], sample[1][i] };
    //     for(int step = 0; step < 1; step++){
    //         neural.learning(input, w_in, w_out, sample[2][i]);
    //         printf(".");
    //         for(int i = 0; i < 6; i++) printf("%f ", w_in[i]);
    //         printf("\n");
    //         for(int i = 0; i < 3; i++) printf("%f ", w_out[i]);
    //         printf("\n\n\n");
    //     }
    //     printf("[%1.f]\n", (float)(i/(float)1000) * 100);
    // }
    // float data[2];
    // for(int i = 0; i < 2; i++){
    //     printf("test data %d: ", i);
    //     scanf("%f", &data[i]);
    // }
    // float out = neural.propagation(data, w_in, w_out);
    // printf("Output: %f\n", out);

    Node node = Node(2);
    float input[2] = { 0.05f, 0.1f };
    float weigth[2] = { 0.001f, 0.005f };
    float target = 1;
    
    // Neural neural = Neural(input, weigth, 2);
    // float output = neural.propagation();
    // float* new_weigth = neural.back_propagation(output, target);

    for(int i = 0; i < 1000; i++){
        float input[2] = { sample[0][i], sample[1][i] };
        float target = sample[2][i];

        printf("%d.Input: %f\t%f\tTarget: %f\n", i, input[0], input[1], target);

        Neural neural = Neural(input, weigth, 2);

        float output = neural.propagation();

        float* new_weigth = neural.back_propagation(output, target);

        memcpy(weigth, new_weigth, 2 * sizeof(float));

        printf("%d. Output: %f\tTarget:%1.f\tUp.Weigth: %f\t%f\n", i, output, target, weigth[0], weigth[1]);
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

        Neural neural = Neural(input, weigth, 2);

        printf("Output: %f\n", neural.propagation());

        printf("1. Test\n");
        printf("2. Exit\n");
        printf("Enter option (1/2): ");
        scanf("%d", &option);

    }
    return 0;
}