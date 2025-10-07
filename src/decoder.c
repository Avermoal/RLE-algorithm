#include "decoder.h"

#include <stdlib.h>

#include "utils.h"


size_t decode(uint8_t *todecbuf, size_t size, uint8_t **decbuf)
{
  size_t decsize = 0;/*Размер декодированного буфера необходимо узнать прежде чем записывать в него что-то*/
  for(size_t i = 0; i < size; ++i){/*Подсчёт decsize*/
    if(*(todecbuf + i) - 0b10000000 >= 0){
      decsize += *(todecbuf + i) - 0b10000000 + 0b00000010;/*-128 + 2*/
      ++i;
    }else{
      decsize += *(todecbuf + i) + 1;
      i += *(todecbuf + i) + 1;
    }
  }

  *(decbuf) = (uint8_t*)realloc(*decbuf, decsize*sizeof(uint8_t));
 
  for(size_t i = 0, deciter = 0; i < size; ++i){/*Декодинг буфера*/
    if(*(todecbuf + i) - 0b10000000 >= 0){
      for(size_t j = 0; j < *(todecbuf + i) - 0b10000000 + 0b00000010; ++j){
        *(*(decbuf) + j + deciter) = *(todecbuf + i + 1);
      }
      deciter += *(todecbuf + i) - 0b10000000 + 0b00000010;
      ++i;
    }else{
      for(size_t j = 0; j < *(todecbuf + i) + 1; ++j){
        *(*(decbuf) + j + deciter) = *(todecbuf + i + 1 + j);
      }
      deciter += *(todecbuf + i) + 1;
      i += *(todecbuf + i);
    }
  }

  return decsize;
}
