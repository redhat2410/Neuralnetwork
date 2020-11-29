import sys
import numpy as np
import random

def create_sample(path, num):


    t_list = []

    file = open(path, 'w')

    for i in range(num):

        a = random.uniform(0.001, 10)
        b = random.uniform(0.001, 10)

        t_list.append(a)
        t_list.append(b)
        lg = 0
        sm = 0
        eq = 0

        if a > b:
            lg = 1
            sm = 0
            eq = 0
        elif a < b:
            lg = 0
            sm = 1
            eq = 0
        elif a == b:
            lg = 0
            sm = 0
            eq = 1
        else:
            pass

        t_list.append(lg)
        t_list.append(sm)
        t_list.append(eq)
        file.writelines(str(t_list) + '\n')
        t_list.clear()

if(len(sys.argv) > 1):
    pathname = sys.argv[1]
    totalsample = sys.argv[2]
    print("Create file: " + str(pathname))
    print("total size: " + str(totalsample))
    create_sample(sys.argv[1], int(sys.argv[2]))
    print("Done")