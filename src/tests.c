#include "tests.h"

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "encoder.h"
#include "decoder.h"

void do_all_tests(void)
{
  assert((encode_tests() == TEST_PASSED)&&"ERROR:");
  assert((decode_tests() == TEST_PASSED)&&"ERROR:");
}

test_result_t encode_tests(void)
{
  size_t size1 = 200, size2 = 32;
  uint8_t *toencbuf1 = (uint8_t*)calloc(size1, sizeof(uint8_t));
  uint8_t *encbuf1 = (uint8_t*)calloc(size1, sizeof(uint8_t));
  uint8_t toencbuf2[] = {
    0,   0,   0,   0,   0,   0,   4,   2,   0,   4,   4,   4,   4,   4,   4,   4,
	  80,  80,  80,  80,  0,   2,   2,   2,   2,   255, 255, 255, 255, 255, 0,   0
  };
  uint8_t *encbuf2 = (uint8_t*)calloc(size2, sizeof(uint8_t));
  size_t encsize1 = encode(toencbuf1, size1, encbuf1);
  size_t encsize2 = encode(toencbuf2, size2, encbuf2);

  uint8_t control1[] = {255, 0, 197, 0};
  if(encsize1 != 4){
    printf("TEST_FAILED: encode1 size not equal to 4 but %d\n", encsize1);
    free(toencbuf1);
    free(encbuf1);
    free(encbuf2);
    return TEST_FAILED;
  }
  for(size_t i = 0; i < encsize1; ++i){
    if(encbuf1[i] != control1[i] ){
      printf("TEST_FAILED: not same");
      free(toencbuf1);
      free(encbuf1);
      free(encbuf2);
      return TEST_FAILED;
    }
  }

  uint8_t control2[] = {
    0x84, 0x00, 0x02, 0x04, 0x02, 0x00, 0x85, 0x04, 0x82, 0x80, 0x00, 0x00, 0x82, 0x02, 0x83, 0xFF, 0x80, 0x00
  };
  for(size_t i = 0; i < encsize2; ++i){
    printf("%d\t", encbuf2[i]);
  }
  printf("\n");
  for(size_t i = 0; i < 18; ++i){
    printf("%d\t", control2[i]);
  }
  printf("\n");
  if(encsize2 != 18){
    printf("TEST_FAILED: encode2 size not equal 18 but %d\n", encsize2);
    free(toencbuf1);
    free(encbuf1);
    free(encbuf2);
    return TEST_FAILED;
  }
  for(size_t i = 0; i < encsize2; i++){
    if(encbuf2[i] != control2[i]){
      printf("TEST_FAILED: not same");
      return TEST_FAILED;
      free(toencbuf1);
      free(encbuf1);
      free(encbuf2);
    }
  }
  free(toencbuf1);
  free(encbuf1);
  free(encbuf2);
  return TEST_PASSED;
}

test_result_t decode_tests(void)
{
  return TEST_PASSED;
}
