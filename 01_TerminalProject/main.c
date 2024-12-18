#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>

#define DX 7
#define DY 3

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int main(int argc, char** argv) {
    char* filename = argv[1];

    FILE* file = fopen(filename, "r");
    int lines_count = 0;
    while (!feof(file)) {
        char c = fgetc(file);
        if (c == '\n') {
            ++lines_count;
        }
    }

    fseek(file, 0, SEEK_SET);

    char** lines = malloc(lines_count * sizeof(char*));
    size_t len = 0;
    for (int i = 0; i < lines_count; ++i) {
        getline(lines + i, &len, file);
    }

    WINDOW *win, *frame;
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    printw(filename);
    refresh();

    int height = LINES - 2 * DY - 2;
    int max_line = MAX(0, lines_count - height);

    win = newwin(height, COLS - 2 * DX - 2, DY + 1, DX + 1);
    frame = newwin(height + 2, COLS - 2 * DX, DY, DX);
    box(frame, 0, 0);
    wrefresh(frame);
    keypad(win, TRUE);

    int start = 0;
    int end = MIN(start + height, lines_count);
    wclear(win);
    for (int i = start; i < end; ++i) {
        wprintw(win, "%5d: %s", i, lines[i]);
    }
    wmove(win, 0, 0);
    wrefresh(win);

    int ch;
    while ((ch = wgetch(win)) != 27) {
        if (ch == ' ' && start != max_line) {
            start = MIN(start + 1, max_line);
            end = MIN(start + height, lines_count);
            wclear(win);
            for (int i = start; i < end; ++i) {
                wprintw(win, "%5d: %s", i, lines[i]);
            }
            wmove(win, 0, 0);
            wrefresh(win);
        }
    }

    delwin(win);
    delwin(frame);

    endwin();

    return 0;
}

