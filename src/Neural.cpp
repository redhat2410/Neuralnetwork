#include "Neural.h"

Node::Node(void) { }

Node::Node(int input){
    this->_input = input;
}

float Node::activate(float* input, float* weigth){
    float activation = 0.0f;
    for(int i = 0; i < this->_input; i++) activation += (input[i] * weigth[i]);

    return activation;
}

float Node::transfer(float activation){
    return 1.0f / (1.0f + exp(-activation));
}

float Node::transfer_deriactive(float output){
    return output * (1.0f - output);
}

Neural::Neural(float* input, float* weigth, int n_input, int n_output){
    this->_input = input;
    this->_weigth = weigth;
    this->_n_input = n_input;
    this->_n_output = n_output;
}

float* Neural::propagation(void){

    float* output = (float*)malloc(this->_n_output * sizeof(float));

    for(int i = 0; i < this->_n_output; i++){
        Node node = Node(this->_n_input);

        float* weigth_branch = (float*)malloc(this->_n_input * sizeof(float));
        int step = i * this->_n_input;
        printf("%d ", step);
        memcpy(weigth_branch, &this->_weigth[step], this->_n_input * sizeof(float));
        printf("%f %f\n",weigth_branch[0], weigth_branch[1]);
        float activation = node.activate(this->_input, weigth_branch);

        output[i] = node.transfer(activation);

    }
    printf("\n");
    return output;
}

float* Neural::back_propagation(float* output, float* target){
    float* new_weigth;

    for(int i = 0; i < this->_n_output; i++){
        Node node = Node(this->_n_input);

        new_weigth = (float*)malloc((this->_n_input * this->_n_output) * sizeof(float));

        float gama = node.transfer_deriactive(output[i]) * (target[i] - output[i]);

        for(int j = 0; j < this->_n_input; j++){
            int step = (i * this->_n_input) + j;
            printf("%d ", step);
            new_weigth[step] = this->_weigth[step] + (gama * this->_input[i]);
            
        }
        printf("\n=======\n\n");
    }

    return new_weigth;
}