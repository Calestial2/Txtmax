#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define MAX_INPUT 1024
#define NUM_KEYWORDS 14
#define NUM_BUILTINS 5
#define MAX_LINES 1000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24

// Define C language keywords and built-in functions
const char *keywords[] = {
    "int", "float", "char", "double", "if", "else", "for", "while", "do", "return",
    "void", "switch", "case", "default"
};

const char *builtins[] = {
    "printf", "scanf", "malloc", "free", "strlen"
};

const char *loop_keywords[] = { "for", "while", "do" };
const char *comment_symbols[] = { "//", "/*", "*/" };

typedef struct {
    char lines[MAX_LINES][MAX_INPUT];
    int line_count;
} CodeFile;

// Function prototypes
void highlight_syntax(WINDOW *win, char *input, int line_num);
void autocomplete_suggestions(WINDOW *win, char *input, int cursor_pos);
void load_file(const char *filename, CodeFile *file);
void save_file(const char *filename, CodeFile *file);
void display_code(WINDOW *win, CodeFile *file, int current_line, int cursor_pos);

int main() {
    char filename[MAX_INPUT];
    char code[MAX_INPUT];
    int ch, cursor_pos = 0;
    int x = 0, y = 0, current_line = 0;
    CodeFile code_file;
    code_file.line_count = 0;

    // Initialize ncurses
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Keyword highlight color
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK); // Loop keyword color
    init_pair(3, COLOR_RED, COLOR_BLACK); // Builtin function color
    init_pair(4, COLOR_BLUE, COLOR_BLACK); // Comment color

    // Prompt for file name
    printw("Enter the filename (including .c extension): ");
    refresh();
    getstr(filename);

    // Load or create file
    load_file(filename, &code_file);

    // Main editing loop
    printw("\nStart typing your C code (Press F1 to save and exit):\n");
    move(2, 0);
    
    while (1) {
        display_code(stdscr, &code_file, current_line, cursor_pos);

        ch = getch();

        if (ch == KEY_F(1)) {
            // Save and exit
            save_file(filename, &code_file);
            break;
        }

        // Handle editing and cursor movement
        if (ch == 10) { // Newline character (Enter)
            code_file.lines[current_line][cursor_pos] = '\0';
            current_line++;
            cursor_pos = 0;
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            if (cursor_pos > 0) {
                cursor_pos--;
            }
        } else if (ch == KEY_UP) {
            if (current_line > 0) {
                current_line--;
            }
        } else if (ch == KEY_DOWN) {
            if (current_line < code_file.line_count - 1) {
                current_line++;
            }
        } else if (ch == KEY_LEFT) {
            if (cursor_pos > 0) {
                cursor_pos--;
            }
        } else if (ch == KEY_RIGHT) {
            if (cursor_pos < strlen(code_file.lines[current_line])) {
                cursor_pos++;
            }
        } else {
            code_file.lines[current_line][cursor_pos++] = ch;
        }

        // Syntax highlighting and auto-completion
        clear();
        highlight_syntax(stdscr, code_file.lines[current_line], current_line);
        autocomplete_suggestions(stdscr, code_file.lines[current_line], cursor_pos);
    }

    // Clean up ncurses
    endwin();
    return 0;
}

// Function to perform syntax highlighting
void highlight_syntax(WINDOW *win, char *input, int line_num) {
    int i = 0, start_pos = 0;
    char word[100];
    
    // Highlight line number
    attron(COLOR_PAIR(1));
    mvprintw(line_num + 2, 0, "%d: ", line_num + 1);
    attroff(COLOR_PAIR(1));

    // Loop through the line
    while (input[i] != '\0') {
        if (isspace(input[i]) || input[i] == ';' || input[i] == '(' || input[i] == ')') {
            i++;
            continue;
        }

        int j = 0;
        while (isalpha(input[i])) {
            word[j++] = input[i++];
        }
        word[j] = '\0';

        // Check if word is a keyword
        int highlighted = 0;
        for (int k = 0; k < NUM_KEYWORDS; k++) {
            if (strcmp(word, keywords[k]) == 0) {
                attron(COLOR_PAIR(1)); // Green for keywords
                highlighted = 1;
                break;
            }
        }

        // Check if word is a built-in function
        for (int k = 0; k < NUM_BUILTINS; k++) {
            if (strcmp(word, builtins[k]) == 0) {
                attron(COLOR_PAIR(3)); // Red for built-ins
                highlighted = 1;
                break;
            }
        }

        // Check if word is a loop keyword
        for (int k = 0; k < 3; k++) {
            if (strcmp(word, loop_keywords[k]) == 0) {
                attron(COLOR_PAIR(2)); // Magenta for loops
                highlighted = 1;
                break;
            }
        }

        // Check if it's a comment
        if (strncmp(input + i, "//", 2) == 0 || strncmp(input + i, "/*", 2) == 0) {
            attron(COLOR_PAIR(4)); // Blue for comments
        }

        // Print the word
        printw("%s", word);
        if (highlighted) {
            attroff(COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3) | COLOR_PAIR(4));
        }
    }
}

// Function to provide autocomplete suggestions
void autocomplete_suggestions(WINDOW *win, char *input, int cursor_pos) {
    // Provide suggestions only when user starts typing
    if (cursor_pos > 0 && isalpha(input[cursor_pos - 1])) {
        int start_pos = cursor_pos - 1;
        while (start_pos > 0 && isalpha(input[start_pos - 1])) {
            start_pos--;
        }
        char prefix[100];
        strncpy(prefix, &input[start_pos], cursor_pos - start_pos);
        prefix[cursor_pos - start_pos] = '\0';

        // Display suggestions below the input area
        mvprintw(5, 0, "Suggestions for '%s':", prefix);
        for (int i = 0; i < NUM_KEYWORDS; i++) {
            if (strncmp(prefix, keywords[i], strlen(prefix)) == 0) {
                printw("\n- %s", keywords[i]);
            }
        }
    }
}

// Function to load file content
void load_file(const char *filename, CodeFile *file) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printw("File does not exist. A new file will be created.\n");
        return;
    }

    char line[MAX_INPUT];
    while (fgets(line, MAX_INPUT, f)) {
        strcpy(file->lines[file->line_count++], line);
    }
    fclose(f);
}

// Function to save file content
void save_file(const char *filename, CodeFile *file) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printw("Error saving file.\n");
        return;
    }

    for (int i = 0; i < file->line_count; i++) {
        fputs(file->lines[i], f);
    }
    fclose(f);
    printw("\nFile saved successfully!\n");
}

// Function to display the code in the editor
void display_code(WINDOW *win, CodeFile *file, int current_line, int cursor_pos) {
    clear();
    
    // Display line numbers and code lines
    for (int i = 0; i < SCREEN_HEIGHT - 2 && i + current_line < file->line_count; i++) {
        mvprintw(i + 2, 0, "%d: %s", i + current_line + 1, file->lines[i + current_line]);
    }

    move(current_line + 2, cursor_pos); // Move cursor to current position
    refresh();
}
