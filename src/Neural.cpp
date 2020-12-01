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

Neural::Neural(float* input, int n_input, int n_output){
    srand(time(NULL));
    this->_input = input;
    this->_n_input = n_input;
    this->_n_output = n_output;

    this->_initWeigth();
}

Neural::Neural(int n_input, int n_output){
    srand(time(NULL));
    this->_n_input = n_input;
    this->_n_output = n_output;

    this->_initWeigth();
}

void Neural::input_data(float* data) {
    this->_input = (float*)malloc(this->_n_input * sizeof(float));
    memcpy(this->_input, data, this->_n_input * sizeof(float));
}

void Neural::_initWeigth(void){
    //Hàm khởi tạo trọng số trong mạng neural
    //số weigth cần khởi tạo phụ thuộc vào thông sô n_input và n_output
    this->_weigth = (float*)malloc(this->_n_input * sizeof(float));

    for(int i = 0; i < this->_n_input; i++) this->_weigth[i] = this->_f_rand(0.0f, 1.0f);
}

float* Neural::getWeigth(void) { return this->_weigth; }

void Neural::setWeigth(float* weigth){
    memcpy(this->_weigth, weigth, this->_n_input * sizeof(float));
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

float Neural::_f_rand(float min, float max){
    float scale = (float) (rand()) / (float) (RAND_MAX);
    return min + scale * (max - min);
}