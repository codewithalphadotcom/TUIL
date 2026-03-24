#include "../include/tuil.h"
#include "../include/tuil_fonts.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void tuil_print_ascii(const char *text, int fg_color, const tuil_font_t *font) {
    if (!font || !text) return;
    int len = strlen(text);
    
    // Set color
    if (fg_color != -1) {
        printf("\033[%dm", fg_color);
    }
    
    // Print dynamic lines according to font height
    for (int line = 0; line < font->height; line++) {
        for (int i = 0; i < len; i++) {
            unsigned char c = text[i];
            if (c == ' ') {
                for(int s=0; s<5; s++) printf(" ");
            } else if (c < 128 && font->chars[c]) {
                const char **font_char = font->chars[c];
                if (font_char && font_char[line]) {
                    printf("%s", font_char[line]);
                } else {
                    printf("?");
                }
            } else {
                printf("?");
            }
        }
        printf("\n");
    }
    
    // Reset color
    printf("\033[0m");
}
