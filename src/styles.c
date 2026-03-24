#include "../include/tuil.h"
#include <stdio.h>

void tuil_print_styled(const char *text, int fg_color, int bg_color, int attribute) {
    printf("\033[");
    
    int started = 0;
    
    if (attribute != -1) {
        printf("%d", attribute);
        started = 1;
    }
    
    if (fg_color != -1) {
        if (started) printf(";");
        printf("%d", fg_color);
        started = 1;
    }
    
    if (bg_color != -1) {
        if (started) printf(";");
        printf("%d", bg_color);
        started = 1;
    }
    
    // Default to reset if nothing passed, else finish the code
    if (!started) {
        printf("0");
    }
    
    printf("m%s\033[0m", text);
}

void tuil_clear_screen(void) {
    printf("\033[2J\033[H");
}
