# TUIL (Terminal UI Library)

TUIL is a dedicated C library for generating beautiful ASCII art and styled text directly in the terminal. It's built for zero-setup execution, featuring highly optimized, natively compiled fonts (like "Doom"), and scales beautifully with your C applications.

---

## Integration Guide

There are two primary ways to integrate TUIL into your own C projects: as a **Local Subdirectory** or as a **System-Wide Library**.

### Method 1: Local Subdirectory (Recommended)

If you want to bundle TUIL directly inside your project so other developers don't have to install anything globally, you can clone it as a folder:

1. Clone TUIL inside your project's folder:

   ```bash
   git clone https://github.com/alpha/tuil.git tuil
   ```
2. Build the TUIL library:

   ```bash
   cd tuil
   make
   cd ..
   ```
3. Create your `app.c` file:

   ```c
   #include "tuil/include/tuil.h"

   int main() {
       tuil_clear_screen();
       // Using the beautiful Doom font!
       tuil_print_ascii("Hello World", TUIL_FG_CYAN, FONT_DOOM);
       return 0;
   }
   ```
4. Configure your `Makefile`:
   To avoid typing long compiler paths every time, you can create a `Makefile`.

   **Option A: New Project** (Create a file named `Makefile`):

   ```makefile
   CC = gcc
   CFLAGS = -Wall -Ituil/include
   LDFLAGS = -Ltuil -ltuil

   app: app.c
   	$(CC) $(CFLAGS) app.c $(LDFLAGS) -o app
   ```

   **Option B: Existing Project** (Add these flags to your current `Makefile`):
   Simply append the `TUIL` include and library paths to your existing variables:

   ```makefile
   # Add to your CFLAGS
   CFLAGS += -Ituil/include

   # Add to your LDFLAGS
   LDFLAGS += -Ltuil -ltuil
   ```
5. Compile and Run!
   Now, anytime you update your code, you just type:

   ```bash
   make
   ./app
   ```

### Method 2: System-Wide Installation

If you build many C apps and just want TUIL available natively across your entire OS (like `<stdio.h>`):

1. Clone and install globally:

   ```bash
   git clone https://github.com/alpha/tuil.git
   cd tuil
   sudo make install
   ```
2. Now you can include it natively in **any** project on your computer:

   ```c
   #include <tuil.h>
   ```
3. Compile using the standard `-ltuil` flag:

   ```bash
   gcc app.c -ltuil -o app
   ```

---

## Fonts Architecture

TUIL features an automated Python build tool (`tools/font_converter.py`) that converts raw `.txt` ASCII art geometries into highly efficient C structs mapping the full 128-character ASCII alphabet (uppercase and lowercase). These structs are "baked" into the `libtuil.a` archive itself!

### Included Multi-Case Fonts

- `&tuil_font_doom` *(High-resolution native height Doom)*

## API Reference

### 1. `tuil_print_ascii`

Prints high-resolution ASCII art using a specified font.

**Signature:**

```c
void tuil_print_ascii(const char *text, int fg_color, const tuil_font_t *font);
```

**Usage:**

```c
// Using DOOM font in Cyan
tuil_print_ascii("Hello World", FG_CYAN, FONT_DOOM);

// Using -1 for default color
tuil_print_ascii("TUIL", -1, FONT_DOOM);
```
<img width="671" height="328" alt="Screenshot 2026-03-24 at 7 37 11 PM" src="https://github.com/user-attachments/assets/9391738f-4856-4477-9799-68246a8a3b72" />

---

### 2. `tuil_print_styled`

Prints standard text with ANSI styles (colors and attributes).

**Signature:**

```c
void tuil_print_styled(const char *text, int fg_color, int bg_color, int attribute);
```

**Usage:**

```c
// Bold White text on Red background
tuil_print_styled("ERROR: System Failure\n", FG_WHITE, BG_RED, ATTR_BOLD);

// Simple Green text (no background or attributes)
tuil_print_styled("Success!\n", FG_GREEN, -1, -1);
```

---

### 3. `tuil_clear_screen`

Utility function to clear the terminal screen.

**Signature:**

```c
void tuil_clear_screen(void);
```

**Usage:**

```c
tuil_clear_screen();
```

---

## Constants & Macros

### Colors

TUIL supports standard ANSI colors via shorthands (e.g., `FG_RED`, `BG_BLUE`):

- `FG_BLACK`, `FG_RED`, `FG_GREEN`, `FG_YELLOW`, `FG_BLUE`, `FG_MAGENTA`, `FG_CYAN`, `FG_WHITE`
- `BG_BLACK`, `BG_RED`, `BG_GREEN`, `BG_YELLOW`, `BG_BLUE`, `BG_MAGENTA`, `BG_CYAN`, `BG_WHITE`

### Attributes

- `ATTR_RESET`, `ATTR_BOLD`, `ATTR_UNDERLINE`, `ATTR_REVERSE`

### Fonts

- `FONT_DOOM`: High-resolution "Doom" style font.
