#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_welcome_message() {
    printf("Welcome to Txtmax Packages!\n\n");
    printf("Read README at GitHub/txtmax-package for More Info\n\n");
    printf("Type \"list\" for List of all Available Packages\n\n");
}

void list_packages() {
    printf("Here's the List of all Packages:\n");
    printf("Example: An Example Package for Text (Install via: pkg install example)\n");
    // You can add more packages here in the future.
}

void install_package(const char* package_name) {
    char command[256];
    // Construct the command to run gcc on the package.
    snprintf(command, sizeof(command), "gcc %splugin.c -o %s", package_name, package_name);
    printf("Installing package: %s\n", package_name);
    
    // Run the gcc command using system()
    if (system(command) == 0) {
        printf("Package '%s' installed successfully!\n", package_name);
    } else {
        printf("Error installing package '%s'.\n", package_name);
    }
}

int main() {
    char command[256];

    // Show the welcome message initially
    show_welcome_message();

    // Prompt the user for input
    while (1) {
        printf("~/packages> ");
        fgets(command, sizeof(command), stdin);
        
        // Remove the newline character from the end of the input
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "list") == 0) {
            list_packages();
        } else if (strncmp(command, "pkg install ", 12) == 0) {
            // Extract the package name after "pkg install "
            char package_name[128];
            sscanf(command + 12, "%s", package_name);
            install_package(package_name);
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting Txtmax Packages...\n");
            break;
        } else {
            printf("Unknown command: %s\n", command);
        }
    }

    return 0;
}
