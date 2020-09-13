#ifndef __NEURAL__
#define __NEURAL__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
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
    float calc_back(float* weigth, float* input, float output, float target, uint8_t sel);
    private:
    uint8_t _num;
    float calc_sigmoid(float x);
    float calc_derisigmoid(float x);
};

class Neural{
    public:
    //so node trong moi lop
    Neural(int input, int hidden);
    /**
     * Hàm propagation thực hiện tình toán lan truyền thuận của mạng
     * @param input     tham số input của mạng
     * @param w_in   tham số  w_input là trong cho lớp input và lớp hidden
     * @param w_out  tham số  w_out là trong lớp hidden và lớp output
     * @return      Hàm trả về giá trị output của mạng
    */
    float propagation(float* input, float* w_in, float* w_out);
    /**
     * Hàm backpropagation thực hiện tính toán lan truyền ngược của mạng
     * @param w_in  Tham sô w_in là trọng số của lớp input và lớp hidden
     * @param w_out  tham số  w_out là trong lớp hidden và lớp output
     * @param input tham input cua mang
     * @param target muc tieu huong toi cua mang
    */
    void backpropagation(float* w_in, float* w_out, float* input, float target);
    /**
     * Hàm learning hàm có chức năng thực hiện việc học theo mục tiêu có sẳn target
     * @param input     dữ liệu ngõ vào của mảng
     * @param w_in      trọng số của lớp input với hidden
     * @param w_out     trọng số của lớp hidden với output
     * @param target    mục tiêu của việc học
    */
    void learning(float* input, float* w_in, float* w_out, float target);
    private:
    int _nodeInput;
    int _nodeHidden;
    float* _Hidden;
    float* _w_in;
    float* _w_out;
    float  _Output;
};

#endif