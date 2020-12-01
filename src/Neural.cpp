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

Neural::Neural(float* input, float* weigth_hidden_1, float* weigth_hidden_2, float* weigth_output, int n_input){
    this->_input = input;
    this->_weigth_hidden_1 = weigth_hidden_1;
    this->_weigth_hidden_2 = weigth_hidden_2;
    this->_weigth_output = weigth_output;
    this->_n_input = n_input;
    this->_n_hidden = 2;
}

// float* Neural::propagation(void){

//     float* output = (float*)malloc(this->_n_output * sizeof(float));
//     for(int i = 0; i < this->_n_output; i++){
//         Node node = Node(this->_n_input);

//         float* weigth_branch = (float*)malloc(this->_n_input * sizeof(float));
//         int step = i * this->_n_input;
//         memcpy(weigth_branch, &this->_weigth[step], this->_n_input * sizeof(float));
//         float activation = node.activate(this->_input, weigth_branch);

//         output[i] = node.transfer(activation);

//     }
//     return output;
// }

// float* Neural::back_propagation(float* output, float* target){
//     float* new_weigth;

//     for(int i = 0; i < this->_n_output; i++){
//         Node node = Node(this->_n_input);

//         new_weigth = (float*)malloc((this->_n_input * this->_n_output) * sizeof(float));

//         float gama = node.transfer_deriactive(output[i]) * (target[i] - output[i]);

//         for(int j = 0; j < this->_n_input; j++){
//             int step = (i * this->_n_input) + j;
//             new_weigth[step] = this->_weigth[step] + (gama * this->_input[j]);
            
//         }
//     }

//     return new_weigth;
// }




float Neural::propagation(void){
    Node node = Node(this->_n_input);

    float activation = node.activate(this->_input, this->_weigth);

    return node.transfer(activation);
}

float* Neural::back_propagation(float output, float target){
    float* new_weigth = (float*)malloc( this->_n_input * sizeof(float) );

    Node node = Node(this->_n_input);

    float gama = node.transfer_deriactive(output) * (target - output);

    for(int i = 0; i < this->_n_input; i++){
        new_weigth[i] = this->_weigth[i] + (gama * this->_input[i]);
    }

    return new_weigth;
}

// float Neural::propagation_level2(void){
//     Node hidden_1 = Node(this->_n_input);
//     Node hidden_2 = Node(this->_n_input);
//     Node output = Node(this->_n_hidden);

//     float act_hidden_1 = hidden_1.activate(this->_input, this->_weigth_hidden_1);
//     float act_hidden_2 = hidden_2.activate(this->_input, this->_weigth_hidden_2);

//     float trs_hidden_1 = hidden_1.transfer(act_hidden_1);
//     float trs_hidden_2 = hidden_2.transfer(act_hidden_2);

//     this->_hidden_1_activation = trs_hidden_1;
//     this->_hidden_2_activation = trs_hidden_2;

//     float hidden[2] = { trs_hidden_1, trs_hidden_2 };

//     float act_output = output.activate(hidden, this->_weigth_output);
//     float trs_output = output.transfer(act_output);

//     return trs_output;
// }

// void Neural::back_propagation_level2(float output, float target){
//     float* n_weigth_hidden_1 = (float*)malloc(this->_n_input * sizeof(float));
//     float* n_weigth_hidden_2 = (float*)malloc(this->_n_input * sizeof(float));
//     float* n_weigth_output   = (float*)malloc(this->_n_hidden * sizeof(float));

//     Node node_output = Node(this->_n_hidden);
//     Node node_hidden_1 = Node(this->_n_input);
//     Node node_hidden_2 = Node(this->_n_input);

//     float gama_output = node_output.transfer_deriactive(output) * (target - output);

//     //calc new weigth output 
//     n_weigth_output[0] = this->_weigth_output[0] + ( gama_output * this->_hidden_1_activation);
//     n_weigth_output[1] = this->_weigth_output[1] + ( gama_output * this->_hidden_2_activation);


//     float gama_weigth_hidden_1 = node_hidden_1.transfer_deriactive(this->_hidden_1_activation) * gama_output * n_weigth_output[0];
//     float gama_weigth_hidden_2 = node_hidden_2.transfer_deriactive(this->_hidden_2_activation) * gama_output * n_weigth_output[1];
    
//     //calc new weigth hidden 1
//     for(int i = 0; i < this->_n_input; i++){
//         n_weigth_hidden_1[i] = this->_weigth_hidden_1[i] + (gama_weigth_hidden_1 * this->_input[i]);
//     }

//     //calc new weigth hidden 2
//     for(int i = 0; i < this->_n_input; i++){
//         n_weigth_hidden_2[i] = this->_weigth_hidden_2[i] + (gama_weigth_hidden_2 * this->_input[i]);
//     }

//     this->weigth_hidden_1 = n_weigth_hidden_1;
//     this->weigth_hidden_2 = n_weigth_hidden_2;
//     this->weigth_output = n_weigth_output;
// }