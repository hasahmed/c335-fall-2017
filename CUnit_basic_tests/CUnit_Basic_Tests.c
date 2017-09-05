#include <stdio.h>
#include <assert.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

int pinit(){
    return 1;
}

int pcleanup(){
    return 2;
}

int trippleNum(int num){
    return num * 3;
}

int doubleNum(int x){
    return x * 2;
}

void test_doubleNum(){
    CU_ASSERT_EQUAL(doubleNum(2), 4);
}
void test_trippleNum(){
    CU_ASSERT_EQUAL(trippleNum(2), 5);
}

int main(){
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Sweet1", NULL, NULL);
    if(suite == 0){
        puts("successfully added suite");
    }
    CU_pTest test1 = CU_add_test(suite, "test1", test_doubleNum);
    CU_pTest test2 = CU_add_test(suite, "test2", test_trippleNum);
    CU_basic_set_mode(CU_BRM_NORMAL);
    //CU_basic_run_tests();
    CU_basic_run_suite(suite);


    puts("Go to cleanup");
    CU_cleanup_registry();
}
