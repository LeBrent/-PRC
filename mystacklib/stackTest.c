#include "Unity/src/unity.h"
#include "mystack.h"

// I rather dislike keeping line numbers updated, so I made my own macro to ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void setUp(void)
{
    // This is run before EACH test
}

void tearDown(void)
{
    // This is run after EACH test
}

void test_create_a_stack_and_get_the_handle(void)
{
  //first stack that is about to be created so the handle should be 1
  TEST_ASSERT_EQUAL(1,mystack_create(20));
}

void test_destroy_previous_stack(void)
{
  //first stack that is about to be created so the handle should be 1
  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void test_create_multiple_stacks(void)
{
  TEST_ASSERT_EQUAL(1,mystack_create(sizeof(int)));
  TEST_ASSERT_EQUAL(2,mystack_create(sizeof(unsigned int)));
  TEST_ASSERT_EQUAL(3,mystack_create(sizeof(char)));
  TEST_ASSERT_EQUAL(4,mystack_create(34));
  TEST_ASSERT_EQUAL(5,mystack_create(89));
}

void test_succesful_push(void)
{

  int number = 4;
  unsigned int j = 20;
  char c = 'B';
  TEST_ASSERT_EQUAL(0,mystack_push(1,&number));
  TEST_ASSERT_EQUAL(0,mystack_push(2,&j));
  TEST_ASSERT_EQUAL(0,mystack_push(3,&c));
}

void test_succesful_pop(void)
{
  mystack_create(4);
  mystack_create(4);
  mystack_create(4);
  int number = 34958;
  int number2 = 0;
  mystack_push(2,&number);
  mystack_pop(2,&number2);
  TEST_ASSERT_EQUAL_INT(number, number2);
}
int main() {
  UnityBegin("stackTest.c");

  MY_RUN_TEST(test_create_a_stack_and_get_the_handle);
  MY_RUN_TEST(test_destroy_previous_stack);

	MY_RUN_TEST(test_create_multiple_stacks);
  MY_RUN_TEST(test_succesful_push);
  MY_RUN_TEST(test_succesful_pop);

  return UnityEnd();
}
