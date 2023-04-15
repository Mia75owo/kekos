#include "./kernel.h"

void __stack_chk_fail(void) {}

void clear_screen() {
    for (int i = 0; i <= MAX_ROWS * MAX_COLS; i++) {
        unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
        vidmem[i * 2] = ' ';
        vidmem[i * 2 + 1] = WHITE_ON_BLACK;
    }
    set_cursor(0);
}

color getColor(int fore, int back) {
  return (color)((back << 4) + fore);
}

color s() {
    return (color)((black << 4) + white);
}

void print_str(char *text, color c) {
    int offset = get_cursor();
    int i = 0;
    while (text[i] != 0) {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scroll_ln(offset);
        }
        if (text[i] == '\n' || get_line_offset() >= MAX_COLS - 1) {
            ++i;
            ++offset;
            next_line();
            offset = get_cursor();
            continue;
        }
        unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
        vidmem[offset * 2] = text[i];
        vidmem[offset * 2 + 1] = c;
        ++i;
        ++offset;
    }
    set_cursor(offset);
}

void next_line() {
    set_cursor((get_line() + 1) * 80);
}

int get_line() {
    int c = get_cursor();
    int l = 0;
    while (c >= 80) {
        c -= 80;
        ++l;
    }
    return l;
}

int get_line_offset() {
    int c = get_cursor();
    while (c >= 80) {
        c -= 80;
    }
    return c;
}

void memory_copy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int scroll_ln(int offset) {
    memory_copy(
            (char *) (get_offset(0, 1) + VIDEO_ADDRESS),
            (char *) (get_offset(0, 0) + VIDEO_ADDRESS),
            MAX_COLS * (MAX_ROWS - 1) * 2
    );

    for (int col = 0; col < MAX_COLS; col++) {

        unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
        vidmem[get_offset(col, MAX_ROWS - 1)] = ' ';
    }

    return offset - 2 * MAX_COLS;
}

unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

void set_cursor(int offset) {
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    port_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset >> 8));
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    port_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}

int get_cursor() {
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    int offset = port_byte_in(VGA_DATA_REGISTER) << 8;
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    offset += port_byte_in(VGA_DATA_REGISTER);
    return offset;
}




int main() {
    clear_screen();
    char text[] = "Test1\n";
    char text2[] = "Test2\n";
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text, s());
    print_str(text2, s());
    return 0;
}
