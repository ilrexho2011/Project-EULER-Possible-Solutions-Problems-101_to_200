class sieve_primes_up_to_limit
{
public:
	sieve_primes_up_to_limit(size_t limit);
	~sieve_primes_up_to_limit();

	size_t limit() const { return _limit; }
	size_t size() const { return _size; }
	size_t operator[] (size_t i) const
	{
		assert(i<_size);
		return _primes[i];
	}

	bool is_prime(size_t n) const
	{
		assert(n<=_limit);
		if(n%2!=0)
			return !get(n/2);
		else return n==2;
	}

private:
	bool get(size_t i) const { return (_mask[i/32]>>(i%32))&1; }
	void set(size_t i) { _mask[i/32]|=(1<<(i%32)); }

private:
	size_t _limit;
	size_t _size;
	std::vector<uint32_t> _mask;
	size_t *_primes;
};

sieve_primes_up_to_limit::sieve_primes_up_to_limit(size_t limit)
: _limit(limit), _size(0), _mask(limit/64+1, 0), _primes(0), _pi(0), _mu(0)
{
	_mask[0]=1;
	for(size_t p=3; p*p<=limit; p+=2)
		if(!get(p/2))
			for(size_t n=p*p; n<=limit; n+=2*p)
				set(n/2);

	size_t capacity=size_t(1.06*limit/log(limit))+ 15000;
	_primes=new size_t[capacity];
	if(2<=limit)
		_primes[_size++]=2;
	for(size_t p=3; p<=limit; p+=2)
		if(!get(p/2))
			_primes[_size++]=p;
#ifndef NDEBUG
	assert(_size<=capacity);
	std::cout << "primes size=" << _size;
	if(0<_size)
		std::cout << ", max=" << _primes[_size-1];
	std::cout << ", limit=" << _limit << std::endl;
#endif
}