#ifndef __NEURAL__
#define __NEURAL__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


class Node{
    public:
    /**
     * contructor class Node
     * @param num   number input of network
    */
    Node(uint8_t num);
    /**
     * Function calc calculate node of network with
     *  output <=> O = f((I1 * w1) + (I2 * w2))
    */
    float calc(float* input, float* weigth);
    void calc_back(float* weigth, float output, float target);
    private:
    uint8_t _num;
    float* _input;
    float* _weigth;
    float calc_sigmoid(float x);
    float calc_derisigmoid(float x, float target);
};

class Neural : Node{

};

#endif