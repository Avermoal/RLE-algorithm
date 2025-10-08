#ifdef NDEBUG

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <regex.h>

#include "decoder.h"
#include "encoder.h"
#include "utils.h"

#else

#include "tests.h"

#endif

int main(int argc, char *argv[])
{

  #ifdef NDEBUG
  
  if(argc == 3){
    regex_t regex;
    regcomp(&regex, ".rle", 0);
    int match = regexec(&regex, argv[2], 0, NULL, 0);

    if(strcmp(argv[1], "encode") == 0 && match != 0){
      printf("%s\n", "Encoding...");

      encodefile(argv[2]);

      printf("%s\n", "Finish.");
    }else if(strcmp(argv[1], "decode") == 0 && match == 0) {
     printf("%s\n", "Decoding...");
 
     decodefile(argv[2]);

      printf("%s\n", "Finish.");
    }else{
     printf("%s\n", "Invalid parameters");
     regfree(&regex);
     return -1;
    }
    regfree(&regex);
  }else{
    printf("Invalid parameters namber\n");
  }

  #else

  do_all_tests();
  
  #endif

  return 0;
}
