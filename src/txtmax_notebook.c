#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CELLS 100
#define MAX_CELL_SIZE 2048
#define FILENAME_SIZE 256

// ANSI Color Codes for Syntax Highlighting
#define GREEN "\033[32m"    // If-Else
#define YELLOW "\033[33m"   // int
#define BLUE "\033[34m"     // Strings
#define BLACK "\033[30m"    // Comments
#define PINK "\033[35m"     // Loops
#define LIGHT_BLUE "\033[94m" // Variables
#define ORANGE "\033[91m"   // Print, input
#define RESET "\033[0m"     // Reset color

char notebook_filename[FILENAME_SIZE];
char py_filename[FILENAME_SIZE];

// Function to highlight syntax
void highlight_syntax(const char *code) {
    char word[256];
    int i = 0, j = 0;

    while (code[i] != '\0') {
        if (isspace(code[i]) || ispunct(code[i])) {
            word[j] = '\0';
            if (strcmp(word, "if") == 0 || strcmp(word, "else") == 0)
                printf(GREEN "%s" RESET, word);
            else if (strcmp(word, "for") == 0 || strcmp(word, "while") == 0)
                printf(PINK "%s" RESET, word);
            else if (strcmp(word, "int") == 0 || strcmp(word, "float") == 0 || strcmp(word, "str") == 0)
                printf(YELLOW "%s" RESET, word);
            else if (strcmp(word, "print") == 0 || strcmp(word, "input") == 0)
                printf(ORANGE "%s" RESET, word);
            else if (word[0] == '"' || word[0] == '\'')
                printf(BLUE "%s" RESET, word);
            else
                printf(LIGHT_BLUE "%s" RESET, word);
            printf("%c", code[i]); // Print punctuation or space
            j = 0;
        } else {
            word[j++] = code[i];
        }
        i++;
    }
    printf("\n");
}

// Function to save notebook
void save_notebook(char cells[MAX_CELLS][MAX_CELL_SIZE], int cell_count) {
    FILE *file = fopen(notebook_filename, "w");
    if (!file) {
        printf("Error saving notebook.\n");
        return;
    }
    for (int i = 0; i < cell_count; i++) {
        fprintf(file, "Cell %d:\n%s\n", i + 1, cells[i]);
    }
    fclose(file);
    printf("Notebook saved as %s\n", notebook_filename);
}

int main() {
    printf("Enter the Python filename (with extension, e.g., script.py): ");
    scanf("%255s", py_filename);
    getchar(); // Consume newline

    snprintf(notebook_filename, sizeof(notebook_filename), "%s.txtmaxnb", py_filename);

    char cells[MAX_CELLS][MAX_CELL_SIZE];
    int cell_count = 0;

    while (1) {
        printf("Cell %d: ", cell_count + 1);
        fgets(cells[cell_count], MAX_CELL_SIZE, stdin);
        cells[cell_count][strcspn(cells[cell_count], "\n")] = '\0'; // Remove newline

        if (strcmp(cells[cell_count], "exit") == 0) {
            printf("Exiting Txtmax Notebook...\n");
            break;
        } else if (strncmp(cells[cell_count], "pip install ", 12) == 0) {
            char command[1024];
            snprintf(command, sizeof(command), "python -m pip install %s", cells[cell_count] + 12);
            system(command);
        } else if (strcmp(cells[cell_count], "save") == 0) {
            save_notebook(cells, cell_count);
        } else {
            // Save Python Code
            FILE *py_file = fopen(py_filename, "a");
            if (!py_file) {
                printf("Error opening file %s\n", py_filename);
                continue;
            }
            fprintf(py_file, "%s\n", cells[cell_count]);
            fclose(py_file);

            // Highlight Syntax
            highlight_syntax(cells[cell_count]);

            // Execute Python Code
            char command[1024];
            snprintf(command, sizeof(command), "python %s", py_filename);
            system(command);
        }

        cell_count++;
        if (cell_count >= MAX_CELLS) {
            printf("Maximum cell limit reached!\n");
            break;
        }
    }
    return 0;
}
