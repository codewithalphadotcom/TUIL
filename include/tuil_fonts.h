#ifndef TUIL_FONTS_H
#define TUIL_FONTS_H

typedef struct {
    const char *name;
    int height;
    const char **chars[128]; // Supports standard ASCII (A-Z, a-z, etc)
} tuil_font_t;

extern const tuil_font_t tuil_font_doom;
#define FONT_DOOM &tuil_font_doom

#endif // TUIL_FONTS_H
