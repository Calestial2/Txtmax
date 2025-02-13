#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
  
void list_themes() {  
    printf("\nExpress yourself with Txtmax's Themes! There are a variety of themes to use:\n\n");  
    printf("1. Ubuntu-like Theme: An Ubuntu-like Theme with Deep Purple and Lighter Text.\n");  
    printf("   Requires TrueColor (24-bit format) and RGB.\n");  
    printf("   Install using: install-deep-purple\n\n");  
  
    printf("2. Deep Dark Theme: A Very Deep Black Theme.\n");  
    printf("   Install using: install-black-theme\n\n");  
  
    printf("3. Greyish Theme: A Gray Theme.\n");  
    printf("   Install using: install-gray-theme\n\n");  
}  
  
void install_theme(const char *theme_name, const char *cmd1, const char *cmd2) {  
    printf("Installing %s... Please wait 10 seconds.\n", theme_name);  
    sleep(10); // Simulating installation delay  
  
    printf("Applying %s...\n", theme_name);  
    system(cmd1);  
    system(cmd2);  
    printf("%s applied successfully!\n", theme_name);  
}  
  
int main() {  
    char input[256];  
  
    printf("Welcome to Txtmax Themes!\n");  
    while (1) {  
        printf("themes> ");  
        if (!fgets(input, sizeof(input), stdin)) {  
            continue; // Handle input error  
        }  
  
        // Remove newline character from input  
        input[strcspn(input, "\n")] = 0;  
  
        if (strcmp(input, "exit") == 0) {  
            printf("Exiting Txtmax Themes...\n");  
            break;  
        } else if (strcmp(input, "list") == 0) {  
            list_themes();  
        } else if (strcmp(input, "install-deep-purple") == 0) {  
            install_theme("Ubuntu-like Theme",   
                "echo -e '\\e]11;rgb:2c/00/1e\\a'",   
                "echo -e '\\e]10;rgb:dd/48/14\\a'");  
        } else if (strcmp(input, "install-black-theme") == 0) {  
            install_theme("Deep Dark Theme",   
                "echo -e '\\e]11;rgb:00/00/00\\a'",   
                "echo -e '\\e]10;rgb:ff/ff/ff\\a'");  
        } else if (strcmp(input, "install-gray-theme") == 0) {  
            install_theme("Greyish Theme",   
                "echo -e '\\e]11;rgb:33/33/33\\a'",   
                "echo -e '\\e]10;rgb:F2/F2/F2\\a'");  
        } else {  
            printf("Unknown command: %s\n", input);  
        }  
    }  
  
    return 0;  
}
