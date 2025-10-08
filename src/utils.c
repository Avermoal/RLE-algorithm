#include "utils.h"

#include <stdlib.h>
#include <string.h>

#include "decoder.h"
#include "encoder.h"


void decodefile(const char *filename)
{
  uint8_t *todecbuf = (uint8_t*)calloc(1, sizeof(uint8_t));
  uint8_t *decbuf = (uint8_t*)calloc(1, sizeof(uint8_t));
  size_t todecsize = getbuf(filename, &todecbuf);
  size_t decsize = decode(todecbuf, todecsize, &decbuf);
  
  char new_file_name[MAX_FILE_NAME_LENGTH];
  strncpy(new_file_name, filename, strlen(filename) - 4);

  offloadbuf(new_file_name, decbuf, decsize);

  free(todecbuf);
  free(decbuf);
}

void encodefile(const char *filename)
{
  uint8_t *toencbuf = (uint8_t*)calloc(1, sizeof(uint8_t));
  uint8_t *encbuf = (uint8_t*)calloc(1, sizeof(uint8_t));
  size_t toencsize = getbuf(filename, &toencbuf);
  size_t encsize = encode(toencbuf, toencsize, &encbuf);

  char new_file_name[MAX_FILE_NAME_LENGTH];
  int strlength = strlen(filename);
  for(int i = 0; i <= strlength; ++i){
    new_file_name[i] = filename[i];
  }
  strcat(new_file_name, ".rle");

  offloadbuf(new_file_name, encbuf, encsize);

  free(toencbuf);
  free(encbuf);
}

size_t getbuf(const char *filename, uint8_t **buf)
{
  size_t bufsize = get_file_size(filename);
  if(bufsize == 0){
    return 0;
  }
  *(buf) = (uint8_t*)realloc(*(buf), bufsize*sizeof(uint8_t));
  FILE *file = fopen(filename, "r");
  if(file == NULL){
    perror("ERROR: FILE NOT OPEN\n");
    return 0;
  }
  
  uint8_t ch = 0;
  size_t i = 0;
  while((ch = fgetc(file) != EOF)){
    *(*(buf) + i) = ch;
    ++i;
  }

  fclose(file);
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
}

size_t get_file_size(const char *filename)
{
  size_t filesize;
  FILE *file = fopen(filename, "r");
  if(file == NULL){
    perror("ERROR: FILE NOT READ\n");
    return 0;
  }
  
  while(fgetc(file) != EOF){
    ++filesize;
  }

  fclose(file);
  return filesize;
}
