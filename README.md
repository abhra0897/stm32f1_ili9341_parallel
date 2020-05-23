


## ILI9341 Parallel Display Driver for STM32F1
This is a fast display driver for interfacing ILI9341 LCD display with STM32F1 microcontroller over an 8bit parallel (8080-II) bus. It's mainly written for my personal usage.

GPIOs are handled by direct register manipulation for faster performance. As this driver doesn't configure the GPIOs, *user must configure the used ports and pins before using the driver.*

This driver needs STM32 HAL library. To avoid using HAL, replace "HAL_Delay(ms)" with any other delay(ms) function.

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
Example code will be in examples directory.
TBD

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
 * @param x1 Start col address
 * @param y1 Start row address
 * @param x2 End col address
 * @param y2 End row address
 */
void ili_fill_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

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
void ili_draw_bitmap(uint16_t x, uint16_t y, const tImage16bit *bitmap);

/**
 * Draw a pixel at a given position with `color`
 * @param x Start col address
 * @param y Start row address
 */
void ili_draw_pixel(uint16_t x, uint16_t y, uint16_t color);

```
### TO DO

 - [ ] Add example code(s) and write some docs
 - [ ] Write better comments
 - [ ] Explain how to create fonts
 - [ ] Optimize driver for speed and size. Speed is the first priority
 - [ ] Add ability to read from the display
 - [ ] Circle drawing support (maybe)

### License
The MIT License (MIT)

Copyright (c) 2020 Avra Mitra

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.