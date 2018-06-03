import random
import math
import time

low_primes =   [2, 3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97
                ,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179
                ,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269
                ,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367
                ,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461
                ,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571
                ,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661
                ,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773
                ,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883
                ,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997]

def div(n):
    cnt = 0
    while (n & 1) == 0:
        n = n >> 1
        cnt = cnt + 1
    return [n, cnt]

def little_prime_judge(n):
    for i in low_primes:
        if n % i == 0:
            return False
    return True

def miller_rabin_judge(n):
    [m, k] = div(n - 1)

    for i in range(0, 5):
        a = random.randint(2, n - 2)

        tmp = pow(a, m, n)

        if tmp != 1:
            cnt = 0
            while tmp != (n - 1):   #-1
                if cnt == k - 1:
                    return False
                else:
                    cnt = cnt + 1
                    tmp = (tmp ** 2) % n
    return True 


def is_prime(n):
    if little_prime_judge(n):
        if not miller_rabin_judge(n):
            return False
        return True
    else:
        return False

def get_random_num(num):
    #time_start = time.time()
    '''
    n = 1
    for i in range(0, num - 2):
        #print(random.randrange(2))
        n = n << 1
        tmp = random.randint(0, 1)   # 0 or 1
        n = n | tmp
    n = n << 1
    n = n | 1
    '''
    
    
    n = random.randrange(2**(num-1),2**(num))
    #time_end = time.time()
    #print("cost", time_end - time_start)
    return n


def get_prime(num):
    while True:
        n = get_random_num(num)

        if is_prime(n):
            return n


def extend_gcd(a, b):
    if a % b == 0 :
        x = 0
        y = 1
        return [x, y]
    
    [x, y] = extend_gcd(b, a % b)

    tmpx = y
    tmpy = x - (a // b) * y

    return [tmpx, tmpy]


def get_key(num):
    e = 65537

    while True:
        p = get_prime(num)
        q = get_prime(num)

        phi_n = (p - 1) * (q - 1)

        if phi_n % e != 0:
            break
    n = p * q

    [k, d] = extend_gcd(phi_n, e)

    return [e, d, n]


