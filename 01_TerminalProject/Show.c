#include <ncurses.h>
#include <locale.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DX 2
#define _GNU_SOURCE

void print_str(WINDOW *win, char **head, size_t pos,
                int lines, int width, int left_offset) {
    wmove(win, 0, 0);
    for (size_t i = 0; i < lines; ++i) {
        if (head[pos + i] == NULL || strlen(head[pos + i]) < left_offset) {
            mvwprintw(win, i + DX, DX, "\n");
        }
        else {
            mvwprintw(win, i + DX, DX, "%.*s", width, head[pos + i] + left_offset);
        }
    }
    box(win, 0, 0);
    wmove(win, 0, 0);
    wrefresh(win);
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        printf("No files to read\n");
        exit(0);        
    }
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error with opening the file %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }
    setlocale(LC_ALL, "");
    WINDOW *win;
    initscr();
    noecho();
    printw("FILE: %s", argv[1]);
    refresh();
    win = newwin(LINES - 2 * DX, COLS - 2 * DX, DX, DX);
    keypad(win, TRUE);
    scrollok(win, TRUE);
    errno = 0;
    unsigned width = COLS - 2 * DX;
    unsigned height = LINES - 2 * DX;
    unsigned size = height;
    unsigned long long file_size = fseek(file, 0, SEEK_END);
    unsigned long long cur_pos = fseek(file, 0, SEEK_SET);
    
    char **head = calloc(size, sizeof (*head));
    if (head == NULL) {
            endwin();
            fprintf(stderr, "Error with memory allocation\n");
            exit(1);
    }

    size_t cur_line = 0, left_offset = 0;
    size_t a = 0, n_lines = 0;
    while (getline(head + cur_line, &a, file) != -1) {
        if (++cur_line >= size) {
            size *= 2;
            head = realloc(head, size * sizeof (*head));
        }
        ++n_lines;
    }
    
    fclose(file);

    if (errno) {
        endwin();
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }
    
    int c;
    cur_line = 0;
    print_str(win, head, cur_line, height, width, left_offset);

    while((c = wgetch(win)) != 27) {
        switch(c) {
        case KEY_DOWN:
        case ' ':
            if (cur_line <= n_lines - height + 1) {
                ++cur_line;
                werase(win);
                print_str(win, head, cur_line, height, width, left_offset);
            }
            break;

        case KEY_UP:
            if (cur_line) {
                --cur_line;
                werase(win);
                print_str(win, head, cur_line, height, width, left_offset);
            }
            break;

        case KEY_RIGHT:
            ++left_offset;
            werase(win);
            print_str(win, head, cur_line, height, width, left_offset);
            break;

        case KEY_LEFT:
            if (left_offset) {
                --left_offset;
                werase(win);
                print_str(win, head, cur_line, height, width, left_offset);
            }
            break;

        case KEY_NPAGE:
            if (height + cur_line <= n_lines - height) {
                cur_line += height;
            }
            else {
                cur_line = n_lines - height + 2;
            }
            werase(win);
            print_str(win, head, cur_line, height, width, left_offset);
            break;

        case KEY_PPAGE:
            if (cur_line > height) {
                cur_line -= height;
            }
            else {
                cur_line = 0;
            }
            werase(win);
            print_str(win, head, cur_line, height, width, left_offset);
            break;
        }
    }
                
    endwin();
    for (size_t i = 0; i < n_lines; ++i) {
        free(head[i]);
    }
    free(head);
}
