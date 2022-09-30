#include <ncurses.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

enum Consts
{
    DEF_STRING_COUNT = 100,
    MAX_STRING_LEN = 300
};

WINDOW *create_window(int width, int height)
{
    int startx = 0;
    int starty = 3;
    return newwin(height, width, starty, startx);
}

void free_strings(char**, int);

char **read_strings(FILE *file, int *str_count)
{
    char **strings = malloc(DEF_STRING_COUNT * sizeof(char *));
    if (!strings)
    {
        return NULL;
    }

    int current_str_count = DEF_STRING_COUNT;
    int iterator = 0;
    char *str;

    while (!feof(file))
    {
        str = malloc(MAX_STRING_LEN);

        if (!str)
        {
            free_strings(strings, iterator);
            return NULL;
        }

        if (iterator == current_str_count)
        {
            char **tmp = realloc(strings, current_str_count * 2 * sizeof(char *));
            if (!tmp)
            {
                free_strings(strings, iterator);
                return NULL;
            }

            strings = tmp;
            current_str_count *= 2;
        }

        str = fgets(str, MAX_STRING_LEN, file);
        strings[iterator] = str;
        ++iterator;
    }

    *str_count = iterator - 1;
    return strings;
}

void free_strings(char **strings, int len)
{
    for (int i = 0; i < len; ++i)
    {
        if (!strings[i])
        {
            continue;
        }

        free(strings[i]);
    }
    free(strings);
}

void print_strings(WINDOW *win, char **strings, int len, int start, int finish)
{
    if (len < finish)
    {
        finish = len;
    }

    for (int i = start; i < finish; ++i)
    {
        wmove(win, i % (LINES - 5), 2);
        wprintw(win, "%s", strings[i]);
    }
    box(win, 0, 0);
    wrefresh(win);
}

int main(int argc, char **argv)
{
    initscr();
    cbreak();
    noecho();
    halfdelay(1);
    if (argc <= 1)
    {
        printw("There is no file name.\nPress any button to exit.");
        getch();
        endwin();
        return -1;
    }

    FILE* file = fopen(argv[1], "r");

    if (!file)
    {
        printw("Can not open the file %s\nPress any button to exit.", argv[1]);
        getch();
        endwin();
        return -1;
    }

    int str_count = 0;
    char **strings = read_strings(file, &str_count);
    if (!strings)
    {
        printw("Cant read file.");
        getch();
        fclose(file);
        endwin();
        return -1;
    }

    int width = COLS;
    int height = LINES - 3;
    WINDOW *win = create_window(width, height);
    keypad(win, 1);
    refresh();
    printw("%s\n", argv[1]);
    refresh();
    box(win, 0, 0);
    print_strings(win, strings, str_count, 0, height - 2);

    int page = 1;
    while (1)
    {
        int c = wgetch(win);
        if (c == 27)
        {
            break;
        }
        else if (c == 32)
        {
            if (page * (height - 2) < str_count)
            {
                wclear(win);
                print_strings(win, strings, str_count, page * (height - 2), (page + 1) * (height - 2));
                ++page;
            }
        }
        else if (c == 'u')
        {
            if (page > 1)
            {
                wclear(win);
                print_strings(win, strings, str_count, (page - 2) * (height - 2), (page - 1) * (height - 2));
                --page;
            }
        }
    }

    fclose(file);
    free_strings(strings, str_count);
    delwin(win);
    endwin();
    return 0;
}
