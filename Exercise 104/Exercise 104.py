def main():
    class Big:
        def __init__(self, v):
            self.data = v 
                
        def __iadd__(self, other):
            result = []
            carry = 0
            sd = self.data
            od = other.data
            while len(sd) < len(od): sd.append(0)
            while len(od) < len(sd): od.append(0)
            for i,b in enumerate(od):
                carry, sd[i] = divmod(sd[i] + b + carry, 1000000000)
            if carry: sd.append(carry)
            return self
 
        def __str__(self):
            result = ["%09d" % d for d in self.data]
            result.reverse() 
            return "".join(result).lstrip('0')
            
    from sets import Set as set
    
    pandigits = set("123456789")
    
    def pandigital_1_9(n):
        if len(n.data) < 2: return
        s = set(str(n.data[0]))
        if set(s) != pandigits: return False
        s = set(str(n)[:9])
        print k, s
        return s == pandigits
        
    def fib_gen():
        a = Big([1])
        b = Big([1])
        while 1:
            yield a
            a += b; a, b = b, a
            
    for k, fk in enumerate(fib_gen()):
        if k % 100 == 0: print k
        if pandigital_1_9(fk): 
            print fk
            print k
            break 
main()      
