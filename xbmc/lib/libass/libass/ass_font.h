/*
 * Copyright (C) 2006 Evgeniy Stepanov <eugeni.stepanov@gmail.com>
 *
 * This file is part of libass.
 *
 * libass is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libass is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with libass; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef LIBASS_FONT_H
#define LIBASS_FONT_H

#include <stdint.h>
#include <ft2build.h>
#include FT_GLYPH_H
#include "ass.h"
#include "ass_types.h"

#define ASS_FONT_MAX_FACES 10
#define DECO_UNDERLINE 1
#define DECO_STRIKETHROUGH 2

typedef struct {
	char* family;
	unsigned bold;
	unsigned italic;
    int treat_family_as_pattern;
} ass_font_desc_t;

typedef struct {
	ass_font_desc_t desc;
	ass_library_t* library;
	FT_Library ftlibrary;
	FT_Face faces[ASS_FONT_MAX_FACES];
	int n_faces;
	double scale_x, scale_y; // current transform
	FT_Vector v; // current shift
	double size;
} ass_font_t;

// FIXME: passing the hashmap via a void pointer is very ugly.
ass_font_t *ass_font_new(void *font_cache, ass_library_t *library,
                         FT_Library ftlibrary, void *fc_priv,
                         ass_font_desc_t *desc);
void ass_font_set_transform(ass_font_t *font, double scale_x,
                            double scale_y, FT_Vector *v);
void ass_font_set_size(ass_font_t* font, double size);
void ass_font_get_asc_desc(ass_font_t *font, uint32_t ch, int *asc,
                           int *desc);
FT_Glyph ass_font_get_glyph(void *fontconfig_priv, ass_font_t *font,
                            uint32_t ch, ass_hinting_t hinting, int flags);
FT_Vector ass_font_get_kerning(ass_font_t* font, uint32_t c1, uint32_t c2);
void ass_font_free(ass_font_t* font);

#endif /* LIBASS_FONT_H */