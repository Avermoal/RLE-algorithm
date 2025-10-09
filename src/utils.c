#include "utils.h"

#include <stdlib.h>
#include <string.h>

#include "decoder.h"
#include "encoder.h"


void decodefile(const char *filename)
{
  printf("Start\n");
  uint8_t *todecbuf = (uint8_t*)calloc(1, sizeof(uint8_t));
  uint8_t *decbuf = (uint8_t*)calloc(1, sizeof(uint8_t));
  size_t todecsize = getbuf(filename, &todecbuf);
  size_t decsize = decode(todecbuf, todecsize, &decbuf);
  printf("Decode succes\n");
  
  char new_file_name[MAX_FILE_NAME_LENGTH];
  int strlength = strlen(filename);
  for(int i = 0; i < strlength - 4; ++i){
    new_file_name[i] = filename[i];
  }
  new_file_name[strlength-4] = '\0';

  printf("DECODE: file name: %s\n", new_file_name);

  offloadbuf(new_file_name, decbuf, decsize);

  free(todecbuf);
  free(decbuf);
}

void encodefile(const char *filename)
{
  printf("Start\n");
  uint8_t *toencbuf = (uint8_t*)calloc(1, sizeof(uint8_t));
  size_t toencsize = getbuf(filename, &toencbuf);
  uint8_t *encbuf = (uint8_t*)calloc(toencsize, sizeof(uint8_t));
  size_t encsize = encode(toencbuf, toencsize, &encbuf);
  printf("Encode succes, encode length: %d\n", encsize);

  char new_file_name[MAX_FILE_NAME_LENGTH];
  int strlength = strlen(filename);
  for(int i = 0; i <= strlength; ++i){
    new_file_name[i] = filename[i];
  }
  strcat(new_file_name, ".rle");
  printf("ENCODE: file name: %s\n", new_file_name);

  offloadbuf(new_file_name, encbuf, encsize);

  free(toencbuf);
  free(encbuf);
}

size_t getbuf(const char *filename, uint8_t **buf)
{
  printf("Get bufer\n");
  size_t bufsize = get_file_size(filename);
  if(bufsize == 0){
    printf("Bufer size is zero\n");
    return 0;
  }
  *(buf) = (uint8_t*)realloc(*(buf), bufsize*sizeof(uint8_t));
  FILE *file = fopen(filename, "r");
  if(file == NULL){
    perror("ERROR: FILE NOT OPEN\n");
    return 0;
  }
  
  int ch = 0;
  size_t i = 0;
  while((ch = fgetc(file)) != EOF){
    *(*(buf) + i) = (uint8_t)ch;
    ++i;
  }

  fclose(file);
  printf("Success\n");
  printf("Bufer size: %d\n", bufsize);
  return bufsize;
}

void offloadbuf(const char *filename, uint8_t *buf, size_t size)
{
  FILE *file = fopen(filename, "w");
  if(file == NULL){
    perror("FILE MISSED\n");
    return;
  }
  for(size_t i = 0; i < size; ++i){
    fputc(*(buf + i), file);
  }
  fclose(file);
  printf("Offload bufer success\n");
}

size_t get_file_size(const char *filename)
{
  printf("Get file size\n");
  size_t filesize = 0;
  FILE *file = fopen(filename, "r");
  if(file == NULL){
    perror("ERROR: FILE NOT READ\n");
    return 0;
  }

  int ch = 0;
  while((ch = fgetc(file)) != EOF){
    ++filesize;
  }

  fclose(file);
  return filesize;
}
