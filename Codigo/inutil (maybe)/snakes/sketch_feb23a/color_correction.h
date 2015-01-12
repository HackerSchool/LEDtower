#ifndef color_correction
#define color_correction

#define ANSI_COLOR_RED     "\x1b[31m".
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define true 1
#define false 0

#define verticalmax 16

typedef struct body
{
    int column, row;
    struct body *previous;
}body;

int mymain();

void snake(int horizontallimit, int verticallimit, int sizelimit, int grouthrate, int speed, int speedup_rate);
body* add(body* head, int column, int row);
body* delete(body* head);
void endgame(int matriz[][verticalmax][3], int background_color[3]);

#endif
