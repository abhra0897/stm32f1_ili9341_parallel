


## ILI9341 Parallel Display Driver for STM32F1
This is a fast display driver for interfacing ILI9341 LCD display with STM32F1 microcontroller over an 8bit parallel (8080-II) bus. It's mainly written for my personal usage.

GPIOs are handled by direct register manipulation for faster performance. *This driver now configures the used GPIOs, so user need not do it anymore*.

This driver needs **[libopencm3](https://github.com/libopencm3/libopencm3.git)** library. The library is provided with this repository. You may get the latest version of libopencm3 from [here](https://github.com/libopencm3/libopencm3.git), but that may or may not work depending on the changes made in libopencm3 latest version.

### Download
Download this repository using [git](https://git-scm.com/):

```
git clone https://github.com/abhra0897/stm32f1_ili9341_parallel.git
```

### Wiring
Connections between STM32F1 and ILI9341 parallel display.
<table border=1>
    <tr>
        <th colspan=2>ILI9341</th>
        <th rowspan=2>STM32F1</th>
    </tr>
    <tr>
        <td>8080-I 8-bit</td>
        <td>8080-II 8-bit</td>
    </tr>
    <tr>
        <td>D0</td>
        <td>D10</td>
        <td>PA0</td>
    </tr>
    <tr>
        <td>D1</td>
        <td>D11</td>
        <td>PA1</td>
    </tr>
    <tr>
        <td>D2</td>
        <td>D12</td>
        <td>PA2</td>
    </tr>
    <tr>
        <td>D3</td>
        <td>D13</td>
        <td>PA3</td>
    </tr>
    <tr>
        <td>D4</td>
        <td>D14</td>
        <td>PA4</td>
    </tr>
    <tr>
        <td>D5</td>
        <td>D15</td>
        <td>PA5</td>
    </tr>
    <tr>
        <td>D6</td>
        <td>D16</td>
        <td>PA6</td>
    </tr>
    <tr>
        <td>D7</td>
        <td>D17</td>
        <td>PA7</td>
    </tr>
    <tr>
        <td colspan=2 align=center>RESX</td>
        <td>PB0</td>
    </tr>
    <tr>
        <td colspan=2 align=center>CSX</td>
        <td>PB1</td>
    </tr>
    <tr>
        <td colspan=2 align=center>D/CX</td>
        <td>PB5</td>
    </tr>
    <tr>
        <td colspan=2 align=center>WRX</td>
        <td>PB4</td>
    </tr>
    <tr>
        <td colspan=2 align=center>RDX</td>
        <td>PB3</td>
    </tr>
</table>

### Benchmarks
TBD

### Example
Example code (**[main.c](example/main.c)**) is in **[example](example)** directory. To compile using the provided [Makefile](example/Makefile), keep the directory structure as it is. If you change the directory structure, edit the SRCS, INCLS, and LIBS in the Makefile accordingly.
Example is compiled and tested on STM32F103 (overclocked to 128MHz)

![Output of example code](example/photo/example_output.gif)

### Important API Methods

```C
/**
 * Initialize the display driver
 */
void ili_init();

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
 * Rotate the display clockwise or anti-clockwie set by `rotation`
 * @param rotation Type of rotation. Supported values 0, 1, 2, 3
 */
void ili_rotate_display(uint8_t rotation);

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
void ili_fill_rect_fast(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t color);

/**
 * Fill the entire display (screen) with `color`
 * @param color 16-bit RGB565 color
 */
void ili_fill_screen(uint16_t color);

/**
 * Experimental
 * Draw a rectangle without filling it
 * @param x start column address.
 * @param y start row address
 * @param w Width of rectangle
 * @param h height of rectangle
 */
void ili_draw_rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

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

/**
 * Draw a pixel at a given position with `color`
 * @param x Start col address
 * @param y Start row address
 */
void ili_draw_pixel(uint16_t x, uint16_t y, uint16_t color);

```
### TO DO

 - [x] Add example code(s) and write some docs
 - [x] Write better comments
 - [ ] Explain how to create fonts
 - [ ] Optimize driver for speed and size. Speed is the first priority
 - [ ] Add ability to read from the display
 - [ ] Circle drawing support (maybe)

### License
**[libopencm3](libopencm3)** and any derivative of the same are licensed under the terms of the GNU Lesser General Public License (LGPL), version 3 or later. The binaries generated after compilation will also be licensed under the same. See [this](libopencm3/COPYING.LGPL3) and [this](libopencm3/COPYING.GPL3) for the LGPL3 and GPL3 licenses.

All other source codes of the root directory and example directory are licensed under MIT License, unless the source file has no other license asigned for it. See [MIT License](LICENSE).
