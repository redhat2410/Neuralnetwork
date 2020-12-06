#ifndef __NEURAL__
#define __NEURAL__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
// #include <cstdlib>

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
    Neural(float* input, int n_input, int n_output);
    Neural(int n_input, int n_output);

    //Hàm input thực hiện truyền dữ liệu ngõ vào của mạng
    void input_data(float* data);
    //Hàm propagation
    float* propagation(void);
    //Hàm back_propagation
    float** back_propagation(float* output, float* target);
    float** back_propagation(float* target);
    //Hàm getWeigth
    float** getWeigth(void);
    //Hàm setWeigth
    void setWeigth(float** weigth);
    //void dispose giải phóng vùng nhớ con trỏ
    void dispose(void);

    private:
    //Hàm init weigth
    void _initWeigth(void);
    //Hàm f_rand cho phép tạo giá trị số thực ngẫu nhiên
    float _f_rand(float min, float max);
    //Các biến local được sử dụng trong chương trình
    float* _input;
    float* _output;
    float** _weigth;
    int _n_input;
    int _n_output;
};

class NeuralwithHidden{
    public:
    NeuralwithHidden(float input);
    NeuralwithHidden();

    float propagation(void);

    void back_propagation(float output, float target);

    void setWeigth(float* weigth_hidden, float* weigth_output);
    
    void setInput(float input);

    float* _weigth_hidden;
    float* _weigth_output;
    private:
    void _initWeigth(void);
    float _f_rand(float min, float max);
    float _input;

    float* _hidden;
};


#endif