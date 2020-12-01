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
    this->_output = NULL;

    this->_initWeigth();
}

Neural::Neural(int n_input, int n_output){
    srand(time(NULL));
    this->_n_input = n_input;
    this->_n_output = n_output;

    this->_input = NULL;
    this->_output = NULL;

    this->_initWeigth();
}

void Neural::input_data(float* data) {
    this->_input = (float*)malloc(this->_n_input * sizeof(float));
    memcpy(this->_input, data, this->_n_input * sizeof(float));
}

void Neural::_initWeigth(void){
    //Hàm khởi tạo trọng số trong mạng neural
    //Cấp phát bộ nhớ cho mảng 2 chiều cho _weigth
    this->_weigth = (float**)malloc(this->_n_output * sizeof(float*)); //cấp phát bộ nhớ cho hàng
    //cấp phát bộ nhớ cho cột
    for(int i = 0; i < this->_n_output; i++)
        this->_weigth[i] = (float*)malloc(this->_n_input * sizeof(float));

    //Sau khi cấp phát bộ nhớ thành công thì khởi tạo dữ liệu ngẫu nhiên cho mảng

    for(int i = 0; i < this->_n_output; i++){
        for(int j = 0; j < this->_n_input; j++){
            this->_weigth[i][j] = this->_f_rand(0, 1);
        }
    }

}

float** Neural::getWeigth(void) { return this->_weigth; }

void Neural::setWeigth(float** weigth){
    for(int i = 0; i < this->_n_output; i++)
        memcpy(this->_weigth[i], weigth[i], this->_n_input * sizeof(float));
}

float* Neural::propagation(void){
    try{
        //cấp phát vùng nhớ cho output
        this->_output = (float*)malloc(this->_n_output * sizeof(float));
        //tính giá trị của các node ngõ ra theo hàm kích hoạt sigmoid
        for(int i = 0; i < this->_n_output; i++){
            Node node = Node(this->_n_input);

            float activation = node.activate(this->_input, this->_weigth[i]);

            this->_output[i] = node.transfer(activation);
        }
        return this->_output;
    }
    catch(const char* msg)
    {
        printf("%s", msg);
        return NULL;
    }
}

float** Neural::back_propagation(float* output, float* target){
    //Cấp phát bộ nhớ cho giá trị trọng số mới
    float** t_weigth = (float**)malloc(this->_n_output * sizeof(float*));

    for(int i = 0; i < this->_n_output; i++)
        t_weigth[i] = (float*)malloc(this->_n_input * sizeof(float));
    /****************************************/
    for(int i = 0; i < this->_n_output; i++){
        Node node = Node(this->_n_input);
        //thực hiện tính sai số error
        float gama = node.transfer_deriactive(output[i]) * (target[i] - output[i]);
        //cập nhật lại trọng số mới cho mạng
        for(int j = 0; j < this->_n_input; j++){
            t_weigth[i][j] = this->_weigth[i][j] + (gama * this->_input[j]);
        }
    }
    //copy dữ liệu
    for(int i = 0; i < this->_n_output; i++)
        memcpy(this->_weigth[i], t_weigth[i], this->_n_input * sizeof(float));
    
    return this->_weigth;
}

float** Neural::back_propagation(float* target){
    //Cấp phát bộ nhớ cho giá trị trọng số mới
    float** t_weigth = (float**)malloc(this->_n_output * sizeof(float*));

    for(int i = 0; i < this->_n_output; i++)
        t_weigth[i] = (float*)malloc(this->_n_input * sizeof(float));
    /****************************************/
    for(int i = 0; i < this->_n_output; i++){
        Node node = Node(this->_n_input);
        //thực hiện tính sai số error
        float gama = node.transfer_deriactive(this->_output[i]) * (target[i] - this->_output[i]);
        //cập nhật lại trọng số mới cho mạng
        for(int j = 0; j < this->_n_input; j++){
            t_weigth[i][j] = this->_weigth[i][j] + (gama * this->_input[j]);
        }
    }
    //copy dữ liệu
    for(int i = 0; i < this->_n_output; i++)
        memcpy(this->_weigth[i], t_weigth[i], this->_n_input * sizeof(float));
    
    return this->_weigth;   
}

float Neural::_f_rand(float min, float max){
    float scale = (float) (rand()) / (float) (RAND_MAX);
    return min + scale * (max - min);
}