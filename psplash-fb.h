/* 
 *  pslash - a lightweight framebuffer splashscreen for embedded devices. 
 *
 *  Copyright (c) 2006 Matthew Allum <mallum@o-hand.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */

#ifndef _HAVE_PSPLASH_FB_H
#define _HAVE_PSPLASH_FB_H

enum RGBMode {
    RGB565,
    BGR565,
    RGB888,
    BGR888,
    GENERIC,
};

#define OFFSET(fb,x,y) (((y) * (fb)->stride) + ((x) * ((fb)->bpp >> 3)))

typedef struct PSplashFB
{
  int            fd;			
  struct termios save_termios;	        
  int            type;		        
  int            visual;		
  int            width, height;
  int            bpp;
  int            stride;
  char		*data;
  char		*base;

  int            angle;
  int            real_width, real_height;

  enum RGBMode   rgbmode;
  int            red_offset;
  int            red_length;
  int            green_offset;
  int            green_length;
  int            blue_offset;
  int            blue_length;
  int            alloc;
}
PSplashFB;

void
psplash_fb_destroy (PSplashFB *fb);

PSplashFB*
psplash_fb_new (int angle);

void
psplash_fb_flush (PSplashFB *fb);

void
psplash_fb_plot_pixel (PSplashFB    *fb, 
		       int          x, 
		       int          y, 
		       uint8        red,
		       uint8        green,
		       uint8        blue);

void
psplash_fb_draw_rect (PSplashFB    *fb, 
		      int          x, 
		      int          y, 
		      int          width, 
		      int          height,
		      uint8        red,
		      uint8        green,
		      uint8        blue);

void
psplash_fb_draw_image (PSplashFB    *fb, 
		       int          x, 
		       int          y, 
		       int          img_width, 
		       int          img_height,
		       int          img_bytes_pre_pixel,
		       uint8       *rle_data);

void
psplash_fb_text_size (PSplashFB          *fb,
		      int                *width, 
		      int                *height,
		      const PSplashFont  *font,
		      const char         *text);

void
psplash_fb_draw_text (PSplashFB         *fb, 
		      int                x, 
		      int                y, 
		      uint8              red,
		      uint8              green,
		      uint8              blue,
		      const PSplashFont *font,
		      const char        *text);

inline uint16_t RGB888_TO_RGB565_INT(int r, int g, int b)
{ 
	return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}
inline uint32_t RGB888_TO_INT(int r, int g, int b)
{
	return (r << 16) | (g << 8) | b;
}

#endif
