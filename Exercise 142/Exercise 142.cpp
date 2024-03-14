public long sum() {
	long sum = 0;
	boolean found = false;
	long a = 1;
	while (true) {
	    if (found) { break; }
	    a++;
	    long a2 = a*a;
	    for (long b=2; b*b<a2; b++) {
		if (found) { break; }
		long b2 = b*b;
		long abSum = a2 + b2;
		if (abSum%2 != 0) {
		    continue;
		}
		long x = abSum/2;
		long abDiff = a2 - b2;
		if (abDiff%2 != 0) {
		    continue;
		}
		long y = abDiff/2;
		long xSqrt = (long) Math.sqrt(x);
		for (long c=xSqrt+1; c*c<a2; c++) {
		    long c2 = c*c;
		    // deduce all other unknowns
		    long d2 = abSum - c2;
		    // z > 0
		    if (d2 >= c2) {
			break;
		    }
		    if (! Util.isSquare(d2)) {
			continue;
		    }
		    long cdDiff = c2 - d2;
		    if (cdDiff%2 != 0) {
			continue;
		    }
		    long z = cdDiff/2;
		    long e2 = y + z;
		    if (! Util.isSquare(e2)) {
			continue;
		    }
		    long f2 = y - z;
		    if (! Util.isSquare(f2)) {
			continue;
		    }
		    sum = x + y + z;
		    found = true;
		    break;
		}
	    }
	}
	return sum;
    }