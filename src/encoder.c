#include "encoder.h"

#include <stdlib.h>

#include <stdio.h>

size_t encode(uint8_t *toencbuf, size_t size, uint8_t **encbuf)
{
  size_t encsize = 0; /*Размер в байтах*/
  for(size_t i = 0; i < size; ){
    size_t same_part_size = 0, unsame_part_size = 0; /*Размер кодируемой области (не больше 129)*/
    uint8_t *unsamesimbols = (uint8_t*)calloc(129, sizeof(uint8_t));
    uint8_t simbol = *(toencbuf + i);
    for(size_t j = i; j < size && simbol == *(toencbuf + j) && same_part_size < 129; ++j, ++same_part_size);
    
    uint8_t simbol_iter_prev = simbol;
    int is_repeated = 0;
    for(size_t j = i; j < size && unsame_part_size < 129 && !is_repeated; ++j, ++unsame_part_size){
      if(simbol_iter_prev == *(toencbuf + j) && j != i){
        is_repeated = 1;
        unsame_part_size -= 2;
        continue;
      }
      *(unsamesimbols + (j - i)) = *(toencbuf + j);
      simbol_iter_prev = *(toencbuf + j);
    }

    if(same_part_size >= unsame_part_size && is_repeated){
      if(same_part_size == 1){
        *(*(encbuf) + encsize) = 0b00000000;
        *(*(encbuf) + encsize + 1) = simbol;
        encsize += 2;
      }else{
        uint8_t code = 0b00000000 + same_part_size - 0b00000010 + 0b10000000;
        *(*(encbuf) + encsize) = code;
        *(*(encbuf) + encsize + 1) = simbol;
        encsize += 2;
      }
      i += same_part_size;
    }else{
      uint8_t code = 0b00000000 + unsame_part_size - 0b00000001;
      *(*(encbuf) + encsize) = code;
      ++encsize;
      for(uint8_t i = 0; i < unsame_part_size; ++i, ++encsize){
        *(*(encbuf) + encsize) = *(unsamesimbols + i);
      }
      i += unsame_part_size;
    }
    free(unsamesimbols);
  }
  *(encbuf) = (uint8_t*)realloc(*encbuf, encsize*sizeof(uint8_t));
  return encsize;
}
