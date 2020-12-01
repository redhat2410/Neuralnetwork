#ifndef __NEURAL__
#define __NEURAL__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

class Node{
    public:
    //Hàm tạo của lớp Node
    Node(void);
    Node(int input = 2);
    //hàm activate 
    float activate(float* input, float* weigth);
    //hàm transfer
    float transfer(float activation);
    //hàm transfer_deriactive
    float transfer_deriactive(float output);
    
    private:
    int _input;

};

class Neural{
    public:
    //Hàm tạo của lớp Neural
    // Neural(float* input, float* weigth, int n_input, int n_output);
    Neural(float* input, float* weigth, int n_input, int n_ouptut);
    Neural(float* input, float* weigth_hidden_1, float* weigth_hidden_2, float* weigth_output, int n_input);

    //Hàm propagation
    // float* propagation(void);
    float propagation(void);
    float propagation_level2(void);

    //Hàm back_propagation
    // float* back_propagation(float* output, float* target);
    float* back_propagation(float output, float target);
    void back_propagation_level2(float output, float target);

    float* weigth_hidden_1;
    float* weigth_hidden_2;
    float* weigth_output;

    private:
    float* _input;
    float* _weigth;
    float* _weigth_hidden_1;
    float* _weigth_hidden_2;
    float* _weigth_output;
    int _n_input;
    int _n_output;
    int _n_hidden;

    float _hidden_1_activation;
    float _hidden_2_activation;
};


#endif