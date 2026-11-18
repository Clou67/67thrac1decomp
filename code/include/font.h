#ifndef FONT_H
#define FONT_H

struct FontWindow {
    short win_top;
    short win_bot;
    short win_left;
    short win_right;
    short text_x;
    short text_y;
    short max_width;
    short max_height;
    short line_spacing;
    short flags;
    short sub_pixel_x;
    short sub_pixel_y;
    short drop_shadow_offset_x;
    short drop_shadow_offset_y;
};

// Selects font and returns its TEX0 register value (RC1 layout; DL returns void).
unsigned long FontSet(int fontName);
int FontLen(char *text, int length);
void FontPrintMediumLeft(int x, int y, unsigned long rgba, char *text, int length);
void SetFontWindow(FontWindow *window, int win_top, int win_bot, int win_left, int win_right, int text_x, int text_y, int line_spacing, int flags);
void FontPrintWindowSmall(FontWindow *window, unsigned long rgba, char *text, int length);

#endif
