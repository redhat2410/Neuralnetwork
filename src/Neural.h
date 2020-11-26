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
    Neural(float* input, float* weigth, int n_input, int n_output);
    //Hàm propagation
    float* propagation(void);
    //Hàm back_propagation
    float* back_propagation(float* output, float* target);
    private:
    float* _input;
    float* _weigth;
    int _n_input;
    int _n_output;
};


#endif