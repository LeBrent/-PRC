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

void test_NAME(void)
{
  int test = 1337;

  int handle = mystack_create(20);

  TEST_ASSERT_EQUAL(0,mystack_push(handle, &test));

  int res = -1;

  TEST_ASSERT_EQUAL(0,mystack_pop(handle, &res));

  // printf("res=%d\n", res);

	TEST_ASSERT_EQUAL(test, res);
}

int main() {
  UnityBegin("stackTest.c");

  MY_RUN_TEST(test_create_a_stack_and_get_the_handle);
  MY_RUN_TEST(test_destroy_previous_stack);

	MY_RUN_TEST(test_NAME);

  return UnityEnd();
}
