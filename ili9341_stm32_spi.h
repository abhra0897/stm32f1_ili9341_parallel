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

#include "fonts/bitmap_typedefs.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/dma.h>

#ifndef INC_ILI9341_STM32_SPI_H_
#define INC_ILI9341_STM32_SPI_H_

#ifdef DSO138_PLATFORM
	#warning SPI interface doesn't support DSO138 platform. Include parallel interface header instead.
#endif

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


#define	ILI_R_POS_RGB   11	// Red last bit position for RGB display
#define	ILI_G_POS_RGB   5 	// Green last bit position for RGB display
#define	ILI_B_POS_RGB   0	// Blue last bit position for RGB display

#define	ILI_RGB(R,G,B) \
	(((uint16_t)(R >> 3) << ILI_R_POS_RGB) | \
	((uint16_t)(G >> 2) << ILI_G_POS_RGB) | \
	((uint16_t)(B >> 3) << ILI_B_POS_RGB))

#define	ILI_R_POS_BGR   0	// Red last bit position for BGR display
#define	ILI_G_POS_BGR   5 	// Green last bit position for BGR display
#define	ILI_B_POS_BGR   11	// Blue last bit position for BGR display

#define	ILI_BGR(R,G,B) \
	(((uint16_t)(R >> 3) << ILI_R_POS_BGR) | \
	((uint16_t)(G >> 2) << ILI_G_POS_BGR) | \
	((uint16_t)(B >> 3) << ILI_B_POS_BGR))


// Color definitions
#define ILI_COLOR_BLACK       ILI_RGB(0,     0,   0)
#define ILI_COLOR_NAVY        ILI_RGB(0,     0, 123)
#define ILI_COLOR_DARKGREEN   ILI_RGB(0,   125,   0)
#define ILI_COLOR_DARKCYAN    ILI_RGB(0,   125, 123)
#define ILI_COLOR_MAROON      ILI_RGB(123,   0,   0)
#define ILI_COLOR_PURPLE      ILI_RGB(123,   0, 123)
#define ILI_COLOR_OLIVE       ILI_RGB(123, 125,   0)
#define ILI_COLOR_LIGHTGREY   ILI_RGB(198, 195, 198)
#define ILI_COLOR_DARKGREY    ILI_RGB(123, 125, 123)
#define ILI_COLOR_BLUE        ILI_RGB(0,     0, 255)
#define ILI_COLOR_GREEN       ILI_RGB(0,   255,   0)
#define ILI_COLOR_CYAN        ILI_RGB(0,   255, 255)
#define ILI_COLOR_RED         ILI_RGB(255,   0,   0)
#define ILI_COLOR_MAGENTA     ILI_RGB(255,   0, 255)
#define ILI_COLOR_YELLOW      ILI_RGB(255, 255,   0)
#define ILI_COLOR_WHITE       ILI_RGB(255, 255, 255)
#define ILI_COLOR_ORANGE      ILI_RGB(255, 165,   0)
#define ILI_COLOR_GREENYELLOW ILI_RGB(173, 255,  41)
#define ILI_COLOR_PINK        ILI_RGB(255, 130, 198)


/*************************** Pin confirugation START ************************/

/**
 * Pin mapping:
 * ILI9341				STM32
 * ---------------------------
 * SDA					PA7
 * SCL					PA5				..			
 * RESETn				PA4
 * D/Cn					PA2
 * BLK					PA3
 * CSn					--
 */
#define ILI_USE_SPI_DMA
#define ILI_HAS_RST
//#define ILI_HAS_CS
#ifdef ILI_HAS_CS
//	#define ILI_RELEASE_WHEN_IDLE
#endif

#define ILI_SPI			SPI1
#ifdef ILI_USE_SPI_DMA
	#define ILI_DMA			DMA1
	#define ILI_DMA_CHANNEL	3
#endif

#define ILI_PORT			GPIOA

#define ILI_RST			GPIO4
#define ILI_DC			GPIO2
#define ILI_SDA			GPIO7
#define ILI_SCL			GPIO5
#define ILI_BLK			GPIO3
// To use Chip Select (CS), uncomment `ILI_HAS_CS` above
#define ILI_CS			GPIO6

#define JTAG_REMAPPING_MODE AFIO_MAPR_SWJ_CFG_FULL_SWJ_NO_JNTRST /* See below */


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

#define ILI_DC_CMD			GPIO_BRR(ILI_PORT) = ILI_DC
#define ILI_DC_DAT			GPIO_BSRR(ILI_PORT) = ILI_DC
#define ILI_RST_ACTIVE		GPIO_BRR(ILI_PORT) = ILI_RST
#define ILI_RST_IDLE		GPIO_BSRR(ILI_PORT) = ILI_RST
#ifdef ILI_HAS_CS
	#define ILI_CS_ACTIVE		GPIO_BRR(ILI_PORT) = ILI_CS
	#define ILI_CS_IDLE			GPIO_BSRR(ILI_PORT) = ILI_CS
#endif

#define ILI_CONFIG_GPIO_CLOCK()	{ \
									rcc_periph_clock_enable(RCC_GPIOA); \
									rcc_periph_clock_enable(RCC_AFIO); \
									rcc_periph_clock_enable(RCC_SPI1); \
									rcc_periph_clock_enable(RCC_DMA1); \
								}
#ifdef ILI_HAS_CS
	#define ILI_CONFIG_GPIO()		{ \
										/*Configure GPIO pins : PA2 PA3 PA4 PA5 PA7 */ \
										gpio_set_mode(ILI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, ILI_SCL|ILI_SDA); \
										gpio_set_mode(ILI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, ILI_DC|ILI_BLK|ILI_RST|ILI_CS); \
										/*Configure GPIO pin Output Level */ \
										gpio_set(ILI_PORT, ILI_BLK|ILI_RST|ILI_DC|ILI_CS); \
										/* Configures PB4 as GPIO */ \
										AFIO_MAPR |= JTAG_REMAPPING_MODE; \
									}
#else
	#define ILI_CONFIG_GPIO()		{ \
										/*Configure GPIO pins : PA2 PA3 PA4 PA5 PA7 */ \
										gpio_set_mode(ILI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, ILI_SCL|ILI_SDA); \
										gpio_set_mode(ILI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, ILI_DC|ILI_BLK|ILI_RST); \
										/*Configure GPIO pin Output Level */ \
										gpio_set(ILI_PORT, ILI_BLK|ILI_RST|ILI_DC); \
										/* Configures PB4 as GPIO */ \
										AFIO_MAPR |= JTAG_REMAPPING_MODE; \
									}
#endif

#define ILI_CONFIG_SPI()			{ \
									/* Reset SPI, SPI_CR1 register cleared, SPI is disabled */ \
									spi_reset(ILI_SPI); \
									SPI_I2SCFGR(ILI_SPI) = 0; \
									/* Must use SPI_MODE = 2. (CPOL 1, CPHA 0) */\
									/* Read about SPI MODEs: https://en.wikipedia.org/wiki/Serial_Peripheral_Interface*/ \
									spi_init_master(ILI_SPI, SPI_CR1_BAUDRATE_FPCLK_DIV_2, SPI_CR1_CPOL_CLK_TO_1_WHEN_IDLE, SPI_CR1_CPHA_CLK_TRANSITION_1, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST); \
									spi_enable_software_slave_management(ILI_SPI); \
									spi_set_full_duplex_mode(ILI_SPI); \
									spi_set_nss_high(ILI_SPI); \
									/* Enable SPI1 periph. */ \
									spi_enable(ILI_SPI); \
								}


#define ILI_SWAP(a, b)		{uint16_t temp; temp = a; a = b; b = temp;}


// Either use TXE and BSY flag check to ensure transaction completes, 
// or use nops to get higher fps. Add more nops if display is not working properly
// Remove nops if fps is too low. 
// Rule of thumb: If optimization flag value is set to higher, and/or MCU is overclocked, then increase nops

// Note: If display shows wrong output, either change number of nops as said above,
//		 or uncomment TXE and BSY flag checks and comment out all nops.
#define ILI_WRITE_8BIT(d)	do{ \
							SPI_DR(ILI_SPI) = (uint8_t)(d); \
							/*while (!(SPI_SR(ST_SPI) & SPI_SR_TXE));*/ \
							/*while (SPI_SR(ST_SPI) & SPI_SR_BSY);*/ \
							__asm__("nop"); __asm__("nop"); __asm__("nop"); __asm__("nop"); \
							__asm__("nop"); __asm__("nop"); __asm__("nop"); __asm__("nop"); \
							__asm__("nop"); __asm__("nop"); __asm__("nop"); __asm__("nop"); \
							__asm__("nop"); __asm__("nop"); __asm__("nop"); __asm__("nop"); \
							__asm__("nop"); __asm__("nop"); __asm__("nop"); __asm__("nop"); \
						} while(0)

#ifdef ILI_USE_SPI_DMA

	#define ILI_CONFIG_SPI_DMA()		{ \
									/* DMA Peripheral address set to SPI*/ \
									DMA_CPAR(ILI_DMA, ILI_DMA_CHANNEL) = (uint32_t)&SPI_DR(ILI_SPI); \
									/* Dma memory address is reset */ \
									DMA_CMAR(ILI_DMA, ILI_DMA_CHANNEL) = 0; \
									/* Number of data transfer is reset */ \
									DMA_CNDTR(ILI_DMA, ILI_DMA_CHANNEL) = 0; \
									/* DMA priority is high */ \
									DMA_CCR(ILI_DMA, ILI_DMA_CHANNEL) = DMA_CCR_PL_HIGH; \
									/* Data transfer direction: Read from memory */ \
									DMA_CCR(ILI_DMA, ILI_DMA_CHANNEL) |= DMA_CCR_DIR; \
									/* Disable circular DMA */ \
									DMA_CCR(ILI_DMA, ILI_DMA_CHANNEL) &= ~DMA_CCR_CIRC; \
									/* peripheral increment disabled */\
									DMA_CCR(ILI_DMA, ILI_DMA_CHANNEL) &= ~DMA_CCR_PINC; \
									/* memory increment enabled */ \
									DMA_CCR(ILI_DMA, ILI_DMA_CHANNEL) |= DMA_CCR_MINC; \
									/* peripheral and memory data size set to 8 bit */ \
									DMA_CCR(ILI_DMA, ILI_DMA_CHANNEL) |= DMA_CCR_PSIZE_8BIT | DMA_CCR_MSIZE_8BIT; \
								}

	__attribute__((always_inline)) static inline void _ili_write_spi_dma(void *data_addr, uint16_t length)
	{
		// Set memory source address
		DMA_CMAR(ILI_DMA, ILI_DMA_CHANNEL) = (uint32_t)data_addr;
		// set data count
		DMA_CNDTR(ILI_DMA, ILI_DMA_CHANNEL) = length;

		// Enable DMA channel 
		DMA_CCR(ILI_DMA, ILI_DMA_CHANNEL) |= DMA_CCR_EN;
		// Enable SPI DMA. This will start the DMA transaction
		SPI_CR2(ILI_SPI) |= SPI_CR2_TXDMAEN;

		// wait until all data is sent (count becomes 0)
		while (DMA_CNDTR(ILI_DMA, ILI_DMA_CHANNEL));
		// Wait until tx buffer is empty (not set)
		while (!(SPI_SR(ILI_SPI) & SPI_SR_TXE));
		// Wait until bus is not busy
		while (SPI_SR(ILI_SPI) & SPI_SR_BSY);

		// Disable SPI DMA tx
		SPI_CR2(ILI_SPI) &= ~SPI_CR2_TXDMAEN;
		// Disable DMA channel
		DMA_CCR(ILI_DMA, ILI_DMA_CHANNEL) &= ~DMA_CCR_EN;
	}

#endif


__attribute__((always_inline)) static inline void _ili_write_command_8bit(uint8_t cmd)
{
	#ifdef ILI_RELEASE_WHEN_IDLE
		ILI_ACTIVE;
	#endif
	ILI_DC_CMD;
	ILI_WRITE_8BIT(cmd);
	#ifdef ILI_RELEASE_WHEN_IDLE
		ILI_IDLE;
	#endif
}

/*
 * inline function to send 8 bit data to the display
 * User need not call it
 */
__attribute__((always_inline)) static inline void _ili_write_data_8bit(uint8_t dat)
{
	#ifdef ILI_RELEASE_WHEN_IDLE
		ILI_ACTIVE;
	#endif
	ILI_DC_CMD;
	ILI_WRITE_8BIT(dat);
	#ifdef ILI_RELEASE_WHEN_IDLE
		ILI_IDLE;
	#endif
}

/*
 * inline function to send 16 bit data to the display
 * User need not call it
 */
__attribute__((always_inline)) static inline void _ili_write_data_16bit(uint16_t dat)
{
	#ifdef ILI_RELEASE_WHEN_IDLE
		ILI_ACTIVE;
	#endif
	ILI_DC_CMD;
	ILI_WRITE_8BIT((uint8_t)(dat >> 8));
	ILI_WRITE_8BIT((uint8_t)dat);
	#ifdef ILI_RELEASE_WHEN_IDLE
		ILI_IDLE;
	#endif
}

/*
* function prototypes
*/

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
void _ili_plot_line_low(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);

/*
 * Called by ili_draw_line().
 * User need not call it
 */
void _ili_plot_line_high(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);

/*
 * Called by ili_draw_line().
 * User need not call it
 */
void _ili_draw_fast_h_line(uint16_t x0, uint16_t y0, uint16_t x1, uint8_t width, uint16_t color);

/*
 * Called by ili_draw_line().
 * User need not call it
 */
void _ili_draw_fast_v_line(uint16_t x0, uint16_t y0, uint16_t y1, uint8_t width, uint16_t color);

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
 * Render a character glyph on the display. Called by `ili_draw_string_main()`
 * User need NOT call it
 */
void _ili_render_glyph(uint16_t x, uint16_t y, uint16_t fore_color, uint16_t back_color, const tImage *glyph, uint8_t is_bg);

/**
 * Renders a string by drawing each character glyph from the passed string.
 * Called by `ili_draw_string()` and `ili_draw_string_withbg()`.
 * Text is wrapped automatically if it hits the screen boundary.
 * x_padding and y_padding defines horizontal and vertical distance (in px) between two characters
 * is_bg=1 : Text will habe background color,   is_bg=0 : Text will have transparent background
 * User need NOT call it.
 */
void _ili_draw_string_main(uint16_t x, uint16_t y, char *str, uint16_t fore_color, uint16_t back_color, const tFont *font, uint8_t is_bg);

/**
 * Draws a string on the display with `font` and `color` at given position.
 * Background of this string is transparent
 * @param x Start col address
 * @param y Start y address
 * @param str pointer to the string to be drawn
 * @param color 16-bit RGB565 color of the string
 * @param font Pointer to the font of the string
 */
void ili_draw_string(uint16_t x, uint16_t y, char *str, uint16_t color, const tFont *font);

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
void ili_draw_string_withbg(uint16_t x, uint16_t y, char *str, uint16_t fore_color, uint16_t back_color, const tFont *font);

/**
 * Draws a character at a given position, fore color, back color.
 * @param x Start col address
 * @param y Start row address
 * @param character the ASCII character to be drawn
 * @param fore_color foreground color
 * @param back_color background color
 * @param font Pointer to the font of the character
 * @param is_bg Defines if character has background or not (transparent)
 */
void ili_draw_char(uint16_t x, uint16_t y, char character, uint16_t fore_color, uint16_t back_color, const tFont *font, uint8_t is_bg);

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
