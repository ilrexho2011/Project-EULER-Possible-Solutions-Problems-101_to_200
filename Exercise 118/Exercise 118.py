from __future__ import division
from itertools import permutations
import km
from kdecs import timing

def rec(n, l, mem={}):
    if not n:
        return 1/f[l]
    try:
        return mem[n, l]
    except KeyError:
        s = 0
        for i in xrange(1, len(n)+1):
            if km.is_prime(int(n[:i])):
                s += rec(n[i:], l+1)
        mem[n, l] = s
        return s

@timing
def p118():
    global f
    f = [km.factorial(x) for x in range(10)]
    n = '123456789'
    s = round(sum(rec(''.join(nn), 0) for nn in permutations(n)))
    print 'Solution: {0}'.format(int(s))

p118()
