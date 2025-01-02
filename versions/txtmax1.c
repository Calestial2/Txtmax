#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

#define MAX_INPUT 256
#define MAX_CONTENT 1024

// ANSI Colors for Syntax Highlighting
#define COLOR_RESET "\033[0m"
#define COLOR_KEYWORD "\033[1;32m"
#define COLOR_STRING "\033[1;34m"
#define COLOR_COMMENT "\033[1;33m"

const char *keywords[] = {"int", "return", "if", "else", "while", "for", "void", "char", "include", "define", NULL};

// Function to check if a word is a keyword
int is_keyword(const char *word) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Syntax Highlighting Function
void syntax_highlight(const char *line) {
    char buffer[MAX_INPUT];
    int idx = 0;
    int in_string = 0, in_comment = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '\"') {
            if (!in_comment) {
                in_string = !in_string;
                printf(COLOR_STRING "%c" COLOR_RESET, line[i]);
                continue;
            }
        } else if (line[i] == '/' && line[i + 1] == '/') {
            if (!in_string) {
                in_comment = 1;
                printf(COLOR_COMMENT "%s" COLOR_RESET, line + i);
                break;
            }
        }

        if (in_string || in_comment) {
            printf("%c", line[i]);
            continue;
        }

        if (isalnum(line[i]) || line[i] == '_') {
            buffer[idx++] = line[i];
        } else {
            if (idx > 0) {
                buffer[idx] = '\0';
                if (is_keyword(buffer))
                    printf(COLOR_KEYWORD "%s" COLOR_RESET, buffer);
                else
                    printf("%s", buffer);
                idx = 0;
            }
            printf("%c", line[i]);
        }
    }
    if (idx > 0) {
        buffer[idx] = '\0';
        if (is_keyword(buffer))
            printf(COLOR_KEYWORD "%s" COLOR_RESET, buffer);
        else
            printf("%s", buffer);
    }
}

// Command Handlers
void create_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error creating file");
        return;
    }
    printf("Enter content (type ':wq' to save and quit):\n");
    char line[MAX_INPUT];
    while (1) {
        fgets(line, MAX_INPUT, stdin);
        if (strcmp(line, ":wq\n") == 0)
            break;
        fprintf(file, "%s", line);
    }
    fclose(file);
    printf("File '%s' created and saved locally.\n", filename);
}

void list_files() {
    struct dirent *entry;
    DIR *dir = opendir(".");
    if (!dir) {
        perror("Error opening directory");
        return;
    }
    printf("Files in the local directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) // Only list regular files
            printf("  %s\n", entry->d_name);
    }
    closedir(dir);
}

void view_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    char line[MAX_INPUT];
    int line_number = 1;
    printf("Contents of '%s':\n", filename);
    while (fgets(line, sizeof(line), file)) {
        printf("%3d | ", line_number++);
        syntax_highlight(line);
    }
    fclose(file);
}

void edit_file(const char *filename, int line_to_edit) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Error opening file for editing");
        return;
    }

    char content[MAX_CONTENT][MAX_INPUT];
    int total_lines = 0;

    // Read the file into memory
    while (fgets(content[total_lines], MAX_INPUT, file)) {
        total_lines++;
    }

    if (line_to_edit < 1 || line_to_edit > total_lines) {
        printf("Invalid line number. The file has %d lines.\n", total_lines);
        fclose(file);
        return;
    }

    printf("Current line %d: %s", line_to_edit, content[line_to_edit - 1]);
    printf("Enter the new content for line %d: ", line_to_edit);
    fgets(content[line_to_edit - 1], MAX_INPUT, stdin);

    // Rewind and write back the modified content
    freopen(filename, "w", file); // Reopen file in write mode to overwrite content
    for (int i = 0; i < total_lines; i++) {
        fputs(content[i], file);
    }

    fclose(file);
    printf("Line %d updated successfully in '%s'.\n", line_to_edit, filename);
}

void delete_file(const char *filename) {
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Error deleting file");
    }
}

// Help Function
void help() {
    printf("Commands:\n");
    printf("  help                    Show this help message\n");
    printf("  create <filename>       Create a new file and save locally\n");
    printf("  files                   List all files in the current directory\n");
    printf("  view <filename>         View file contents with syntax highlighting\n");
    printf("  edit <filename> <line>  Edit a specific line in the file\n");
    printf("  delete <filename>       Delete a file\n");
    printf("  exit                    Exit txtmax\n");
}

// Main Function
int main() {
    printf("Welcome to txtmax - Advanced Linux Text Editor\n");
    printf("Type '$ help' for the list of commands.\n");

    char input[MAX_INPUT];
    while (1) {
        printf("\ntxtmax> ");
        if (!fgets(input, sizeof(input), stdin))
            break;

        // Remove trailing newline
        input[strcspn(input, "\n")] = 0;

        if (strncmp(input, "$ help", 6) == 0) {
            help();
        } else if (strncmp(input, "create ", 7) == 0) {
            create_file(input + 7);
        } else if (strcmp(input, "files") == 0) {
            list_files();
        } else if (strncmp(input, "view ", 5) == 0) {
            view_file(input + 5);
        } else if (strncmp(input, "edit ", 5) == 0) {
            char *filename = strtok(input + 5, " ");
            char *line_str = strtok(NULL, " ");
            if (!filename || !line_str) {
                printf("Usage: edit <filename> <line>\n");
                continue;
            }
            int line_to_edit = atoi(line_str);
            edit_file(filename, line_to_edit);
        } else if (strncmp(input, "delete ", 7) == 0) {
            delete_file(input + 7);
        } else if (strcmp(input, "exit") == 0) {
            printf("Exiting txtmax. Goodbye!\n");
            break;
        } else {
            printf("Unknown command. Type '$ help' for a list of commands.\n");
        }
    }
    return 0;
}
