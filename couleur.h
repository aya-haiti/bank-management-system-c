#ifndef COULEUR_H
#define COULEUR_H


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

// Define ANSI color codes
#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

// Define ANSI codes for styles
#define BOLD        "\033[1m"
#define ITALIC      "\033[3m"

typedef struct {
    char *title;
    char **ops;
    int len;
    }Options;

// Function to calculate the visible length of a string (ignoring ANSI codes)
int visible_length(const char *text) {
    int len = 0;
    int in_escape = 0;

    while (*text) {
        if (*text == '\033') {  // Start of escape sequence
            in_escape = 1;
        } else if (in_escape && *text == 'm') {  // End of escape sequence
            in_escape = 0;
        } else if (!in_escape) {
            len++;  // Count visible characters
        }
        text++;
    }

    return len;
}

// Function to center text with ANSI codes based on console width
void print_centered(const char *text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // Calculate the console width
    int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    // Calculate the visible text length (ignoring ANSI codes)
    int text_len = visible_length(text);

    // Calculate padding
    int padding = (console_width - text_len) / 2;

    // Print padding spaces
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }

    // Print the actual text with ANSI color codes
    printf("%s\n", text);
}

void draw(int op, Options options) {
    system("cls");
    char line[50];
    sprintf(line, RED BOLD "%s\n" , options.title);
    print_centered(line);
    for (int i = 0 ; i <  options.len ; i++) {
        sprintf(line,ITALIC "%s%s%s" RESET, op == i ? GREEN "[" : WHITE " " , options.ops[i], op == i ? GREEN "]" : WHITE " ");
        print_centered(line);
    }
}

int select_menu(Options options) {
    int current_option = 0;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    draw(current_option, options);

    INPUT_RECORD input;
    DWORD events;
    while (1) {
        ReadConsoleInput(hInput, &input, 1, &events);
        if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown) {
            switch (input.Event.KeyEvent.wVirtualKeyCode) {
                case VK_UP:
                    if (current_option > 0) {
                        current_option--;
                        draw(current_option, options);
                    }
                    break;
                case VK_DOWN:
                    if (current_option < options.len - 1) {
                        current_option++;
                        draw(current_option, options);
                    }
                    break;
                case VK_RETURN:
                    return current_option;
            }
        }
    }
}

#endif // COULEUR_H

