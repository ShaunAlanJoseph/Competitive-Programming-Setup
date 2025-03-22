template <typename T, T DEFAULT = T(), typename OPERATION = std::plus<T>>
class SegTree {
	int N = 1;
	vector<T> segtree;
	OPERATION OP;

	int LC(int i) { return 2 * i + 1; }
	int RC(int i) { return 2 * i + 2; }

	T build(int i, int L, int R, vector<T> &a) {
		if (L == R)
			return segtree[i] = (L < (int)a.size() ? a[L] : DEFAULT);
		int mid = (L + R) / 2;
		return segtree[i] = OP(build(LC(i), L, mid), build(RC(i), mid + 1, R));
	}

public:
	SegTree(vector<T> &a) {
		while (N < (int)a.size())
			N *= 2;
		segtree = vector<T>(2 * N - 1, DEFAULT);
		build(0, 0, N - 1, a);
	}

	T query(int ql, int qr, int i, int L, int R) {
		if (R < ql || L > qr)
			return DEFAULT;
		if (ql <= L && qr >= R)
			return segtree[i];
		int mid = (L + R) / 2;
		return OP(query(ql, qr, LC(i), L, mid), query(ql, qr, RC(i), mid + 1, R));
	}
	T query(int ql, int qr) { return query(ql, qr, 0, 0, N - 1); }

	T get(int x) { return query(x, x); }

	void point_upd(int x, T val, int i, int L, int R) {
		if (L == R) {
			segtree[i] = val;
			return;
		}
		int mid = (L + R) / 2;
		if (x <= mid)
			point_upd(x, val, LC(i), L, mid);
		else
			point_upd(x, val, RC(i), mid + 1, R);
		segtree[i] = OP(segtree[LC(i)], segtree[RC(i)]);
	}
	void point_upd(int x, T val) { point_upd(x, val, 0, 0, N - 1); }

	void point_op(int x, T val) { point_upd(x, OP(get(x), val), 0, 0, N - 1); }
};

