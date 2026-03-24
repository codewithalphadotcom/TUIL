#include "tuil.h"
#include <stdio.h>

int main() {
  // Clear screen
  tuil_clear_screen();

  // Print Styled Text
  tuil_print_styled("Warning: Critical Error\n", FG_WHITE, BG_RED, ATTR_BOLD);

  // Print ASCII Art
  tuil_print_ascii("Hello World", FG_MAGENTA, FONT_DOOM);

  return 0;
}