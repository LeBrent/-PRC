#include "unity.h"
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

void Succesful_Create(void)
{
  mystack_create(10);
	TEST_ASSERT_EQUAL(mystack->gStackList->next->handle,1 );
}

int main() {
  UnityBegin("stackTest.c");

	MY_RUN_TEST(Succesful_Create);

  return UnityEnd();
}
