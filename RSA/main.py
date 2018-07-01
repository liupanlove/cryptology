import random
from func import *
import time

num = 512

with open("data.txt", "w") as f:
    for i in range(0, 100):
        n = get_random_num(num)

        f.write(str(n) + " ")
        if is_prime(n, num):
            f.write("是素数\n")
        else:
            f.write("不是素数\n")