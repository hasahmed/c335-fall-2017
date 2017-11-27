/*
 * Hasan Y Ahmed
 * CSCI-C335
 * HW4
 * 11/08/17
 */
#ifndef _REG_NAME_H_
#define _REG_NAME_H_
#define NAMES_LEN 16
char *names[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"};
char* reg_name(unsigned int x);
char* reg_name_c(unsigned int x){
    if (x > 15)
        return 0;
    return names[x];
}
#endif //_REG_NAME_H_
