#include <stdio.h>
#include "Neural.h"
#include "handleFile.h"

int main(void){
    // float input[] = { 2.3, 3.1};
    float w_in[] = { 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    float w_out[] = { 0.1, 0.1, 0.1};

    // Neural neural = Neural(2, 3);
    // float out = neural.propagation(input, w_in, w_out);
    // neural.backpropagation(w_in, w_out, input, 1.0);

    // for(int i = 0; i < 6; i++) printf("%f ", w_in[i]);
    // printf("\n");
    // for(int i = 0; i < 3; i++) printf("%f ", w_out[i]);
    // printf("\n");
    File::getSample("../samples/sample_larger.csv");
    Neural neural = Neural(2, 3);
    for(int i = 0; i < 1000; i++){
        float input[2] = { sample[0][i], sample[1][i] };
        for(int step = 0; step < 1; step++){
            neural.learning(input, w_in, w_out, sample[2][i]);
            printf(".");
        }
        printf("[%1.f]\n", (float)(i/(float)1000) * 100);
    }
    float data[2];
    for(int i = 0; i < 2; i++){
        printf("test data %d: ", i);
        scanf("%f", &data[i]);
    }
    float out = neural.propagation(data, w_in, w_out);
    printf("Output: %f\n", out);

    for(int i = 0; i < 6; i++) printf("%f ", w_in[i]);
    printf("\n");
    for(int i = 0; i < 3; i++) printf("%f ", w_out[i]);
    printf("\n");

    return 0;
}