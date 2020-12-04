import sys
import numpy as np
import random

def create_sample(path, num):
    

    t_list = []

    file = open(path, 'w')

    for i in range(num):

        a = random.randint(1, 100)

        t_list.append(a)

        count = 0
        for j in range(2, (int)(a / 2)):
            if a % j == 0:
               count = count + 1 
        
        result = 0
        if(count == 0) and (a != 1):
            result = 1
        else:
            result = 0;

        t_list.append(result)
        file.writelines(str(t_list) + '\n')
        t_list.clear()

if(len(sys.argv) > 1):
    pathname = sys.argv[1]
    totalsample = sys.argv[2]
    print("Create file: " + str(pathname))
    print("total size: " + str(totalsample))
    create_sample(sys.argv[1], int(sys.argv[2]))
    print("Done")