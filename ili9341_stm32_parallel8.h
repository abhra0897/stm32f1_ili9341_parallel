/*
 * ili9341_stm32_parallel8.h
 *
 *  Created on: Sep 29, 2019
 *  Last edited on: May 20, 2020
 *      Author: Avra
 */
#include "../../FontsEmbedded/bitmap_typedefs.h"
#include "stm32f1xx_hal.h"

#ifndef INC_ILI9341_STM32_PARALLEL8_H_
#define INC_ILI9341_STM32_PARALLEL8_H_


#define ILI_NOP     0x00
#define ILI_SWRESET 0x01
#define ILI_RDDID   0xD3
#define ILI_RDDST   0x09

#define ILI_SLPIN   0x10
#define ILI_SLPOUT  0x11
#define ILI_PTLON   0x12
#define ILI_NORON   0x13

#define ILI_RDMODE  0x0A
#define ILI_RDMADCTL  0x0B
#define ILI_RDPIXFMT  0x0C
#define ILI_RDIMGFMT  0x0D
#define ILI_RDSELFDIAG  0x0F

#define ILI_INVOFF  0x20
#define ILI_INVON   0x21
#define ILI_GAMMASET 0x26
#define ILI_DISPOFF 0x28
#define ILI_DISPON  0x29

#define ILI_CASET   0x2A
#define ILI_PASET   0x2B
#define ILI_RAMWR   0x2C
#define ILI_RAMRD   0x2E

#define ILI_PTLAR   0x30
#define ILI_MADCTL  0x36
#define ILI_PIXFMT  0x3A

#define ILI_FRMCTR1 0xB1
#define ILI_FRMCTR2 0xB2
#define ILI_FRMCTR3 0xB3
#define ILI_INVCTR  0xB4
#define ILI_DFUNCTR 0xB6

#define ILI_PWCTR1  0xC0
#define ILI_PWCTR2  0xC1
#define ILI_PWCTR3  0xC2
#define ILI_PWCTR4  0xC3
#define ILI_PWCTR5  0xC4
#define ILI_VMCTR1  0xC5
#define ILI_VMCTR2  0xC7

#define ILI_RDID1   0xDA
#define ILI_RDID2   0xDB
#define ILI_RDID3   0xDC
#define ILI_RDID4   0xDD

#define ILI_GMCTRP1 0xE0
#define ILI_GMCTRN1 0xE1
/*
#define ILI_PWCTR6  0xFC
*/


// Color definitions
#define ILI_COLOR_BLACK       0x0000  ///<   0,   0,   0
#define ILI_COLOR_NAVY        0x000F  ///<   0,   0, 123
#define ILI_COLOR_DARKGREEN   0x03E0  ///<   0, 125,   0
#define ILI_COLOR_DARKCYAN    0x03EF  ///<   0, 125, 123
#define ILI_COLOR_MAROON      0x7800  ///< 123,   0,   0
#define ILI_COLOR_PURPLE      0x780F  ///< 123,   0, 123
#define ILI_COLOR_OLIVE       0x7BE0  ///< 123, 125,   0
#define ILI_COLOR_LIGHTGREY   0xC618  ///< 198, 195, 198
#define ILI_COLOR_DARKGREY    0x7BEF  ///< 123, 125, 123
#define ILI_COLOR_BLUE        0x001F  ///<   0,   0, 255
#define ILI_COLOR_GREEN       0x07E0  ///<   0, 255,   0
#define ILI_COLOR_CYAN        0x07FF  ///<   0, 255, 255
#define ILI_COLOR_RED         0xF800  ///< 255,   0,   0
#define ILI_COLOR_MAGENTA     0xF81F  ///< 255,   0, 255
#define ILI_COLOR_YELLOW      0xFFE0  ///< 255, 255,   0
#define ILI_COLOR_WHITE       0xFFFF  ///< 255, 255, 255
#define ILI_COLOR_ORANGE      0xFD20  ///< 255, 165,   0
#define ILI_COLOR_GREENYELLOW 0xAFE5  ///< 173, 255,  41
#define ILI_COLOR_PINK        0xFC18  ///< 255, 130, 198


/**
 * Pin mapping:
 * ILI9341				STM32
 * ---------------------------
* 		--Data--
 * DB10					PA0
 * DB11					PA1
 * ..					..
 * DB17					PA7
 *
 *		--Control--
 * RESETn				PB0
 * CSn					PB1
 * D/Cn					PB5
 * WRn					PB4
 * RDn					PB3
 */
#define ILI_PORT_DATA	GPIOA
#define ILI_PORT_CTRL	GPIOB
#define ILI_RST			GPIO_PIN_0
#define ILI_CS			GPIO_PIN_1
#define ILI_DC			GPIO_PIN_5
#define ILI_WR			GPIO_PIN_4
#define ILI_RD			GPIO_PIN_3

#define RD_ACTIVE		ILI_PORT_CTRL->BRR = (uint32_t)ILI_RD
#define RD_IDLE			ILI_PORT_CTRL->BSRR = (uint32_t)ILI_RD
#define WR_ACTIVE		ILI_PORT_CTRL->BRR = (uint32_t)ILI_WR
#define WR_IDLE			ILI_PORT_CTRL->BSRR = (uint32_t)ILI_WR
#define DC_CMD			ILI_PORT_CTRL->BRR = (uint32_t)ILI_DC
#define DC_DAT			ILI_PORT_CTRL->BSRR = (uint32_t)ILI_DC
#define CS_ACTIVE		ILI_PORT_CTRL->BRR = (uint32_t)ILI_CS
#define CS_IDLE			ILI_PORT_CTRL->BSRR = (uint32_t)ILI_CS
#define RST_ACTIVE		ILI_PORT_CTRL->BRR = (uint32_t)ILI_RST
#define RST_IDLE		ILI_PORT_CTRL->BSRR = (uint32_t)ILI_RST

#define WR_STROBE		{WR_ACTIVE; WR_IDLE;}
#define RD_STROBE		{RD_ACTIVE; RD_IDLE;}

#define WRITE_8BIT(d)	{ILI_PORT_DATA->BSRR = (uint32_t)(0x00FF0000 | ((d) & 0xFF)); WR_STROBE;}
#define READ_8BIT(d)	{d = (uint8_t)(ILI_PORT_DATA->IDR & 0x00FF;}

#define SWAP(a, b)		{uint16_t temp; temp = a; a = b; b = temp;}

/*
* function prototypes
*/

/*
inline void write_command_8bit(uint8_t cmd);
inline void write_data_8bit(uint8_t dat);
inline void write_data_16bit(uint16_t dat);
*/

static inline void write_command_8bit(uint8_t cmd)
{
	//CS_ACTIVE;
	DC_CMD;
	WRITE_8BIT(cmd);
}

static inline void write_data_8bit(uint8_t dat)
{
	//CS_ACTIVE;
	DC_DAT;
	WRITE_8BIT(dat);
}


static inline void write_data_16bit(uint16_t dat)
{
	//CS_ACTIVE;
	DC_DAT;
	WRITE_8BIT((uint8_t)(dat >> 8));
	WRITE_8BIT((uint8_t)dat);
}


void ili_set_address_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void ili_fill_color(uint16_t color, uint32_t len);
void ili_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);
void plot_line_low(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);
void plot_line_high(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);
void ili_draw_fast_h_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);
void ili_draw_fast_v_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);
void ili_rotate_display(uint8_t rotation);
void ili_init();

void ili_fill_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ili_fill_rect_fast(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t color);
void ili_fill_screen(uint16_t color);
void ili_draw_char(uint16_t x, uint16_t y, uint16_t fore_color, uint16_t back_color, const tImage *glyph, uint8_t is_bg);
void ili_draw_string_main(uint16_t x, uint16_t y, char *str, uint16_t fore_color, uint16_t back_color, tFont *font, uint8_t is_bg);
void ili_draw_string(uint16_t x, uint16_t y, char *str, uint16_t color, tFont *font);
void ili_draw_string_withbg(uint16_t x, uint16_t y, char *str, uint16_t fore_color, uint16_t back_color, tFont *font);
void ili_draw_bitmap(uint16_t x, uint16_t y, const tImage16bit *bitmap);

void ili_fill_rect_colors_array(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t *color_p);
void ili_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
//------------------------------------------------------------------------
#endif /* INC_ILI9341_STM32_PARALLEL8_H_ */
