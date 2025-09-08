#ifndef FONT_MANAGER_HPP
#define FONT_MANAGER_HPP

#include <SDL/SDL.h>

namespace FontManager {
    typedef struct font Font;

    Font* loadFont(Uint16* font_data, int char_width, int char_height, int r, int g, int b);
    void drawText(SDL_Surface* screen, Font* font, int x, int y, const char* format, ...);
    void drawTextCentered(SDL_Surface* screen, Font* font, int x, int y, const char* format, ...);
    int measureText(Font* font, const char* format, ...);
    void unloadFont(Font* font);
}

#endif