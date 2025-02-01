const int P_MAX = (int)(4*1e7);
bitset<P_MAX/2> P_BITS;
int P_COUNT = 1;
vector<ll> PRIMES = {2};

void calc_PRIMES() {
	P_BITS.set();
	for (int i = 3; i / 2 < (int)P_BITS.size(); i = 2 * P_BITS._Find_next(i / 2) + 1) {
		PRIMES.push_back(i);
		++P_COUNT;
		for (auto j = (int64_t) i * i / 2; j < (int)P_BITS.size(); j += i)
			P_BITS[j] = 0;
	}
}
