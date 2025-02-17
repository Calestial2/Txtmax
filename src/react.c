#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void react() {
    char appName[256];
    char fileName[256];
    char userChoice;
    char isLastFile;

    printf("Enter the name of your React app (including extension): ");
    scanf("%s", appName);

    char command[512];
    snprintf(command, sizeof(command), "npx create-react-app %s", appName);
    printf("Creating React app...\n");
    system(command);

    snprintf(command, sizeof(command), "cd %s", appName);
    system(command);

    while (1) {
        printf("Do you want to create a file? (Type y for yes and n for no): ");
        scanf(" %c", &userChoice);

        if (userChoice == 'n') {
            printf("Exiting file creation...\n");
            break;
        }

        if (userChoice == 'y') {
            printf("Enter the filename (including extension): ");
            scanf("%s", fileName);

            FILE *file = fopen(fileName, "w");
            if (file == NULL) {
                printf("Error creating file %s\n", fileName);
                continue;
            }

            printf("File %s created successfully. Enter your React code below (Type ':wq' to save and exit):\n", fileName);
            char codeLine[1024];

            while (1) {
                printf(">> ");
                fgets(codeLine, sizeof(codeLine), stdin);

                if (strncmp(codeLine, ":wq", 3) == 0) {
                    printf("File saved.\n");
                    break;
                }

                fprintf(file, "%s", codeLine);
            }

            fclose(file);

            while (1) {
                printf("Is this the last file? (Type y for yes and n for no): ");
                scanf(" %c", &isLastFile);

                if (isLastFile == 'n') {
                    break;
                } else if (isLastFile == 'y') {
                    printf("Last file saved.\n");
                    snprintf(command, sizeof(command), "cd %s", appName);
                    system(command);
                    system("npm start");
                    return;
                } else {
                    printf("Invalid choice, please type 'y' or 'n'.\n");
                }
            }
        } else {
            printf("Invalid choice, please type 'y' or 'n'.\n");
        }
    }
}

int main() {
    react();
    return 0;
}
