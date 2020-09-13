#include "Neural.h"

Node::Node(uint8_t num){
    this->_num = num;
    this->_input = (float*)malloc(this->_num * sizeof(float));
    this->_weigth = (float*)malloc(this->_num * sizeof(float));
}

float Node::calc_sigmoid(float x){
    return 1 / (1 + exp(-x));
}

float Node::calc_derisigmoid(float x, float target){
    return this->calc_sigmoid(x) * (1 - this->calc_sigmoid(x)) * (x - target);
}

float Node::calc(float* input, float* weigth){
    float sum = 0;
    for(int i = 0; i < this->_num; i++){
        sum += input[i] * weigth[i];
    }
    return this->calc_sigmoid(sum);
}

void calc_back(float* weigth, float output, float target){
    
}