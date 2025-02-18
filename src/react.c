#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILENAME 256
#define MAX_CODE 10000

void execute_command(const char *command) {
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to execute command\n");
        exit(1);
    }
    pclose(fp);
}

void create_react_app(char *app_name) {
    char command[MAX_FILENAME + 50];
    sprintf(command, "npx create-react-app %s", app_name);
    execute_command(command);
}

void enter_project_directory(char *app_name) {
    char command[MAX_FILENAME + 10];
    sprintf(command, "cd %s", app_name);
    system(command);
    chdir(app_name);
}

void write_react_file(char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file\n");
        return;
    }

    printf("Enter your React code below. Type ':wq' to save and exit.\n");

    char code[MAX_CODE];
    int pos = 0;
    while (1) {
        char line[500];
        fgets(line, sizeof(line), stdin);

        if (strcmp(line, ":wq\n") == 0) {
            break;
        }

        if (pos + strlen(line) < MAX_CODE) {
            strcpy(&code[pos], line);
            pos += strlen(line);
        } else {
            printf("Code limit reached!\n");
            break;
        }
    }

    fprintf(file, "%s", code);
    fclose(file);
    printf("File %s saved successfully.\n", filename);
}

void start_react_server() {
    execute_command("npm start");
}

int main() {
    char app_name[MAX_FILENAME];

    printf("Enter React app name: ");
    scanf("%s", app_name);
    getchar();

    create_react_app(app_name);
    enter_project_directory(app_name);

    while (1) {
        char choice;
        printf("Do you want to create a file? (y for yes, n for no): ");
        scanf(" %c", &choice);
        getchar();

        if (choice == 'n') break;

        char filename[MAX_FILENAME];
        printf("Enter filename including its extension: ");
        scanf("%s", filename);
        getchar();

        write_react_file(filename);

        char more_files;
        printf("Is this the last file or do you want to create more? (y to create more, n to start server): ");
        scanf(" %c", &more_files);
        getchar();

        if (more_files == 'n') break;
    }

    start_react_server();
    return 0;
}
