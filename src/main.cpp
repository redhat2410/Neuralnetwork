#include <stdio.h>
#include "Neural.h"

int main(void){
    float input[] = { 2.3, 3.1};
    float weight[] = { 1.2, 1.5};

    Node node = Node(2);
    printf("%f\n", node.calc(input, weight));
    return 0;
}