int gcd_c(int a, int b) {
    int d = 0;

    while (!(a & 1) && !(b & 1)) {
        a >>= 1;
        b >>= 1;
        d += 1;
    }
    while (a != b) {
        if (!(a & 1)) a >>= 1;
        else if (!(b & 1)) b >>= 1;
        else if (a > b) a = ((a-b) >> 1);
        else b = ((b-a) >> 1);
    }
    return a << d;
}
