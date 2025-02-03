#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define MAX_INPUT 1024
#define NUM_KEYWORDS 14
#define NUM_BUILTINS 5
#define MAX_LINES 1000

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
void highlight_syntax(char *input, int line_num);
void autocomplete_suggestions(char *input, int cursor_pos);
void load_file(const char *filename, CodeFile *file);
void save_file(const char *filename, CodeFile *file);
void display_code(CodeFile *file, int current_line, int cursor_pos);

int main() {
    char filename[MAX_INPUT];
    char code[MAX_INPUT];
    int ch, cursor_pos = 0;
    int current_line = 0;
    CodeFile code_file;
    code_file.line_count = 0;

    // Prompt for file name
    printf("Enter the filename (including .c extension): ");
    fgets(filename, MAX_INPUT, stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove newline character

    // Load or create file
    load_file(filename, &code_file);

    // Main editing loop
    printf("\nStart typing your C code (Type ':wq' to save and exit):\n");

    while (1) {
        display_code(&code_file, current_line, cursor_pos);

        // Get user input
        fgets(code, MAX_INPUT, stdin);
        code[strcspn(code, "\n")] = 0; // Remove newline character

        if (strcmp(code, ":wq") == 0) {
            // Save and exit
            save_file(filename, &code_file);
            break;
        }

        // Handle editing and cursor movement
        if (code_file.line_count < MAX_LINES) {
            strcpy(code_file.lines[code_file.line_count++], code);
        }

        // Syntax highlighting and auto-completion
        highlight_syntax(code, current_line);
        autocomplete_suggestions(code, cursor_pos);
    }

    return 0;
}

// Function to perform syntax highlighting
void highlight_syntax(char *input, int line_num) {
    int i = 0, start_pos = 0;
    char word[100];

    printf("%d: ", line_num + 1); // Print line number

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
                printf("\033[1;32m%s\033[0m ", word); // Green for keywords
                highlighted = 1;
                break;
            }
        }

        // Check if word is a built-in function
        for (int k = 0; k < NUM_BUILTINS; k++) {
            if (strcmp(word, builtins[k]) == 0) {
                printf("\033[1;31m%s\033[0m ", word); // Red for built-ins
                highlighted = 1;
                break;
            }
        }

        // Check if word is a loop keyword
        for (int k = 0; k < 3; k++) {
            if (strcmp(word, loop_keywords[k]) == 0) {
                printf("\033[1;35m%s\033[0m ", word); // Magenta for loops
                highlighted = 1;
                break;
            }
        }

        // Check if it's a comment
        if (strncmp(input + i, "//", 2) == 0 || strncmp(input + i, "/*", 2) == 0) {
            printf("\033[1;34m%s\033[0m ", word); // Blue for comments
        }

        // If no highlighting, print normally
        if (!highlighted) {
            printf("%s ", word);
        }
    }

    printf("\n");
}

// Function to provide autocomplete suggestions
void autocomplete_suggestions(char *input, int cursor_pos) {
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
        printf("Suggestions for '%s':\n", prefix);
        for (int i = 0; i < NUM_KEYWORDS; i++) {
            if (strncmp(prefix, keywords[i], strlen(prefix)) == 0) {
                printf("- %s\n", keywords[i]);
            }
        }
    }
}

// Function to load file content
void load_file(const char *filename, CodeFile *file) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("File does not exist. A new file will be created.\n");
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
        printf("Error saving file.\n");
        return;
    }

    for (int i = 0; i < file->line_count; i++) {
        fputs(file->lines[i], f);
    }
    fclose(f);
    printf("\nFile saved successfully!\n");
}

// Function to display the code in the editor
void display_code(CodeFile *file, int current_line, int cursor_pos) {
    // Display line numbers and code lines
    for (int i = 0; i < 20 && i + current_line < file->line_count; i++) {
        printf("%d: %s", i + current_line + 1, file->lines[i + current_line]);
    }
}
