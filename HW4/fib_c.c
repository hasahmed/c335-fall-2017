int fib_c(int num) {
  int prev2=1;
  int prev1=1; 
  int val=1;
  int i; 
  if (num == 0) return 0;
  else if (num == 1) return 1;
  else {
    for (i = 0; i < (num - 2); i++) {
      val = prev1 + prev2;
      prev2 = prev1;
      prev1 = val;
    }
    return val;
  }
}
