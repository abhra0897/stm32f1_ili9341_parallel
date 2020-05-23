/*
 * ili9341_stm32_parallel8.c
 *
 *  Created on: Oct 6, 2019
 *  Last edited on: May 20, 2020
 *      Author: Avra
 */


#include <ili9341_stm32_parallel8.h>

//TFT width and height default global variables
uint16_t ili_tftwidth = 320;
uint16_t ili_tftheight = 240;



/*
 * Set address window to fill with color(s)
 */
void ili_set_address_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	write_command_8bit(ILI_CASET);

	DC_DAT;
	WRITE_8BIT((uint8_t)(x1 >> 8));
	WRITE_8BIT((uint8_t)x1);
	WRITE_8BIT((uint8_t)(x2 >> 8));
	WRITE_8BIT((uint8_t)x2);


	write_command_8bit(ILI_PASET);
	DC_DAT;
	WRITE_8BIT((uint8_t)(y1 >> 8));
	WRITE_8BIT((uint8_t)y1);
	WRITE_8BIT((uint8_t)(y2 >> 8));
	WRITE_8BIT((uint8_t)y2);

	write_command_8bit(ILI_RAMWR);
}




/*
 * Draw a character glyph in the given position with transparent or solid background.
 * draw_string_main() calls this function
 */
/*
void ili_draw_char(uint16_t x, uint16_t y, uint16_t fore_color, uint16_t back_color, const tImage *glyph, uint8_t is_bg)
{
	uint16_t width = 0, height = 0;
*  Last edited on: May 20, 2020
 *      Author: Avra
	width = glyph->width;
	height = glyph->height;

	uint16_t temp_x = x;
	uint16_t temp_y = y;

	ili_set_address_window(x, y, x + width-1, y + height-1);

	uint32_t mask = 0x80000000;

	int k = 0;
	while (k < height)
	{
		for (int j = 0; j < width; j++)
		{
			uint32_t big = ((uint32_t)glyph->data[j*3] << 24) | ((uint32_t)glyph->data[(j*3) + 1] << 16) | ((uint32_t)glyph->data[(j*3) + 2] << 8);

			//If pixel is blank
			if (big & mask)
			{
				temp_x++;

				//Has background color
				if (is_bg)
				{
					write_data_16bit(back_color);
				}
				//transarent background
				else
				{
					//skipping the current pixel and set the column address to next pixel
					ili_set_address_window(temp_x, temp_y, x + width-1, y + height-1);
				}

			}

			//if pixel is not blank
			else
			{
				temp_x++;
				//display the color in that pixel position
				write_data_16bit(fore_color);
			}

		}
		k++;
		mask = (mask >> 1);

		//New row starts. So, column is set to initial value and row is increased by one
		temp_x = x;
		temp_y++;

		//set the pixel position as per the column and row value
		ili_set_address_window(temp_x, temp_y, x + width-1, y + height-1);

	}
}
*/
void ili_draw_char(uint16_t x, uint16_t y, uint16_t fore_color, uint16_t back_color, const tImage *glyph, uint8_t is_bg)
{
	uint16_t width = 0, height = 0;

	width = glyph->width;
	height = glyph->height;

	uint16_t temp_x = x;
	uint16_t temp_y = y;

	uint8_t mask = 0x80;
	uint8_t bit_counter = 0;

	const uint8_t *glyph_data_ptr = (const uint8_t *)(glyph->data);
	uint8_t glyph_data = 0;

	// font bitmaps are stored in column major order (scanned from left-to-right, not the conventional top-to-bottom)
	// as font glyphs have heigher height than width, this scanning saves some storage.
	// So, we also render in left-to-right manner.

	// Along x axis (width)
	for (int i = 0; i < width; i++)
	{
		// Along y axis (height)
		for (int j = 0; j < height; j++)
		{

			// load new data only when previous byte (or word, depends on glyph->dataSize) is completely traversed by the mask
			// bit_counter = 0 means glyph_data is completely traversed by the mask
			if (bit_counter == 0)
			{
				glyph_data = *glyph_data_ptr++;
				bit_counter = glyph->dataSize;
			}
			// Decrement bit counter
			bit_counter--;

			//If pixel is blank
			if (glyph_data & mask)
			{
				//Has background color (not transparent bg)
				if (is_bg)
				{
					ili_draw_pixel(temp_x, temp_y, back_color);
				}
			}

			//if pixel is not blank
			else
			{
				ili_draw_pixel(temp_x, temp_y, fore_color);
			}

			glyph_data <<= 1;
			temp_y++;
		}

		//New col starts. So, row is set to initial value and col is increased by one
		temp_y = y;
		temp_x++;

		//Reset the bit counter cause we're moving to next column, so we start with a new byte
		bit_counter = 0;
	}
}



/*
 * draw a string in a given position
 * This function is called by ili_draw_string() and ili_draw_string_withbg()
 * Text is wrapped automatically if it hits the screen boundary.
 * x_padding and y_padding defines horizontal and vertical distance (in px) between two characters
 * is_bg=1 : Text will habe background color,   is_bg=0 : Text will have transparent background
 */

void ili_draw_string_main(uint16_t x, uint16_t y, char *str, uint16_t fore_color, uint16_t back_color, tFont *font, uint8_t is_bg)
{
	uint16_t x_temp = x;
	uint16_t y_temp = y;

	uint8_t x_padding = 0;
	uint8_t y_padding = 0;
	const tImage *img = {0};
	uint16_t width = 0, height = 0;



	while (*str)
	{
		if (*str == '\n')
		{
			x_temp = x;					//go to first col
			y_temp += (font->chars[0].image->height + y_padding);	//go to next row (row height = height of space)
		}

		else if (*str == '\t')
		{
			x_temp += 4 * (font->chars[0].image->height + y_padding);	//Skip 4 spaces (width = width of space)
		}
		else
		{
			for (uint8_t i = 0; i < font->length; i++)
			{
				if (font->chars[i].code == *str)
				{
					img = font->chars[i].image;
					break;
				}
			}
			width = img->width;
			height = img->height;

			if(y_temp + (height + y_padding) > ili_tftheight - 1)	//not enough space available at the bottom
				return;
			if (x_temp + (width + x_padding) > ili_tftwidth - 1)	//not enough space available at the right side
			{
				x_temp = x;					//go to first col
				y_temp += (height + y_padding);	//go to next row
			}


			if (is_bg)
				ili_draw_char(x_temp, y_temp, fore_color, back_color, img, 1);
			else
				ili_draw_char(x_temp, y_temp, fore_color, back_color, img, 0);
			x_temp += (width + x_padding);		//next char position
		}


		str++;
	}
}


void ili_draw_string(uint16_t x, uint16_t y, char *str, uint16_t color, tFont *font)
{
	ili_draw_string_main(x, y, str, color, 0, font, 0);
}

void ili_draw_string_withbg(uint16_t x, uint16_t y, char *str, uint16_t fore_color, uint16_t back_color, tFont *font)
{
	ili_draw_string_main(x, y, str, fore_color, back_color, font, 1);
}


/*
 * Draw a bitmap image on the screen
 */
void ili_draw_bitmap(uint16_t x, uint16_t y, const tImage16bit *bitmap)
{
	uint16_t width = 0, height = 0;
	width = bitmap->width;
	height = bitmap->height;

	uint16_t total_pixels = width * height;

	ili_set_address_window(x, y, x + width-1, y + height-1);

	DC_DAT;
	for (uint16_t pixels = 0; pixels < total_pixels; pixels++)
	{
		WRITE_8BIT((uint8_t)(bitmap->data[pixels] >> 8));
		WRITE_8BIT((uint8_t)bitmap->data[pixels]);
	}
}


/*
 * Fill an area with color. set_address_window() should be called before calling it
 * Here, macros are directly called (instead of inline functions) for performance increase
 */
void ili_fill_color(uint16_t color, uint32_t len)
{
	uint16_t blocks = (uint16_t)(len / 64); // 64 pixels/block
	uint8_t  pass_count;
	uint8_t color_high = color >> 8;
	uint8_t color_low = color;

	DC_DAT;
	// Write first pixel
	WRITE_8BIT(color_high); WRITE_8BIT(color_low);
	len--;

	// If higher byte abd lower byte are identical,
	// just strobe the WR pin to send the previous data
	if(color_high == color_low)
	{
		while(blocks--)
		{
			// pass count = number of blocks / pixels per pass = 64 / 4
			pass_count = 16;
			while(pass_count--)
			{
				WR_STROBE; WR_STROBE; WR_STROBE; WR_STROBE; // 2
				WR_STROBE; WR_STROBE; WR_STROBE; WR_STROBE; // 4
			}
		}
		// Fill any remaining pixels (1 to 64)
		pass_count = len & 63;
		while (pass_count--)
		{
			WR_STROBE; WR_STROBE;
		}
	}

	// If higher and lower bytes are different, send those bytes
	else
	{
		while(blocks--)
		{
			pass_count = 16;
			while(pass_count--)
			{
				WRITE_8BIT(color_high); WRITE_8BIT(color_low); 	WRITE_8BIT(color_high); WRITE_8BIT(color_low); //2
				WRITE_8BIT(color_high); WRITE_8BIT(color_low); 	WRITE_8BIT(color_high); WRITE_8BIT(color_low); //4
			}
		}
		pass_count = len & 63;
		while (pass_count--)
		{
			// write here the remaining data
			WRITE_8BIT(color_high); WRITE_8BIT(color_low);
		}
	}
}


/*
 * @brief	Fill a rectangle specified by initial co-ordinates and width and height
 * @param	x1: 16 bit integer to define initial position in x axis
 * @param	y1: 16 bit integer to define initial position in y axis
 * @param	w:  16 bit integer to define width
 * @param	h:  16 bit integer to define height
 * @param	color: 16 bit integer to define the color
 */


void ili_fill_rect(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t color)
{
	if (x1 >= ili_tftwidth || y1 >= ili_tftheight || w == 0 || h == 0)
		return;
	if (x1 + w - 1 >= ili_tftwidth)
		w = ili_tftwidth - x1;
	if (y1 + h - 1 >= ili_tftheight)
		h = ili_tftheight - y1;

	ili_set_address_window(x1, y1, x1 + w - 1, y1 + h - 1);
	ili_fill_color(color, (uint32_t)w * (uint32_t)h);
}


void ili_fill_rect_fast(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t color)
{
	ili_set_address_window(x1, y1, x1 + w - 1, y1 + h - 1);
	ili_fill_color(color, (uint32_t)w * (uint32_t)h);
}


/*
 * Fill the whole screen with a color
 */
void ili_fill_screen(uint16_t color)
{
	ili_set_address_window(0, 0, ili_tftwidth - 1, ili_tftheight - 1);
	ili_fill_color(color, (uint32_t)ili_tftwidth * (uint32_t)ili_tftheight);
}


/*
 * When dy < 0
 * It's called only by line_draw function. Not for user
 */
void plot_line_low(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color)
{
	int16_t dx = x1 - x0;
	int16_t dy = y1 - y0;
	int8_t yi = 1;
	uint8_t pixels_per_point = width * width;	//no of pixels making a point. if line width is 1, this var is 1. if 2, this var is 4 and so on
	uint8_t color_high = (uint8_t)(color >> 8);
	uint8_t color_low = (uint8_t)color;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}

	int16_t D = 2*dy - dx;
	uint16_t y = y0;
	uint16_t x = x0;

	while (x <= x1)
	{
		ili_set_address_window(x, y, x+width-1, y+width-1);
		//Drawing all the pixels of a single point

		DC_DAT;
		for (uint8_t pixel_cnt = 0; pixel_cnt < pixels_per_point; pixel_cnt++)
		{
			WRITE_8BIT(color_high);
			WRITE_8BIT(color_low);
		}
		if (D > 0)
		{
			y = y + yi;
			D = D - 2*dx;
		}
		D = D + 2*dy;
		x++;
	}
}


/*
 * When dx < 0
 * It's called only by line_draw function. Not for user
 */
void plot_line_high(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color)
{
	int16_t dx = x1 - x0;
	int16_t dy = y1 - y0;
	int8_t xi = 1;
	uint8_t pixels_per_point = width * width;	//no of pixels making a point. if line width is 1, this var is 1. if 2, this var is 4 and so on
	uint8_t color_high = (uint8_t)(color >> 8);
	uint8_t color_low = (uint8_t)color;

	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}

	int16_t D = 2*dx - dy;
	uint16_t y = y0;
	uint16_t x = x0;

	while (y <= y1)
	{
		ili_set_address_window(x, y, x+width-1, y+width-1);
		//Drawing all the pixels of a single point

		DC_DAT;
		for (uint8_t pixel_cnt = 0; pixel_cnt < pixels_per_point; pixel_cnt++)
		{
			WRITE_8BIT(color_high);
			WRITE_8BIT(color_low);
		}
		if (D > 0)
		{
			x = x + xi;
			D = D - 2*dy;
		}
		D = D + 2*dx;
		y++;
	}
}


/*
 * Brehensen's algorithm is used.
 * Draw line between ANY two points.
 * Not necessarily start points has to be less than end points.
 */
void ili_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color)
{
	if (x0 == x1)	//vertical line
	{
		ili_draw_fast_v_line(x0, y0, x1, y1, width, color);
	}
	else if (y0 == y1)		//horizontal line
	{
		ili_draw_fast_h_line(x0, y0, x1, y1, width, color);
	}

	else
	{
		if (abs(y1 - y0) < abs(x1 - x0))
		{
			if (x0 > x1)
				plot_line_low(x1, y1, x0, y0, width, color);
			else
				plot_line_low(x0, y0, x1, y1, width, color);
		}

		else
		{
			if (y0 > y1)
				plot_line_high(x1, y1, x0, y0, width, color);
			else
				plot_line_high(x0, y0, x1, y1, width, color) ;
		}
	}

}

/*
 * Draw a horizontal line very fast
 */
void ili_draw_fast_h_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color)
{
	ili_set_address_window(x0, y0, x1, y0+width-1);	//as it's horizontal line, y1=y0.. must be.

	ili_fill_color(color, (uint32_t)width * (uint32_t)abs(x1 - x0 + 1));
}

/*
 * Draw a vertical line very fast
 */
void ili_draw_fast_v_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color)
{
	ili_set_address_window(x0, y0, x0+width-1, y1);	//as it's vertical line, x1=x0.. must be.

	ili_fill_color(color, (uint32_t)width * (uint32_t)abs(y1 - y0 + 1));
}


/*
 * Draw a single pixel in a given point with a given color
 * Why?: This function is mainly added in the driver so that  ui libraries can use it.
 * example: LittlevGL requires user to supply a function that can draw pixel
 */
void ili_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
	ili_set_address_window(x, y, x, y);
	DC_DAT;
	WRITE_8BIT((uint8_t)(color >> 8));
	WRITE_8BIT((uint8_t)color);
}


/*
 * Rotate the display and also set the display width and height global variables
 * Parameters:
 * 	(uint8_t)rotation :	Rotation Type
 * 					0 : Default landscape
 * 					1 : Potrait 1
 * 					2 : Landscape 2
 * 					3 : Potrait 2
 */
void ili_rotate_display(uint8_t rotation)
{
	switch (rotation)
	{
		case 0:
			write_command_8bit(ILI_MADCTL);		//Memory Access Control
			write_data_8bit(0x40);				//MX: 1, MY: 0, MV: 0	(Landscape 1. Default)
			//CS_IDLE;
			ili_tftheight = 240;
			ili_tftwidth = 320;
			break;
		case 1:
			write_command_8bit(ILI_MADCTL);		//Memory Access Control
			write_data_8bit(0x20);				//MX: 0, MY: 0, MV: 1	(Potrait 1)
			//CS_IDLE;
			ili_tftheight = 320;
			ili_tftwidth = 240;
			break;
		case 2:
			write_command_8bit(ILI_MADCTL);		//Memory Access Control
			write_data_8bit(0x80);				//MX: 0, MY: 1, MV: 0	(Landscape 2)
			//CS_IDLE;
			ili_tftheight = 240;
			ili_tftwidth = 320;
			break;
		case 3:
			write_command_8bit(ILI_MADCTL);		//Memory Access Control
			write_data_8bit(0xE0);				//MX: 1, MY: 1, MV: 1	(Potrait 2)
			//CS_IDLE;
			ili_tftheight = 320;
			ili_tftwidth = 240;
			break;
	}
}

/*
 * Initialize the ili9341 driver
 */
void ili_init()
{
	CS_ACTIVE;

	RST_IDLE;
	HAL_Delay(5);
	RST_ACTIVE;
	HAL_Delay(20);
	RST_IDLE;
	HAL_Delay(150);

	write_command_8bit(0xEF);
	write_data_8bit(0x03);
	write_data_8bit(0x80);
	write_data_8bit(0x02);
	//CS_IDLE;

	write_command_8bit(0xCF);
	write_data_8bit(0x00);
	write_data_8bit(0XC1);
	write_data_8bit(0X30);
	//CS_IDLE;

	write_command_8bit(0xED);
	write_data_8bit(0x64);
	write_data_8bit(0x03);
	write_data_8bit(0X12);
	write_data_8bit(0X81);
	//CS_IDLE;

	write_command_8bit(0xE8);
	write_data_8bit(0x85);
	write_data_8bit(0x00);
	write_data_8bit(0x78);
	//CS_IDLE;

	write_command_8bit(0xCB);
	write_data_8bit(0x39);
	write_data_8bit(0x2C);
	write_data_8bit(0x00);
	write_data_8bit(0x34);
	write_data_8bit(0x02);
	//CS_IDLE;

	write_command_8bit(0xF7);
	write_data_8bit(0x20);
	//CS_IDLE;

	write_command_8bit(0xEA);
	write_data_8bit(0x00);
	write_data_8bit(0x00);
	//CS_IDLE;

	write_command_8bit(ILI_PWCTR1);    //Power control
	write_data_8bit(0x23);   //VRH[5:0]
	//CS_IDLE;

	write_command_8bit(ILI_PWCTR2);    //Power control
	write_data_8bit(0x10);   //SAP[2:0];BT[3:0]
	//CS_IDLE;

	write_command_8bit(ILI_VMCTR1);    //VCM control
	write_data_8bit(0x3e);
	write_data_8bit(0x28);
	//CS_IDLE;

	write_command_8bit(ILI_VMCTR2);    //VCM control2
	write_data_8bit(0x86);  //--
	//CS_IDLE;

	write_command_8bit(ILI_MADCTL);    // Memory Access Control
	write_data_8bit(0x40); // Rotation 0 (landscape mode)
	//CS_IDLE;

	write_command_8bit(ILI_PIXFMT);
	write_data_8bit(0x55);
	//CS_IDLE;

	write_command_8bit(ILI_FRMCTR1);
	write_data_8bit(0x00);
	write_data_8bit(0x13); // 0x18 79Hz, 0x1B default 70Hz, 0x13 100Hz
	//CS_IDLE;

	write_command_8bit(ILI_DFUNCTR);    // Display Function Control
	write_data_8bit(0x08);
	write_data_8bit(0x82);
	write_data_8bit(0x27);
	//CS_IDLE;

	write_command_8bit(0xF2);    // 3Gamma Function Disable
	write_data_8bit(0x00);
	//CS_IDLE;

	write_command_8bit(ILI_GAMMASET);    //Gamma curve selected
	write_data_8bit(0x01);
	//CS_IDLE;

	write_command_8bit(ILI_GMCTRP1);    //Set Gamma
	write_data_8bit(0x0F);
	write_data_8bit(0x31);
	write_data_8bit(0x2B);
	write_data_8bit(0x0C);
	write_data_8bit(0x0E);
	write_data_8bit(0x08);
	write_data_8bit(0x4E);
	write_data_8bit(0xF1);
	write_data_8bit(0x37);
	write_data_8bit(0x07);
	write_data_8bit(0x10);
	write_data_8bit(0x03);
	write_data_8bit(0x0E);
	write_data_8bit(0x09);
	write_data_8bit(0x00);
	//CS_IDLE;

	write_command_8bit(ILI_GMCTRN1);    //Set Gamma
	write_data_8bit(0x00);
	write_data_8bit(0x0E);
	write_data_8bit(0x14);
	write_data_8bit(0x03);
	write_data_8bit(0x11);
	write_data_8bit(0x07);
	write_data_8bit(0x31);
	write_data_8bit(0xC1);
	write_data_8bit(0x48);
	write_data_8bit(0x08);
	write_data_8bit(0x0F);
	write_data_8bit(0x0C);
	write_data_8bit(0x31);
	write_data_8bit(0x36);
	write_data_8bit(0x0F);
	//CS_IDLE;

	write_command_8bit(ILI_SLPOUT);    //Exit Sleep
	//CS_IDLE;
	HAL_Delay(150);

	write_command_8bit(ILI_DISPON);    //Display on
	//CS_IDLE;
	HAL_Delay(150);
}
