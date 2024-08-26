import km

def p111():
    dim = 10
    mask = 1111111111
    sums = [0]*10
    # zero
    for i in xrange(1, 10):
        for j in xrange(1, 10):
            num = i*1000000000+j
            if km.is_rm_prime(num):
                sums[0]+=num
    # 1 to 9 but not 2 and 8
    for i in xrange(1, 10):
        if i==2 or i==8:
            continue
        for needle in xrange(dim):
            for j in xrange(10):
                test = i*mask+(j-i)*10**needle
                if km.is_rm_prime(test):
                    sums[i]+=test
    # 2 and 8
    for i in [2,8]:
        for p1 in xrange(9):
            for p2 in xrange(p1+1, 10):
                for j in xrange(10):
                    if p2==9 and j==0:
                        continue
                    for k in xrange(10):
                        test = i*mask + (k-i)*10**p1 + (j-i)*10**p2
                        if km.is_rm_prime(test):
                            sums[i]+=test
    s = sum(sums)
    print 'Solution: {}'.format(s)

p111()
