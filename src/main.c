#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "decoder.h"
#include "encoder.h"
#include "tests.h"


int main(int argc, char *argv[])
{
  do_all_tests();


  if(strcmp(argv[1], "encode") == 0){
    printf("%s\n", "Encoding...");

    uint8_t *toencbuf = (uint8_t*)calloc(200, sizeof(uint8_t));
    uint8_t *encbuf = (uint8_t*)calloc(200, sizeof(uint8_t));
    size_t encsize = encode(toencbuf, 200, encbuf);
    for(size_t i = 0; i < encsize; ++i){
      printf("%d\t", *(encbuf + i));
    }
    printf("\n %d\n", encsize);
    free(toencbuf);
    free(encbuf);

    uint8_t toencbuf1[] = {1, 1, 1, 1, 4, 2, 2, 2, 3, 3, 4};
    uint8_t *encbuf1 = (uint8_t*)calloc(11, sizeof(uint8_t));
    size_t encsize1 = encode(toencbuf1, 11, encbuf1);
    for(size_t i = 0; i < encsize1; ++i){
      printf("%d\t", *(encbuf1 + i));
    }
    printf("\n %d\n", encsize1);
    free(encbuf1);

    printf("%s\n", "Finish.");
  }else if(strcmp(argv[1], "decode") == 0) {
    printf("%s\n", "Decoding...");

    uint8_t todecbuf[] = {
      132, 0, 0, 4, 0, 2, 0, 0, 133, 4, 130, 80, 0, 0, 130, 2, 131, 255, 128, 0};
    uint8_t *decbuf = (uint8_t*)calloc(1, sizeof(uint8_t));
    size_t decsize = decode(todecbuf, 20, decbuf);
    for(size_t i = 0; i < decsize; ++i){
      printf("%d\t", *(decbuf + i));
    }
    printf("\n %d\n", decsize);
    free(decbuf);

    printf("%s\n", "Finish.");
  }else{
    printf("%s\n", "Invalid parameter");
    return -1;
  }

  return 0;
}
