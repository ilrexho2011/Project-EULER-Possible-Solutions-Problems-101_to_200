// This is the ease version of Exercise 110

import math, functools, operator

def factor(x):
    factors = {}
    for p in range(2, int(math.sqrt(x)+1)):
        i = 0
        while x % p == 0:
            x //= p
            i += 1
        if i:
            factors[p] = i
    if x > 1:
        factors[x] = 1
    return factors

for n in range(1, 1000000):
    if (functools.reduce(operator.mul,
                        (2 * v + 1 for k, v in factor(n).items()),
                        1) + 1) // 2 > 1000:
        print(n)
        break