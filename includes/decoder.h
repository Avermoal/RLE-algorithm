#ifndef DECODER_H
#define DECODER_H

#include <stddef.h>
#include <stdint.h>

/*
 * Возвращает размер декодированного буфера
 * Принимает буфер закодированных данных, его размер и буфер для декодирования
 */
size_t decode(uint8_t *todecbuf, size_t size, uint8_t *decbuf);

#endif/*DECODER_H*/
