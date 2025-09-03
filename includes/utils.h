#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

/*Функции: получения буфера и выгрузки, подсчёта размера*/

/*Возвращает размер буфера*/
size_t getbuf(const char *filename, uint8_t *buf);

void offloadbuf(const char *filename, uint8_t *buf, size_t size);

size_t get_file_size(const char *filename);

#endif/*UTILS_H*/
