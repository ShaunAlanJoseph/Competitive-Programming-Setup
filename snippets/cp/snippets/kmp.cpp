class KMP {
public:
    string needle;
    int len;
    vector<int> pre;

    KMP(string needle) {
        this->needle = needle;
        len = needle.size();
        pre = vector<int>(len);

        pre[0] = 0;
        int ptr = 0;
        for (int i = 0; i < len; i++) {
            while (ptr > 0 && needle[ptr] != needle[i])
                ptr = pre[ptr - 1];
            if (needle[ptr] == needle[i])
                ptr++;
            pre[i] = ptr;
        }
    }

    vector<int> match(string haystack) {
        vector<int> hits;
        int ptr = 0;
        for (int i = 0; i < (int)haystack.size(); i++) {
            while (ptr > 0 && needle[ptr] != haystack[i])
                ptr = pre[ptr - 1];
            if (needle[ptr] == haystack[i])
                ptr++;
            else
                ptr = pre[ptr];
            if (ptr == len) {
                ptr = pre.back();
                hits.push_back(i - len + 1);
            }
        }
        return hits;
    }
};
