#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 256
#define MAX_LINE 1024

// Function to execute shell commands
void run_command(char *const args[]) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            fprintf(stderr, "Error: Command failed - %s\n", args[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
}

// Function to read user input
void get_input(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (!fgets(buffer, size, stdin)) {
        perror("fgets failed");
        exit(EXIT_FAILURE);
    }
    buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline
}

// Function to write content to a file
void write_to_file(const char *filename, const char *content) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s", content);
    fclose(fp);
}

// Function to read multiline input until ":wq"
void create_code_file(const char *filename) {
    printf("Enter file content (type ':wq' to save and exit):\n");
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File creation failed");
        exit(EXIT_FAILURE);
    }
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), stdin)) {
        if (strcmp(line, ":wq\n") == 0) break;
        fputs(line, fp);
    }
    fclose(fp);
}

// Function to detect the Git branch
void get_git_branch(char *branch, size_t size) {
    FILE *fp = popen("git symbolic-ref --short HEAD 2>/dev/null || echo main", "r");
    if (!fp) {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }
    fgets(branch, size, fp);
    branch[strcspn(branch, "\n")] = '\0';  
    pclose(fp);
}

// Function to check if Git is already initialized
int is_git_initialized() {
    return system("git rev-parse --is-inside-work-tree > /dev/null 2>&1") == 0;
}

// Function to check if package.json exists (for npm projects)
int package_json_exists() {
    return access("package.json", F_OK) == 0;
}

// Function to install dependencies (either manually or from package.json)
void install_dependencies() {
    char dependencies[MAX_INPUT];
    get_input("Enter npm dependencies (or leave blank to use package.json): ", dependencies, sizeof(dependencies));

    if (strlen(dependencies) > 0) {
        char npm_install_cmd[MAX_INPUT + 20];
        snprintf(npm_install_cmd, sizeof(npm_install_cmd), "npm install %s", dependencies);
        char *npm_install[] = {"/bin/sh", "-c", npm_install_cmd, NULL};
        run_command(npm_install);
    } else if (package_json_exists()) {
        char *npm_install[] = {"npm", "install", NULL};
        run_command(npm_install);
    } else {
        printf("No dependencies to install.\n");
    }
}

int main() {
    char app_name[MAX_INPUT], filename[MAX_INPUT], commit_msg[MAX_INPUT], branch[MAX_INPUT];

    // Get app name
    get_input("Heroku App Name: ", app_name, sizeof(app_name));

    // Create Heroku app
    char *heroku_create[] = {"heroku", "create", app_name, NULL};
    run_command(heroku_create);

    // Initialize npm if package.json is missing
    if (!package_json_exists()) {
        printf("No package.json found. Initializing npm project...\n");
        char *npm_init[] = {"npm", "init", "-y", NULL};
        run_command(npm_init);
    }

    // Get filename
    get_input("Enter main file name (with extension): ", filename, sizeof(filename));

    // Create main file
    create_code_file(filename);

    // Create Procfile
    char procfile_content[MAX_INPUT];
    snprintf(procfile_content, sizeof(procfile_content), "web: node %s\n", filename);
    write_to_file("Procfile", procfile_content);

    // Create .gitignore
    write_to_file(".gitignore", "node_modules/\n.env\n");

    // Initialize Git if not already initialized
    if (!is_git_initialized()) {
        printf("Initializing Git repository...\n");
        char *git_init[] = {"git", "init", NULL};
        run_command(git_init);
    }

    // Get commit message
    get_input("Enter commit message: ", commit_msg, sizeof(commit_msg));

    // Add and commit changes
    char *git_add[] = {"git", "add", ".", NULL};
    run_command(git_add);

    char *git_commit[] = {"git", "commit", "-m", commit_msg, NULL};
    run_command(git_commit);

    // Determine Git branch
    get_git_branch(branch, sizeof(branch));

    // Install dependencies
    install_dependencies();

    // Push to Heroku
    char git_push_cmd[MAX_INPUT + 20];
    snprintf(git_push_cmd, sizeof(git_push_cmd), "git push heroku %s", branch);
    char *git_push[] = {"/bin/sh", "-c", git_push_cmd, NULL};
    run_command(git_push);

    // Open Heroku app
    char *heroku_open[] = {"heroku", "open", NULL};
    run_command(heroku_open);

    printf("\n✅ Deployment complete! Your app '%s' is live.\n", app_name);
    return 0;
}
