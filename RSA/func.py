import random
import math
import time

low_primes =   [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 
                101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 
                211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 
                307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 
                401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 
                503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 
                601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 
                701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 
                809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 
                907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 
                1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097,
                1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 
                1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 
                1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381, 1399,
                1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 
                1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 
                1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663, 1667, 1669, 1693, 1697, 1699, 
                1709, 1721, 1723, 1733, 1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 
                1801, 1811, 1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 
                1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 1997, 1999]  #2000以内的小素数

def div(n):  # 将n分解为(n * 2^cnt)
    cnt = 0
    while (n & 1) == 0:
        n = n >> 1
        cnt = cnt + 1
    return [n, cnt]

def little_prime_judge(n):  #判断能否被小素数整除
    for i in low_primes:
        if n % i == 0:
            return False
    return True

def get_rounds(num):
    '''
    http://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.186-4.pdf
    '''
    if num >= 1536:
        return 3
    elif num >= 1024:
        return 4
    elif num >= 512:
        return 7
    else:
        return 10
def miller_rabin_judge(n, num):  
    [m, k] = div(n - 1)    # 将n-1 分解为 m * 2^k

    rounds = get_rounds(num)
    #print(rounds)
    for i in range(0, rounds):   #判定七轮
        a = random.randint(2, n - 2)  # 取一个随机数a

        tmp = pow(a, m, n) # 计算 a^m % n

        if tmp != 1:
            cnt = 0
            while tmp != (n - 1):   #-1
                if cnt == k - 1:
                    return False
                else:
                    cnt = cnt + 1
                    tmp = (tmp ** 2) % n
    return True 


def is_prime(n, num):  # 判断是否是素数
    if little_prime_judge(n):
        if not miller_rabin_judge(n, num):
            return False
        return True
    else:
        return False

def get_random_num(num):  # 获取num位的随机数
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




####  下面的函数用于RSA  与作业无关  ######
def get_prime(num): 
    while True:
        n = get_random_num(num)

        if is_prime(n, num):
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


