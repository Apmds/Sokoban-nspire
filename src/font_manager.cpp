#include "font_manager.hpp"
#include <os.h>
#include <stdarg.h>
#include <stdexcept>

#define FONT_NUMCHARS 128

struct FontManager::font {
    SDL_Surface* data;
    int char_w;
    int char_h;
    int spacing;
};

FontManager::Font* FontManager::loadFont(Uint16* font_data, int char_width, int char_height, int tint_r, int tint_g, int tint_b) {
    // Load font
    SDL_Surface* font_tex = nSDL_LoadImage(font_data);
    if (font_tex == NULL) {
        exit(EXIT_FAILURE);
    }
    SDL_SetColorKey(font_tex, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(font_tex->format, 0, 0, 0));

    FontManager::Font* font = (FontManager::Font*) malloc(sizeof(*font));
    if (font == NULL) {
        exit(EXIT_FAILURE);
    }
    font->data = font_tex;
    font->char_w = char_width;
    font->char_h = char_height;
    font->spacing = 1;

    // Validate character sizes
    if (font->data->h < char_height) {
        free(font);
        throw std::invalid_argument("Font height is less than minimum needed image height.");
    }
    if (font->data->w < char_width*FONT_NUMCHARS) {
        free(font);
        throw std::invalid_argument("Font width is less than minimum needed image width.");
    }

    // Tint the chars
    if (SDL_MUSTLOCK(font_tex)) {
        SDL_LockSurface(font_tex);
    }

    Uint8 r, g, b;
    Uint8 bpp = font_tex->format->BytesPerPixel;
    int w = font_tex->w;
    int h = font_tex->h;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            // Get pixel color with position
            Uint8* p = (Uint8 *)font_tex->pixels + y * font_tex->pitch + x * bpp;

            // Read the pixel value depending on bytes per pixel
            Uint32 pixel_color;
            switch (bpp) {
                case 1:
                    pixel_color = *p;
                    break;
                case 2:
                    pixel_color = *(Uint16*)p;
                    break;
                case 3:
                    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                        pixel_color = (p[0] << 16) | (p[1] << 8) | p[2];
                    else
                        pixel_color = p[0] | (p[1] << 8) | (p[2] << 16);
                    break;
                default:
                    pixel_color = *(Uint32*)p;
                    break;
                
            }

            SDL_GetRGB(pixel_color, font_tex->format, &r, &g, &b);

            // Tinting
            r = (r * tint_r) / 255;
            g = (g * tint_g) / 255;
            b = (b * tint_b) / 255;

            // Write color depending on format
            Uint32 color = SDL_MapRGB(font_tex->format, r, g, b);
            switch(bpp) {
                case 1:
                    *p = color;
                    break;
                case 2:
                    *(Uint16 *)p = color;
                    break;
                case 3:
                    // Setting the color byte by byte depending on endianess
                    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                        p[0] = (color >> 16) & 0xFF;
                        p[1] = (color >> 8) & 0xFF;
                        p[2] = color & 0xFF;
                    } else {
                        p[0] = color & 0xFF;
                        p[1] = (color >> 8) & 0xFF;
                        p[2] = (color >> 16) & 0xFF;
                    }
                    break;
                case 4:
                    *(Uint32 *)p = color;
                    break;
            }
        }
    }
    
    if (SDL_MUSTLOCK(font_tex)) {
        SDL_UnlockSurface(font_tex);
    }

    return font;
}

static void drawChar(SDL_Surface* screen, FontManager::Font* font, char c, int x, int y) {
    SDL_Surface* tex = font->data;
    
    SDL_Rect src;
	src.x = c*font->char_w;
	src.y = 0;
	src.w = font->char_w;
	src.h = font->char_h;

	SDL_Rect pos;
	pos.x = x;
	pos.y = y;

	SDL_BlitSurface(tex, &src, screen, &pos);
}


void FontManager::drawText(SDL_Surface* screen, FontManager::Font* font, int x, int y, const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    // Get required buffer size
    va_list args_copy;
    va_copy(args_copy, args);
    int needed = vsnprintf(NULL, 0, format, args_copy);
    va_end(args_copy);

    // Get formatted string
    char* buffer = (char*) malloc(needed + 1);
    if (buffer == NULL) {
        exit(EXIT_FAILURE);
    }

    vsnprintf(buffer, needed + 1, format, args);

    va_end(args);

    // Draw the formatted buffer to the screen
    int i = 0;
    while (buffer[i] != '\0') {
        drawChar(screen, font, buffer[i], x + (i*(font->char_w+1)), y);

        i++;
    }

    free(buffer);
}

void FontManager::drawTextCentered(SDL_Surface* screen, FontManager::Font* font, int x, int y, const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    // Get required buffer size
    va_list args_copy;
    va_copy(args_copy, args);
    int needed = vsnprintf(NULL, 0, format, args_copy);
    va_end(args_copy);

    // Get formatted string
    char* buffer = (char*) malloc(needed + 1);
    if (buffer == NULL) {
        exit(EXIT_FAILURE);
    }

    vsnprintf(buffer, needed + 1, format, args);

    va_end(args);

    // Draw the formatted buffer to the screen
    int i = 0;
    while (buffer[i] != '\0') {
        drawChar(screen, font, buffer[i], x + (i*(font->char_w+font->spacing)) - (((font->char_w)*needed) + (font->spacing*(needed-1)))/2, y - (font->char_h/2));

        i++;
    }

    free(buffer);
}

int FontManager::measureText(FontManager::Font* font, const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    // Get required buffer size
    int needed = vsnprintf(NULL, 0, format, args);

    va_end(args);

    return (font->char_w * needed) + (font->spacing * (needed - 1));
}

void FontManager::unloadFont(FontManager::Font* font) {
    SDL_FreeSurface(font->data);
    free(font);
}
