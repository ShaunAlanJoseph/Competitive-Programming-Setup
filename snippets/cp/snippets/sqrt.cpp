ll sqrt(ll x) {
    if (x == 0)
        return 0;
    ll left = 1;
    ll right = x / 2 + 1;
    ll res;
    while (left <= right) {
        ll mid = left + ((right - left) / 2);
        if (mid <= x / mid) {
            left = mid + 1;
            res = mid;
        }
        else
            right = mid - 1;
    }
    return res;
}
