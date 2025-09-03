#ifndef ENCODER_H
#define ENCODER_H

#include <stddef.h>
#include <stdint.h>

/*
 * Возвращает размер буфера закодированных данных
 * Принимает буфер некодированных данных и размер этого буфера и указатель на закодированный бффер.
 * Не сохроняет позицию в памяти encbuf, необходимо быть внемательным с указателями на encbuf
*/
size_t encode(uint8_t *toencbuf, size_t size, uint8_t *encbuf);

#endif/*ENCODER_H*/
