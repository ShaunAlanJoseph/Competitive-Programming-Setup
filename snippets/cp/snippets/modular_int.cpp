class mint {
public:
	using ll = long long;

	inline static constexpr int MOD = 1e9 + 7;
	int val;

	template <typename T, typename = enable_if_t<is_integral_v<T>>>
	mint(T v) : val((v < 0) ? (v % MOD + MOD) % MOD : v % MOD) {}

	mint() : val(0) {}

	mint operator+(const mint& o) const { return mint(val + o.val); }
	mint operator-(const mint& o) const { return mint(val - o.val); }
	mint operator*(const mint& o) const { return mint((ll)val * o.val); }
	mint operator/(const mint& o) const { return *this * o.inv(); }

	mint& operator+=(const mint& o) { return *this = *this + o; }
	mint& operator-=(const mint& o) { return *this = *this - o; }
	mint& operator*=(const mint& o) { return *this = *this * o; }
	mint& operator/=(const mint& o) { return *this = *this / o; }

	bool operator==(const mint& o) const { return val == o.val; }
	bool operator!=(const mint& o) const { return val != o.val; }
	bool operator<(const mint& o) const { return val < o.val; }
	bool operator<=(const mint& o) const { return val <= o.val; }
	bool operator>(const mint& o) const { return val > o.val; }
	bool operator>=(const mint& o) const { return val >= o.val; }

	template <typename T, typename = enable_if_t<is_integral_v<T>>>
	mint operator+(const T& o) const { return *this + mint(o); }
	template <typename T, typename = enable_if_t<is_integral_v<T>>>
	mint operator-(const T& o) const { return *this - mint(o); }
	template <typename T, typename = enable_if_t<is_integral_v<T>>>
	mint operator*(const T& o) const { return *this * mint(o); }
	template <typename T, typename = enable_if_t<is_integral_v<T>>>
	mint operator/(const T& o) const { return *this / mint(o); }

	template <typename T, typename = enable_if_t<is_integral_v<T>>>
	mint& operator+=(const T& o) { return *this = *this + o; }
	template <typename T, typename = enable_if_t<is_integral_v<T>>>
	mint& operator-=(const T& o) { return *this = *this - o; }
	template <typename T, typename = enable_if_t<is_integral_v<T>>>
	mint& operator*=(const T& o) { return *this = *this * o; }
	template <typename T, typename = enable_if_t<is_integral_v<T>>>
	mint& operator/=(const T& o) { return *this = *this / o; }

	template <typename T, typename = enable_if_t<is_integral_v<T>>>
	friend mint operator+(T lhs, const mint& rhs) { return mint(lhs) + rhs; }
	template <typename T, typename = enable_if_t<is_integral_v<T>>>
	friend mint operator-(T lhs, const mint& rhs) { return mint(lhs) - rhs; }
	template <typename T, typename = enable_if_t<is_integral_v<T>>>
	friend mint operator*(T lhs, const mint& rhs) { return mint(lhs) * rhs; }
	template <typename T, typename = enable_if_t<is_integral_v<T>>>
	friend mint operator/(T lhs, const mint& rhs) { return mint(lhs) / rhs; }

	mint operator-() const { return mint(-val); }

	mint inv() const { return pow(MOD - 2); }
	mint pow(ll exp) const { ll r = 1, b = val; for (; exp; exp >>= 1, b = (b * b) % MOD) if (exp & 1) r = (r * b) % MOD; return mint(r); }

	operator int() const { return val; }

	friend istream& operator>>(istream& is, mint& m) { ll x; is >> x; m = mint(x); return is; }
	friend ostream& operator<<(ostream& os, const mint& m) { os << m.val; return os; }
};

