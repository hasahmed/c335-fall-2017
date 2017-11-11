int gcd_c(int a, int b) {
    int d = 0;

    //refactored to more closely resemble assembly
    while (1){
        if((a & 1) || (b & 1))  //if odd break
            break;
        a >>= 1;
        b >>= 1;
        d += 1;
    }
    while (1){
        if (a == b) break;
        if (!(a & 1)) //checks for even
            a >>= 1;  //shift right if even
        else if (!(b & 1)) 
            b >>= 1; //checks for even
        else if (a > b)
            a = ((a-b) >> 1);
        else 
            b = ((b-a) >> 1);
    }

    return a << d;

    /*
    while (!(a & 1) && !(b & 1)) { //tests to see if the numbers are even?
        a >>= 1;
        b >>= 1;
        d += 1;
    }
    */
    /*
    while (a != b) {
        if (!(a & 1)) a >>= 1;
        else if (!(b & 1)) b >>= 1;
        else if (a > b) a = ((a-b) >> 1);
        else b = ((b-a) >> 1);
    }
    */
}
