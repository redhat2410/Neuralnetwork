#include "Neural.h"

Node::Node(uint8_t num){
    this->_num = num;
}

float Node::calc_sigmoid(float x){
    return 1 / (1 + exp(-x));
}

float Node::calc_derisigmoid(float x){
    return this->calc_sigmoid(x) * (1 - this->calc_sigmoid(x));
}

float Node::calc(float* input, float* weigth){
    float sum = 0;
    for(int i = 0; i < this->_num; i++){
        sum += input[i] * weigth[i];
    }
    return this->calc_sigmoid(sum);
}

float Node::calc_back(float* weigth, float* input, float output, float target, uint8_t sel){
    //when sel by 1 then calculate back for output else for hidden layer.
    float theta = (sel == 1) ? this->calc_derisigmoid(output) * (output - target) :
                        this->calc_derisigmoid(output) * target; // target = gama * w
    for(int i = 0; i < this->_num; i++)
        weigth[i] = weigth[i] + (theta *  input[i]);
    return theta;
}


Neural::Neural(int input, int hidden){
    this->_nodeInput = input;
    this->_nodeHidden = hidden;
}

float Neural::propagation(float* input, float* w_in, float* w_out){
    this->_Hidden = (float*)malloc(this->_nodeHidden * sizeof(float));
    //thuc hien tinh toan o lop an
    for(int i = 0; i < this->_nodeHidden; i++){
        float* t_weigth = (float*)malloc(this->_nodeInput * sizeof(float));
        Node nodehidden = Node(this->_nodeInput);
        memcpy(t_weigth, &w_in[i * this->_nodeInput], this->_nodeInput * sizeof(float));
        this->_Hidden[i] = nodehidden.calc(input, t_weigth);
    }
    //thuc hien tinh toan o lop ngo ra
    Node nodeOutput = Node(this->_nodeHidden);
    this->_Output = nodeOutput.calc(this->_Hidden, w_out);
    return this->_Output;
}

void Neural::backpropagation(float* w_in, float* w_out, float* input, float target){
    Node bk_out = Node(this->_nodeHidden);
    // lan truyen nguoc cho lop output
    float gama = bk_out.calc_back(w_out, this->_Hidden, this->_Output, target, 1);
    // thuc hien lan truyen nguoc cho lop hidden
    for(int i = 0; i < this->_nodeHidden; i++){
        float* t_weigth = (float*)malloc(this->_nodeInput * sizeof(float));
        memcpy(t_weigth, &w_in[i * this->_nodeInput], sizeof(float) * this->_nodeInput);
        Node bk_hidden = Node(this->_nodeInput);
        (void)bk_hidden.calc_back(t_weigth, input, this->_Hidden[i], gama * w_out[i], 0);
        memcpy(&w_in[i * this->_nodeInput], t_weigth, sizeof(float) * this->_nodeInput);
    }
    this->_w_in = (float*)malloc(this->_nodeInput * this->_nodeHidden * sizeof(float));
    this->_w_out = (float*)malloc(this->_nodeHidden * sizeof(float));

    memcpy(this->_w_in, w_in, (this->_nodeHidden * this->_nodeInput) * sizeof(float));
    memcpy(this->_w_out, w_out, this->_nodeHidden * sizeof(float));
}

void Neural::learning(float* input, float* w_in, float* w_out, float target){
    this->propagation(input, w_in, w_out);
    this->backpropagation(w_in, w_out, input, target);
}