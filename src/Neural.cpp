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

Neural::Neural(float* input, float** weigth, int n_input, int n_output){
    this->_input = input;
    this->_weigth = weigth;
    this->_n_input = n_input;
    this->_n_output = n_output;
}

float Neural::propagation(void){
    Node node = Node(this->_n_input);

    float activation = node.activate(this->_input, this->_weigth);

    float output = node.transfer(activation);

    return output;
}

float* Neural::back_propagation( float output, float target){
    float* new_weigth;
    Node node = Node(this->_n_input);
    
    new_weigth = (float*)malloc(this->_n_input * sizeof(float));

    float gama = node.transfer_deriactive(output) * (target - output);

    for(int i = 0; i < this->_n_input; i++){
        new_weigth[i] = this->_weigth[i] + ( gama * this->_input[i] );

    }
    return new_weigth;
}