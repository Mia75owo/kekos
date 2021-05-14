#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f


#define black         0
#define blue          1
#define green         2
#define cyna          3
#define red           4
#define magenta       5
#define brown         6
#define lightgray     7
#define darkgray      8
#define lightblue     9
#define lightgreen   10
#define lightcyan    11
#define lightred     12
#define lightmagenta 13
#define yellow       14
#define white        15

typedef unsigned char color;
color getColour(int fore, int back);
color s();

void clear_screen();
void port_byte_out(unsigned short port, unsigned char data);
void set_cursor(int offset);
void next_line();
void printstr(char *text, color c);
unsigned char port_byte_in(unsigned short port);
int get_cursor();
int get_line();
int get_line_offset();
int get_line();
void memory_copy(char *source, char *dest, int nbytes);
int scroll_ln(int offset);
int get_offset(int col, int row);