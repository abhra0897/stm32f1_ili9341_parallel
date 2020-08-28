/*
MIT License

Copyright (c) 2020 Avra Mitra

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include "bitmap_typedefs.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

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

#ifdef USER_DEFAULT_PLATFORM
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

#elif DSO138_PLATFORM
    #define	R_POS_RGB   11	// Red last bit position for RGB display
    #define	G_POS_RGB   5 	// Green last bit position for RGB display
    #define	B_POS_RGB   0	// Blue last bit position for RGB display

    #define	RGB(R,G,B) \
	(((uint16_t)(R >> 3) << R_POS_RGB) | \
	 ((uint16_t)(G >> 2) << G_POS_RGB) | \
	 ((uint16_t)(B >> 3) << B_POS_RGB))

    #define	R_POS_BGR   0	// Red last bit position for BGR display
    #define	G_POS_BGR   5 	// Green last bit position for BGR display
    #define	B_POS_BGR   11	// Blue last bit position for BGR display

    #define	BGR(R,G,B) \
	(((uint16_t)(R >> 3) << R_POS_BGR) | \
	 ((uint16_t)(G >> 2) << G_POS_BGR) | \
         ((uint16_t)(B >> 3) << B_POS_BGR))

    #define ILI_COLOR_BLACK       BGR(0,     0,   0)
    #define ILI_COLOR_NAVY        BGR(0,     0, 123)
    #define ILI_COLOR_DARKGREEN   BGR(0,   125,   0)
    #define ILI_COLOR_DARKCYAN    BGR(0,   125, 123)
    #define ILI_COLOR_MAROON      BGR(123,   0,   0)
    #define ILI_COLOR_PURPLE      BGR(123,   0, 123)
    #define ILI_COLOR_OLIVE       BGR(123, 125,   0)
    #define ILI_COLOR_LIGHTGREY   BGR(198, 195, 198)
    #define ILI_COLOR_DARKGREY    BGR(123, 125, 123)
    #define ILI_COLOR_BLUE        BGR(0,     0, 255)
    #define ILI_COLOR_GREEN       BGR(0,   255,   0)
    #define ILI_COLOR_CYAN        BGR(0,   255, 255)
    #define ILI_COLOR_RED         BGR(255,   0,   0)
    #define ILI_COLOR_MAGENTA     BGR(255,   0, 255)
    #define ILI_COLOR_YELLOW      BGR(255, 255,   0)
    #define ILI_COLOR_WHITE       BGR(255, 255, 255)
    #define ILI_COLOR_ORANGE      BGR(255, 165,   0)
    #define ILI_COLOR_GREENYELLOW BGR(173, 255,  41)
    #define ILI_COLOR_PINK        BGR(255, 130, 198)
#endif

/*************************** Pin confirugation START ************************/
#ifdef USER_DEFAULT_PLATFORM
	/*
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
	* D/Cn					PB5#include <libopencm3/stm32/rcc.h>
	* WRn					PB4
	* RDn					PB3
	*/
	#define ILI_PORT_DATA	GPIOA
	#define ILI_D0  		GPIO0
	#define ILI_D1  		GPIO1
	#define ILI_D2          GPIO2
	#define ILI_D3  		GPIO3
	#define ILI_D4			GPIO4
	#define ILI_D5			GPIO5
	#define ILI_D6			GPIO6
	#define ILI_D7			GPIO7
	#define ILI_PORT_CTRL	GPIOB
	#define ILI_RST			GPIO0
	#define ILI_CS			GPIO1
	#define ILI_DC			GPIO5
	#define ILI_WR			GPIO4
	#define ILI_RD			GPIO3
	#define JTAG_REMAPPING_MODE AFIO_MAPR_SWJ_CFG_FULL_SWJ_NO_JNTRST /* See below */

#elif DSO138_PLATFORM
	#define ILI_PORT_DATA	GPIOB
	#define ILI_D0			GPIO0
	#define ILI_D1			GPIO1
	#define ILI_D2			GPIO2
	#define ILI_D3			GPIO3
	#define ILI_D4			GPIO4
	#define ILI_D5			GPIO5
	#define ILI_D6			GPIO6
	#define ILI_D7			GPIO7
	#define ILI_PORT_CTRL_B	GPIOB
	#define ILI_RD			GPIO10
	#define ILI_RST			GPIO11
	#define ILI_PORT_CTRL_C	GPIOC
	#define ILI_CS			GPIO13
	#define ILI_DC			GPIO14
	#define ILI_WR			GPIO15
	#define JTAG_REMAPPING_MODE AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_OFF /* See below */
#endif
/*
Possible values of JTAG_REMAPPING_MODE:
AFIO_MAPR_SWJ_CFG_FULL_SWJ: Full Serial Wire JTAG capability
AFIO_MAPR_SWJ_CFG_FULL_SWJ_NO_JNTRST: Full Serial Wire JTAG capability without JNTRST (PB4 as GPIO)
AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_ON: JTAG-DP disabled with SW-DP enabled
AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_OFF: JTAG-DP disabled and SW-DP disabled
*/

/*
 * >>>>>> ATTENTION: if there are other ports in use, e.g. GPIOC, <<<<<<
 * >>>>>>   please, update CONFIG_GPIO_CLOCK() and CONFIG_GPIO()  <<<<<<
 * >>>>>>              macros below accordingly.                  <<<<<<
 */
/*************************** Pin confirugation END ************************/

#ifdef USER_DEFAULT_PLATFORM
	#define RD_ACTIVE		GPIO_BRR(ILI_PORT_CTRL) = ILI_RD
	#define RD_IDLE			GPIO_BSRR(ILI_PORT_CTRL) = ILI_RD
	#define WR_ACTIVE		GPIO_BRR(ILI_PORT_CTRL) = ILI_WR
	#define WR_IDLE			GPIO_BSRR(ILI_PORT_CTRL) = ILI_WR
	#define DC_CMD			GPIO_BRR(ILI_PORT_CTRL) = ILI_DC
	#define DC_DAT			GPIO_BSRR(ILI_PORT_CTRL) = ILI_DC
	#define CS_ACTIVE		GPIO_BRR(ILI_PORT_CTRL) = ILI_CS
	#define CS_IDLE			GPIO_BSRR(ILI_PORT_CTRL) = ILI_CS
	#define RST_ACTIVE		GPIO_BRR(ILI_PORT_CTRL) = ILI_RST
	#define RST_IDLE		GPIO_BSRR(ILI_PORT_CTRL) = ILI_RST
#elif DSO138_PLATFORM
	#define RD_ACTIVE		GPIO_BRR(ILI_PORT_CTRL_B) = ILI_RD
	#define RD_IDLE			GPIO_BSRR(ILI_PORT_CTRL_B) = ILI_RD
	#define WR_ACTIVE		GPIO_BRR(ILI_PORT_CTRL_C) = ILI_WR
	#define WR_IDLE			GPIO_BSRR(ILI_PORT_CTRL_C) = ILI_WR
	#define DC_CMD			GPIO_BRR(ILI_PORT_CTRL_C) = ILI_DC
	#define DC_DAT			GPIO_BSRR(ILI_PORT_CTRL_C) = ILI_DC
	#define CS_ACTIVE		GPIO_BRR(ILI_PORT_CTRL_C) = ILI_CS
	#define CS_IDLE			GPIO_BSRR(ILI_PORT_CTRL_C) = ILI_CS
	#define RST_ACTIVE		GPIO_BRR(ILI_PORT_CTRL_B) = ILI_RST
	#define RST_IDLE		GPIO_BSRR(ILI_PORT_CTRL_B) = ILI_RST
#endif

#define WR_STROBE		{WR_ACTIVE; WR_IDLE;}
#define RD_STROBE		{RD_ACTIVE; RD_IDLE;}

#define WRITE_8BIT(d)	{GPIO_BSRR(ILI_PORT_DATA) = (uint32_t)(0x00FF0000 | ((d) & 0xFF)); WR_STROBE;}
#define READ_8BIT(d)	{d = (uint8_t)(GPIO_IDR(ILI_PORT_DATA) & 0x00FF;}

#ifdef USER_DEFAULT_PLATFORM
	#define CONFIG_GPIO_CLOCK()	    { \
										rcc_periph_clock_enable(RCC_GPIOB); \
										rcc_periph_clock_enable(RCC_GPIOA); \
										rcc_periph_clock_enable(RCC_AFIO); \
									}
	#define CONFIG_GPIO()			{ \
										/*Configure ILI_PORT_DATA GPIO pins */ \
										gpio_set_mode( \
											ILI_PORT_DATA, \
											GPIO_MODE_OUTPUT_50_MHZ, \
											GPIO_CNF_OUTPUT_PUSHPULL, \
											ILI_D0 | ILI_D1 | ILI_D2 | ILI_D3 | ILI_D4 | ILI_D5 | ILI_D6 | ILI_D7); \
										/*Configure ILI_PORT_CTRL GPIO pins */ \
										gpio_set_mode(ILI_PORT_CTRL, \
											GPIO_MODE_OUTPUT_50_MHZ, \
											GPIO_CNF_OUTPUT_PUSHPULL, \
											ILI_RST | ILI_CS | ILI_DC | ILI_WR | ILI_RD); \
										/*Configure GPIO pin Output Level */ \
										gpio_set( \
											ILI_PORT_DATA, \
											ILI_D0 | ILI_D1 | ILI_D2 | ILI_D3 | ILI_D4 | ILI_D5 | ILI_D6 | ILI_D7); \
										gpio_set( \
											ILI_PORT_CTRL, \
											ILI_RST | ILI_CS | ILI_DC | ILI_WR | ILI_RD); \
										/* Remap JTAG pins */ \
										AFIO_MAPR |= JTAG_REMAPPING_MODE; \
									}
#elif DSO138_PLATFORM
	#define CONFIG_GPIO_CLOCK()	    { \
										rcc_periph_clock_enable(RCC_GPIOB); \
										rcc_periph_clock_enable(RCC_GPIOA); \
										rcc_periph_clock_enable(RCC_GPIOC); \
										rcc_periph_clock_enable(RCC_AFIO); \
									}
	#define CONFIG_GPIO()			{ \
										/*Configure ILI_PORT_DATA GPIO pins */ \
										gpio_set_mode( \
											ILI_PORT_DATA, \
											GPIO_MODE_OUTPUT_50_MHZ, \
											GPIO_CNF_OUTPUT_PUSHPULL, \
											ILI_D0 | ILI_D1 | ILI_D2 | ILI_D3 | ILI_D4 | ILI_D5 | ILI_D6 | ILI_D7); \
										/*Configure ILI_PORT_CTRL_B GPIO pins */ \
										gpio_set_mode(ILI_PORT_CTRL_B, \
											GPIO_MODE_OUTPUT_50_MHZ, \
											GPIO_CNF_OUTPUT_PUSHPULL, \
											ILI_RD | ILI_RST); \
										/*Configure ILI_PORT_CTRL_C GPIO pins */ \
										gpio_set_mode(ILI_PORT_CTRL_C, \
											GPIO_MODE_OUTPUT_50_MHZ, \
											GPIO_CNF_OUTPUT_PUSHPULL, \
											ILI_CS | ILI_DC | ILI_WR); \
										/*Configure GPIO pin Output Level */ \
										gpio_set( \
											ILI_PORT_DATA, \
											ILI_D0 | ILI_D1 | ILI_D2 | ILI_D3 | ILI_D4 | ILI_D5 | ILI_D6 | ILI_D7); \
										gpio_set( \
											ILI_PORT_CTRL_B, \
											ILI_RD | ILI_RST); \
										gpio_set( \
											ILI_PORT_CTRL_C, \
											ILI_CS | ILI_DC | ILI_WR); \
										/* Remap JTAG pins */ \
										AFIO_MAPR |= JTAG_REMAPPING_MODE; \
									}
#endif

#define SWAP(a, b)		{uint16_t temp; temp = a; a = b; b = temp;}

/*
* function prototypes
*/

/*
 * Inline function to send 8 bit command to the display
 * User need not call it
 */
static inline void write_command_8bit(uint8_t cmd)
{
	//CS_ACTIVE;
	DC_CMD;
	WRITE_8BIT(cmd);
}

/*
 * Inline function to send 8 bit data to the display
 * User need not call it
 */
static inline void write_data_8bit(uint8_t dat)
{
	//CS_ACTIVE;
	DC_DAT;
	WRITE_8BIT(dat);
}

/*
 * Inline function to send 16 bit data to the display
 * User need not call it
 */
static inline void write_data_16bit(uint16_t dat)
{
	//CS_ACTIVE;
	DC_DAT;
	WRITE_8BIT((uint8_t)(dat >> 8));
	WRITE_8BIT((uint8_t)dat);
}

/**
 * Set an area for drawing on the display with start row,col and end row,col.
 * User don't need to call it usually, call it only before some functions who don't call it by default.
 * @param x1 start column address.
 * @param y1 start row address.
 * @param x2 end column address.
 * @param y2 end row address.
 */
void ili_set_address_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/**
 * Fills `len` number of pixels with `color`.
 * Call ili_set_address_window() before calling this function.
 * @param color 16-bit RGB565 color value
 * @param len 32-bit number of pixels
 */
void ili_fill_color(uint16_t color, uint32_t len);

/**
 * Draw a line from (x0,y0) to (x1,y1) with `width` and `color`.
 * @param x0 start column address.
 * @param y0 start row address.
 * @param x1 end column address.
 * @param y1 end row address.
 * @param width width or thickness of the line
 * @param color 16-bit RGB565 color of the line
 */
void ili_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);

/**
 * Experimental
 * Draw a rectangle without filling it
 * @param x start column address.
 * @param y start row address
 * @param w Width of rectangle
 * @param h height of rectangle
 */
void ili_draw_rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

/*
 * Called by ili_draw_line().
 * User need not call it
 */
void plot_line_low(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);

/*
 * Called by ili_draw_line().
 * User need not call it
 */
void plot_line_high(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);

/*
 * Called by ili_draw_line().
 * User need not call it
 */
void ili_draw_fast_h_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);

/*
 * Called by ili_draw_line().
 * User need not call it
 */
void ili_draw_fast_v_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);

/**
 * Rotate the display clockwise or anti-clockwie set by `rotation`
 * @param rotation Type of rotation. Supported values 0, 1, 2, 3
 */
void ili_rotate_display(uint8_t rotation);

/**
 * Initialize the display driver
 */
void ili_init();

/**
 * Fills a rectangular area with `color`.
 * Before filling, performs area bound checking
 * @param x Start col address
 * @param y Start row address
 * @param w Width of rectangle
 * @param h Height of rectangle
 * @param color 16-bit RGB565 color
 */
void ili_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

/*
 * Same as `ili_fill_rect()` but does not do bound checking, so it's slightly faster
 */
void ili_fill_rect_fast(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

/**
 * Fill the entire display (screen) with `color`
 * @param color 16-bit RGB565 color
 */
void ili_fill_screen(uint16_t color);

/*
 * Rener a character glyph on the display. Called by `ili_draw_string_main()`
 * User need NOT call it
 */
void ili_draw_char(uint16_t x, uint16_t y, uint16_t fore_color, uint16_t back_color, const tImage *glyph, uint8_t is_bg);

/**
 * Renders a string by drawing each character glyph from the passed string.
 * Called by `ili_draw_string()` and `ili_draw_string_withbg()`.
 * Text is wrapped automatically if it hits the screen boundary.
 * x_padding and y_padding defines horizontal and vertical distance (in px) between two characters
 * is_bg=1 : Text will habe background color,   is_bg=0 : Text will have transparent background
 * User need NOT call it.
 */
void ili_draw_string_main(uint16_t x, uint16_t y, char *str, uint16_t fore_color, uint16_t back_color, tFont *font, uint8_t is_bg);

/**
 * Draws a string on the display with `font` and `color` at given position.
 * Background of this string is transparent
 * @param x Start col address
 * @param y Start y address
 * @param str pointer to the string to be drawn
 * @param color 16-bit RGB565 color of the string
 * @param font Pointer to the font of the string
 */
void ili_draw_string(uint16_t x, uint16_t y, char *str, uint16_t color, tFont *font);

/**
 * Draws a string on the display with `font`, `fore_color`, and `back_color` at given position.
 * The string has background color
 * @param x Start col address
 * @param y Start y address
 * @param str pointer to the string to be drawn
 * @param foe_color 16-bit RGB565 color of the string
 * @param back_color 16-bit RGB565 color of the string's background
 * @param font Pointer to the font of the string
 */
void ili_draw_string_withbg(uint16_t x, uint16_t y, char *str, uint16_t fore_color, uint16_t back_color, tFont *font);

/**
 * Draw a bitmap image on the display
 * @param x Start col address
 * @param y Start row address
 * @param bitmap Pointer to the image data to be drawn
 */
void ili_draw_bitmap(uint16_t x, uint16_t y, const tImage *bitmap);
//void ili_draw_bitmap_old(uint16_t x, uint16_t y, const tImage16bit *bitmap);

/**
 * Draw a pixel at a given position with `color`
 * @param x Start col address
 * @param y Start row address
 */
void ili_draw_pixel(uint16_t x, uint16_t y, uint16_t color);

//------------------------------------------------------------------------
#endif /* INC_ILI9341_STM32_PARALLEL8_H_ */
