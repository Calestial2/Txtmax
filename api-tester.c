#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ANSI_RED "\033[31m"
#define ANSI_RESET "\033[0m"
#define MAX_INPUT 1024
#define MAX_CMD 4096

void print_greeting() {
    printf(ANSI_RED "Welcome to Txtmax's API Tester\n"
           "It supports Request Methods, Authentication and Testing APIs via Scripting\n" ANSI_RESET);
}

void list_commands() {
    printf("Available commands:\n"
           "list       - Show available commands\n"
           "requests   - Make API requests\n"
           "auth       - Authentication with API providers\n"
           "script     - Create and run test scripts\n"
           "exit       - Exit the program\n");
}

void execute_curl(const char *command) {
    char buffer[128];
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        perror("popen failed");
        return;
    }

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
    }
    pclose(pipe);
}

void handle_get() {
    char link[MAX_INPUT];
    printf("Enter URL: ");
    fgets(link, MAX_INPUT, stdin);
    link[strcspn(link, "\n")] = 0;

    char cmd[MAX_CMD];
    snprintf(cmd, sizeof(cmd), "curl -X GET \"%s\"", link);
    execute_curl(cmd);
}

void handle_post() {
    char link[MAX_INPUT], data[MAX_CMD] = "";
    printf("Enter URL: ");
    fgets(link, MAX_INPUT, stdin);
    link[strcspn(link, "\n")] = 0;

    printf("Enter key-value pairs (empty line to finish):\n");
    while (true) {
        char pair[MAX_INPUT];
        fgets(pair, MAX_INPUT, stdin);
        if (strlen(pair) == 1) break;  // Empty line
        pair[strcspn(pair, "\n")] = 0;
        
        if (strlen(data) > 0) strcat(data, "&");
        strcat(data, pair);
    }

    char cmd[MAX_CMD];
    snprintf(cmd, sizeof(cmd), "curl -X POST \"%s\" -d \"%s\"", link, data);
    execute_curl(cmd);
}

void handle_delete() {
    char link[MAX_INPUT];
    printf("Enter URL: ");
    fgets(link, MAX_INPUT, stdin);
    link[strcspn(link, "\n")] = 0;

    char cmd[MAX_CMD];
    snprintf(cmd, sizeof(cmd), "curl -X DELETE \"%s\"", link);
    execute_curl(cmd);
}

void handle_get_headers() {
    char link[MAX_INPUT], token[MAX_INPUT];
    printf("Enter URL: ");
    fgets(link, MAX_INPUT, stdin);
    link[strcspn(link, "\n")] = 0;

    printf("Enter access token: ");
    fgets(token, MAX_INPUT, stdin);
    token[strcspn(token, "\n")] = 0;

    char cmd[MAX_CMD];
    snprintf(cmd, sizeof(cmd), "curl -X GET \"%s\" -H \"Authorization: Bearer %s\"", link, token);
    execute_curl(cmd);
}

void handle_get_json() {
    char link[MAX_INPUT];
    printf("Enter URL: ");
    fgets(link, MAX_INPUT, stdin);
    link[strcspn(link, "\n")] = 0;

    char cmd[MAX_CMD];
    snprintf(cmd, sizeof(cmd), "curl -X GET \"%s\" -H \"Accept: application/json\"", link);
    execute_curl(cmd);
}

void handle_requests() {
    printf("Select request type:\n"
           "GET\nPOST\nDELETE\nGET with Headers\nGET with Query Parameters\nGET with JSON\n");
    
    char type[MAX_INPUT];
    printf("Request type: ");
    fgets(type, MAX_INPUT, stdin);
    type[strcspn(type, "\n")] = 0;

    if (strcmp(type, "GET") == 0) handle_get();
    else if (strcmp(type, "POST") == 0) handle_post();
    else if (strcmp(type, "DELETE") == 0) handle_delete();
    else if (strcmp(type, "GET with Headers") == 0) handle_get_headers();
    else if (strcmp(type, "GET with Query Parameters") == 0) handle_get();
    else if (strcmp(type, "GET with JSON") == 0) handle_get_json();
    else printf("Invalid request type!\n");
}

void handle_auth() {
    printf("Select provider:\nGoogle\nTwitter\n");
    char provider[MAX_INPUT];
    printf("Provider: ");
    fgets(provider, MAX_INPUT, stdin);
    provider[strcspn(provider, "\n")] = 0;

    char link[MAX_INPUT];
    printf("Enter URL: ");
    fgets(link, MAX_INPUT, stdin);
    link[strcspn(link, "\n")] = 0;

    if (strcmp(provider, "Twitter") == 0) {
        char token[MAX_INPUT];
        printf("Enter Bearer token: ");
        fgets(token, MAX_INPUT, stdin);
        token[strcspn(token, "\n")] = 0;

        char cmd[MAX_CMD];
        snprintf(cmd, sizeof(cmd), "curl -X GET \"%s\" -H \"Authorization: Bearer %s\"", link, token);
        execute_curl(cmd);
    } else {
        char cmd[MAX_CMD];
        snprintf(cmd, sizeof(cmd), "curl -X GET \"%s\"", link);
        execute_curl(cmd);
    }
}

void handle_script() {
    char lib[MAX_INPUT], filename[MAX_INPUT];
    printf("Select library (axios/requests): ");
    fgets(lib, MAX_INPUT, stdin);
    lib[strcspn(lib, "\n")] = 0;

    printf("Enter filename: ");
    fgets(filename, MAX_INPUT, stdin);
    filename[strcspn(filename, "\n")] = 0;

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error creating file");
        return;
    }

    printf("Enter script contents (type :wq to save and exit):\n");
    while (true) {
        char line[MAX_INPUT];
        fgets(line, MAX_INPUT, stdin);
        
        if (strcmp(line, ":wq\n") == 0) break;
        fputs(line, fp);
    }
    fclose(fp);

    char cmd[MAX_CMD];
    if (strstr(filename, ".js")) {
        snprintf(cmd, sizeof(cmd), "node %s", filename);
    } else if (strstr(filename, ".py")) {
        snprintf(cmd, sizeof(cmd), "python %s", filename);
    } else {
        printf("Unsupported file type!\n");
        return;
    }
    system(cmd);
}

int main() {
    print_greeting();
    list_commands();

    while (true) {
        printf("api> ");
        char input[MAX_INPUT];
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) break;
        else if (strcmp(input, "list") == 0) list_commands();
        else if (strcmp(input, "requests") == 0) handle_requests();
        else if (strcmp(input, "auth") == 0) handle_auth();
        else if (strcmp(input, "script") == 0) handle_script();
        else printf("Unknown command. Type 'list' for available commands.\n");
    }

    return 0;
}
