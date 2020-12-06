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

void Neural::dispose(void){
    free(this->_input);
    free(this->_output);
    for(int i = 0; i < this->_n_output; i++) free(this->_weigth[i]);
}


/**************** Class NeuralwithHidden ****************/

NeuralwithHidden::NeuralwithHidden(float input){
    this->_input = input;

    this->_initWeigth();
}

NeuralwithHidden::NeuralwithHidden(void){ 
    this->_initWeigth();
}

void NeuralwithHidden::setInput(float input){
    this->_input = input;
}

void NeuralwithHidden::_initWeigth(void){
    this->_weigth_hidden = (float*)malloc(2 * sizeof(float));
    this->_weigth_output = (float*)malloc(2 * sizeof(float));

    // printf("init weigth\n");
    for(int i = 0; i < 2; i++){
        this->_weigth_hidden[i] = this->_f_rand(0, 1);
        // printf("%f ", this->_weigth_hidden[i]);
    }
    // printf("\n");
    for(int i = 0; i < 2; i++){
        this->_weigth_output[i] = this->_f_rand(0, 1);
        // printf("%f ", this->_weigth_output[i]);
    }
    // printf("\n");
}

float NeuralwithHidden::_f_rand(float min, float max){
    float scale = (float)(rand()) / (float)(RAND_MAX);
    return min + scale * (max - min);
}

float NeuralwithHidden::propagation(void){
    Node node_hidden_1 = Node(1);
    Node node_hidden_2 = Node(1);
    Node node_output = Node(2);

    this->_hidden = (float*)malloc(2 * sizeof(float));

    float hdd_1 = node_hidden_1.activate(&this->_input, &this->_weigth_hidden[0]);
    float hidden_1 = node_hidden_1.transfer(hdd_1);

    float hdd_2 = node_hidden_2.activate(&this->_input, &this->_weigth_hidden[1]);
    float hidden_2 = node_hidden_2.transfer(hdd_2);

    float hidden[2] = { hidden_1, hidden_2 };

    memcpy(this->_hidden, hidden, 2 * sizeof(float));

    float out = node_output.activate(hidden, this->_weigth_output);
    float output = node_output.transfer(out);

    return output;
}

void NeuralwithHidden::back_propagation(float output, float target){
    Node node_out = Node(2);
    Node node_hidden_1 = Node(1);
    Node node_hidden_2 = Node(1);
    
    float gama_out = node_out.transfer_deriactive(output) * (target - output);
    
    this->_weigth_output[0] = this->_weigth_output[0] + gama_out * this->_hidden[0];
    this->_weigth_output[1] = this->_weigth_output[1] + gama_out * this->_hidden[1];

    float gama_hidden_1 = node_hidden_1.transfer_deriactive(this->_hidden[0]) * gama_out * this->_weigth_output[0];
    float gama_hidden_2 = node_hidden_1.transfer_deriactive(this->_hidden[0]) * gama_out * this->_weigth_output[0];

    this->_weigth_hidden[0] = this->_weigth_hidden[0] + gama_hidden_1 * this->_input;
    this->_weigth_hidden[1] = this->_weigth_hidden[1] + gama_hidden_2 * this->_input;


    // printf("new weigth\n");

    // for(int i = 0; i < 2; i++) printf("%f ", this->_weigth_hidden[i]);
    // printf("\n");
    // for(int i = 0; i < 2; i++) printf("%f ", this->_weigth_output[i]);
    // printf("\n");
}

void NeuralwithHidden::setWeigth(float* weigth_hidden, float* weigth_output){
    memcpy(this->_weigth_hidden, weigth_hidden, 2 * sizeof(float));
    memcpy(this->_weigth_output, weigth_output, 2 * sizeof(float));
}

