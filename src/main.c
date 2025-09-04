#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "decoder.h"
#include "encoder.h"


int main(int argc, char *argv[])
{
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

    printf("%s\n", "Finish.");
  }else if(strcmp(argv[1], "decode") == 0) {
    printf("%s\n", "Decoding...");

    uint8_t *todecbuf = (uint8_t*)calloc(4, sizeof(uint8_t));
    todecbuf[0] = 255;
    todecbuf[1] = 0;
    todecbuf[2] = 197;
    todecbuf[3] = 0;
    uint8_t *decbuf = (uint8_t*)calloc(1, sizeof(uint8_t));
    size_t decsize = decode(todecbuf, 4, decbuf);
    for(size_t i = 0; i < decsize; ++i){
      printf("%d\t", *(decbuf + i));
    }
    printf("\n %d\n", decsize);
    free(todecbuf);
    free(decbuf);

    printf("%s\n", "Finish.");
  }else{
    printf("%s\n", "Invalid parameter");
    return -1;
  }

  return 0;
}
