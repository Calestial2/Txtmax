#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 2048

void mongo_shell_loop() {
    char *input = (char *)malloc(MAX_INPUT_SIZE);
    if (input == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    printf("MongoDB Shell Interface - Type 'exit' to quit\n");

    while (1) {
        printf("Type Code: ");
        
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            perror("Error reading input");
            free(input);
            exit(EXIT_FAILURE);
        }

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            break;
        }

        if (strlen(input) == 0) {
            fprintf(stderr, "Error: Empty input. Please enter valid MongoDB code.\n");
            continue;
        }

        char *mongo_command = (char *)malloc(strlen(input) + 50);
        if (mongo_command == NULL) {
            perror("Memory allocation failed");
            free(input);
            exit(EXIT_FAILURE);
        }

        snprintf(mongo_command, strlen(input) + 50, "mongo --eval \"%s\"", input);
        
        if (system(mongo_command) == -1) {
            perror("Error executing MongoDB command");
        }

        free(mongo_command);
    }

    free(input);
    printf("Exiting MongoDB shell interface.\n");
}

int main() {
    mongo_shell_loop();
    return 0;
}
