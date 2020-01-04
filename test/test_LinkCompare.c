#include "unity.h"
#include "LinkCompare.h"
#include "LinkListCompare.h"
Link  dataA;
Link  dataB;
int   compareValue;

void setUp(void){}
void tearDown(void){}

void test_List_LinkCompare_same_link(void){
    compareValue=linkCompare(&dataB,&dataB);
    TEST_ASSERT_EQUAL(1,compareValue);
}
void test_List_LinkCompare_different_link(void){
    compareValue=linkCompare(&dataA,&dataB);
    TEST_ASSERT_EQUAL(0,compareValue);
}
