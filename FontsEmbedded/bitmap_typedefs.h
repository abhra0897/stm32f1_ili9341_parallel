/*
 * bitmap_typedefs.h
 *
 *  Created on: Nov 1, 2019
 *      Author: rik
 */

#ifndef INC_BITMAP_TYPEDEFS_H_
#define INC_BITMAP_TYPEDEFS_H_

#include <stdint.h>
#include <inttypes.h>

 typedef struct {
     const uint8_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
     } tImage;

 typedef struct {
	  const uint16_t *data;
	  uint16_t width;
	  uint16_t height;
	  uint8_t dataSize;
	  } tImage16bit;
 typedef struct {
     long int code;
     const tImage *image;
     } tChar;
 typedef struct {
     int length;
     const tChar *chars;
     } tFont;

#endif /* INC_BITMAP_TYPEDEFS_H_ */
