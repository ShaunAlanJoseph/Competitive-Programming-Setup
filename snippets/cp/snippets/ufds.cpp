class UFDS {
	int set_count = 0;
	vector<int> parent, size;
public:
	UFDS(int n) : set_count(n) {
    	parent.resize(n); size.resize(n);
    	for(int i = 0; i < n; i++) { parent[i] = i; size[i] = 1; }
	}
	UFDS() {}

	int make_set() {
    	parent.push_back(parent.size());
    	size.push_back(1);
    	set_count++;
    	return (int)parent.size() - 1;
	}

	int total_nodes() { return parent.size(); }

	int count() { return set_count; }

	int set_size(int id) {
    	id = find(id);
    	return size[id];
	}

	int find(int id) {
    	if(id != parent[id])
       		return id = find(parent[id]);
    	return id;
	}

	bool unite(int x, int y) {
    	x = find(x), y = find(y);
    	if(x == y) return false;
    	if(size[x] < size[y]) swap(x, y);
    	parent[y] = x;
    	size[x] += size[y];
    	set_count--;
    	return true;
	}
};

