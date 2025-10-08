#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_FILE_NAME_LENGTH 100

void decodefile(const char *filename);

void encodefile(const char *filename);

/*Функции: получения буфера и выгрузки*/
/*Возвращает размер буфера. Размер buf должен быть минимальным*/
size_t getbuf(const char *filename, uint8_t **buf);

void offloadbuf(const char *filename, uint8_t *buf, size_t size);

size_t get_file_size(const char *filename);

#endif/*UTILS_H*/
