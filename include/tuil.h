#ifndef TUIL_H
#define TUIL_H

#include <stdio.h>

// Text Attributes
#define TUIL_ATTR_RESET      0
#define TUIL_ATTR_BOLD       1
#define TUIL_ATTR_UNDERLINE  4
#define TUIL_ATTR_REVERSE    7

// Foreground Colors
#define TUIL_FG_BLACK        30
#define TUIL_FG_RED          31
#define TUIL_FG_GREEN        32
#define TUIL_FG_YELLOW       33
#define TUIL_FG_BLUE         34
#define TUIL_FG_MAGENTA      35
#define TUIL_FG_CYAN         36
#define TUIL_FG_WHITE        37

// Background Colors
#define TUIL_BG_BLACK        40
#define TUIL_BG_RED          41
#define TUIL_BG_GREEN        42
#define TUIL_BG_YELLOW       43
#define TUIL_BG_BLUE         44
#define TUIL_BG_MAGENTA      45
#define TUIL_BG_CYAN         46
#define TUIL_BG_WHITE        47

/**
 * Print styled text to stdout.
 * Pass -1 to any attribute to ignore it.
 */
void tuil_print_styled(const char *text, int fg_color, int bg_color, int attribute);

#include "tuil_fonts.h"

/**
 * Print simple ASCII art for a given text using a specified font.
 */
void tuil_print_ascii(const char *text, int fg_color, const tuil_font_t *font);

/**
 * Utility to clear the screen
 */
void tuil_clear_screen(void);

// ======== OPTIONAL SHORTHAND DEFINITIONS ========
#ifndef TUIL_NO_SHORTHAND

// Attribute Shorthands
#define ATTR_RESET     TUIL_ATTR_RESET
#define ATTR_BOLD      TUIL_ATTR_BOLD
#define ATTR_UNDERLINE TUIL_ATTR_UNDERLINE
#define ATTR_REVERSE   TUIL_ATTR_REVERSE

// Foreground Shorthands
#define FG_BLACK       TUIL_FG_BLACK
#define FG_RED         TUIL_FG_RED
#define FG_GREEN       TUIL_FG_GREEN
#define FG_YELLOW      TUIL_FG_YELLOW
#define FG_BLUE        TUIL_FG_BLUE
#define FG_MAGENTA     TUIL_FG_MAGENTA
#define FG_CYAN        TUIL_FG_CYAN
#define FG_WHITE       TUIL_FG_WHITE

// Background Shorthands
#define BG_BLACK       TUIL_BG_BLACK
#define BG_RED         TUIL_BG_RED
#define BG_GREEN       TUIL_BG_GREEN
#define BG_YELLOW      TUIL_BG_YELLOW
#define BG_BLUE        TUIL_BG_BLUE
#define BG_MAGENTA     TUIL_BG_MAGENTA
#define BG_CYAN        TUIL_BG_CYAN
#define BG_WHITE       TUIL_BG_WHITE

#endif // TUIL_NO_SHORTHAND

#endif // TUIL_H
