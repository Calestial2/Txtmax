#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LENGTH 4096

int is_mongo_running() {
    FILE *fp = popen("pgrep mongod", "r");
    if (!fp) return 0;
    char output[10];
    int running = fgets(output, sizeof(output), fp) != NULL;
    pclose(fp);
    return running;
}

void execute_mongo_command(const char *command) {
    char mongo_cmd[MAX_CMD_LENGTH + 50];
    snprintf(mongo_cmd, sizeof(mongo_cmd), "mongo --quiet --eval \"%s\"", command);
    FILE *fp = popen(mongo_cmd, "r");
    if (!fp) {
        printf("Error executing MongoDB command.\n");
        return;
    }
    char result[MAX_CMD_LENGTH];
    printf("\nMongoDB Output:\n");
    while (fgets(result, sizeof(result), fp)) printf("%s", result);
    printf("\n");
    pclose(fp);
}

int main() {
    printf("Starting MongoDB Editor...\n");

    if (!is_mongo_running()) {
        printf("Error: MongoDB is not running! Start with 'mongod'.\n");
        return 1;
    }

    printf("Connected to MongoDB. Type 'exit' or 'quit' to leave.\n\n");

    char command[MAX_CMD_LENGTH];

    while (1) {
        printf("Type Code: ");
        if (!fgets(command, MAX_CMD_LENGTH, stdin)) {
            printf("\nError reading input. Exiting...\n");
            break;
        }
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') command[len - 1] = '\0';
        if (!strcmp(command, "exit") || !strcmp(command, "quit")) {
            printf("Exiting MongoDB Editor...\n");
            break;
        }
        execute_mongo_command(command);
    }

    return 0;
}
