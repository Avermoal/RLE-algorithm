#ifndef TESTS_H
#define TESTS_H

typedef enum{
  TEST_PASSED = 0,
  TEST_FAILED
}test_result_t;

void do_all_tests(void);

test_result_t encode_tests(void);
test_result_t decode_tests(void);

#endif/*TESTS_H*/
