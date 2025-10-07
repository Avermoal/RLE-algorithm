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

  #ifdef NDEBUG

  if(strcmp(argv[1], "encode") == 0){
    printf("%s\n", "Encoding...");

    printf("%s\n", "Finish.");
  }else if(strcmp(argv[1], "decode") == 0) {
    printf("%s\n", "Decoding...");
 
    printf("%s\n", "Finish.");
  }else{
    printf("%s\n", "Invalid parameter");
    return -1;
  }

  #else

  do_all_tests();
  
  #endif

  return 0;
}
