#include <stdio.h>
#include <stdlib.h>


//registers
//2,3
#define rm(x) ((x >> 6) & 0x7) //2,3
#define rn(x) ((x >> 3) & 0x7) //2,3
#define rd(x) (x & 0x7) //2,3

//4
#define rdn(x) ((x >> 8) & 0x7) //4
#define imm8(x) (x & 0xFF)
#define imm3(x) ((x >> 6) & 0x7)

//5
#define RM(x) (((x) >> 3) & 0x7) //5
#define RN(x) (x & 0x7) //5



//opcodes
#define DPR_OPPCODE(x) ((x >> 6) & 0xF) //5
#define ASR_I_OPPCODE(x) ((x >> 9) & 0x1) //for add/subtract register, and add/subtract immediate //2,3

//4
#define ASCM_OPPCODE(x) ((x >> 11) & 0x3)

//instruction classes
#define IS_ADD_SUB_REG(x) (((x >> 13) & 0x3) == 0x0) && (((x >> 10) & 0x1) == 0x0)  //2
#define IS_ADD_SUB_IMMEDIATE(x) (((x >> 13) & 0x3) == 0x0) && (((x >> 10) & 0x1) == 0x1) //3
#define IS_ADD_SUB_CMP_MOV_IMMEDIATE(x) ((x >> 13) & 0x1) == 0x1 //4
#define IS_DATA_PROC_REG(x) ((x >> 10) & 0x10) == 0x10 //5

char *regnames[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "pc"}; //2-5

char *adsr_opnames[] = {"adds", "subs"}; //2, 3
char *opnames[] = {"ands", "eors", "lsls" ,"lsrs", "asrs" ,"adcs" ,"sbcs" ,"rors" ,"tst", "rsbs", "cmp", "cmn", "orrs", "muls", "bics", "mvns"}; // 5
char *ascm_opnames[] = {"movs", "cmp", "adds", "subs"}; //4

char **asm_instructions;

int main(){
    printf( ".text\n"
            ".syntax unified\n"
            ".thumb\n"
            );

    unsigned int hex_num;
    while(scanf("%x", &hex_num) == 1){

    if (IS_ADD_SUB_REG(hex_num)) //2
        printf("    %s %s, %s, %s\n", 
                adsr_opnames[ASR_I_OPPCODE(hex_num)],
                regnames[rd(hex_num)], 
                regnames[rn(hex_num)], 
                regnames[rm(hex_num)]);
    else if (IS_ADD_SUB_IMMEDIATE(hex_num)) //3
        printf("    %s %s, %s, %u\n", adsr_opnames[ASR_I_OPPCODE(hex_num)], regnames[rd(hex_num)], regnames[rn(hex_num)], imm3(hex_num));
    else if (IS_ADD_SUB_CMP_MOV_IMMEDIATE(hex_num)) //4
        printf("    %s %s, %d\n", ascm_opnames[ASCM_OPPCODE(hex_num)], regnames[rdn(hex_num)], imm8(hex_num));
    else if (IS_DATA_PROC_REG(hex_num)) //5
        printf("    %s %s, %s\n", opnames[DPR_OPPCODE(hex_num)], regnames[RN(hex_num)], regnames[RM(hex_num)]);
    else
        printf("    .hword 0x%x\n", hex_num);
    }
    return 0;
}
