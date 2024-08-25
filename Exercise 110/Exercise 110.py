def prob110(fewestSolutions = 4000000):
  bottomSigma = fewestSolutions * 2 - 1
  # The maximum number of distinct prime factors of the 
  #  result is equal to log(bottomSigma, 3), rounded up
  maxPFs = int(round(log(bottomSigma, 3) + .5))
  primes = primesBelow(100)[:maxPFs]
  expons = [1] * len(primes)
  def calcN():
        return prod([primes[i] ** expons[i] 
                     for i in range(len(primes))])
  def calcSigma():
        return prod([expons[i] * 2 + 1 
                     for i in range(len(primes))])
  result = calcN()
  last = len(expons)
  while last:
    # Last is the actually the first zero exponent
    last -= 1
    expons[last] = 0
    for i in range(last):
      expons[i] = 1

    expStack = stack()
    expStack.push(0)
    done = False
    while not done:
      sigma = calcSigma()
      N = calcN()
      while sigma < bottomSigma and N < result:
        expons[expStack.top] += 1
        sigma = calcSigma()
        N = calcN()
      if N < result:
        result = N
      right = expStack.pop()
      # Remove all exponent positions from the stack where
      #  the exponents to the left of the position are one
      #  more than the current position
      while (expStack and 
             (max(expons[:expStack.top]) <= 
              expons[expStack.top] + 1)):
        right = expStack.pop()

      if not expStack:
        # if we emptied the stack in the last loop and
        #  there are still exponents > 2 ...
        if ((right == 0 or max(expons[:right]) > 2) and 
            (right + 1 < last)):  # Don't pass last expon.
          # ... move the rightmost position to the right
          expStack.push(right + 1)
        else:
          # If the stack is empty and no exponent > 2,
          #  there's no way to make a bigger sigma and a
          #  smaller N, so we're done this iteration
          done = True
      if expStack:
        # We are not done, so increase the exponent at the 
        #  position indicated by the top of the stack
        expons[expStack.top] += 1

        # Reset all exponents to its left to the same value
        for i in range(expStack.top):
          expons[i] = expons[expStack.top]

        # Move the stack pointer to 
        #  the leftmost exponent position
        while expStack.top != 0:
          expStack.push(expStack.top - 1)
  return result
