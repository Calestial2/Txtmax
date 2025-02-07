#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_INPUT 1024
#define BUFFER_SIZE 4096

void set_echo(int enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (!enable)
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void get_password(char *password, size_t max_len) {
    set_echo(0);
    fgets(password, max_len, stdin);
    password[strcspn(password, "\n")] = '\0';
    set_echo(1);
    printf("\n");
}

void execute_command(const char *cmd) {
    int result = system(cmd);
    if (result != 0) {
        fprintf(stderr, "Command failed with error code %d\n", result);
    }
}

void aes_gpg() {
    printf("Welcome to Txtmax's Security with AES, GPG Integration\n");
    
    char command[MAX_INPUT];
    char input_file[MAX_INPUT];
    char output_file[MAX_INPUT];
    char password[MAX_INPUT];
    char email[MAX_INPUT];
    char key_file[MAX_INPUT];
    char cmd[BUFFER_SIZE];

    while (1) {
        printf("\nAvailable commands:\n"
               "aes-encrypt    - Encrypt file with AES-256-CBC\n"
               "aes-decrypt    - Decrypt AES-encrypted file\n"
               "gpg-export-key - Export GPG secret key\n"
               "gpg-delete-key - Delete GPG key\n"
               "gpg-import-key - Import GPG public key\n"
               "exit           - Exit program\n"
               "Enter command: ");

        fgets(command, MAX_INPUT, stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }
        else if (strcmp(command, "aes-encrypt") == 0) {
            printf("Enter input filename: ");
            fgets(input_file, MAX_INPUT, stdin);
            input_file[strcspn(input_file, "\n")] = '\0';

            printf("Enter encrypted output filename: ");
            fgets(output_file, MAX_INPUT, stdin);
            output_file[strcspn(output_file, "\n")] = '\0';

            printf("Enter encryption password: ");
            get_password(password, MAX_INPUT);

            snprintf(cmd, BUFFER_SIZE,
                     "openssl enc -aes-256-cbc -salt -pbkdf2 -in \"%s\" -out \"%s\" -pass pass:\"%s\" 2>/dev/null",
                     input_file, output_file, password);
            execute_command(cmd);
        }
        else if (strcmp(command, "aes-decrypt") == 0) {
            printf("Enter encrypted filename: ");
            fgets(input_file, MAX_INPUT, stdin);
            input_file[strcspn(input_file, "\n")] = '\0';

            printf("Enter decrypted output filename: ");
            fgets(output_file, MAX_INPUT, stdin);
            output_file[strcspn(output_file, "\n")] = '\0';

            printf("Enter decryption password: ");
            get_password(password, MAX_INPUT);

            snprintf(cmd, BUFFER_SIZE,
                     "openssl enc -aes-256-cbc -d -pbkdf2 -in \"%s\" -out \"%s\" -pass pass:\"%s\" 2>/dev/null",
                     input_file, output_file, password);
            execute_command(cmd);
        }
        else if (strcmp(command, "gpg-export-key") == 0) {
            printf("Enter email address: ");
            fgets(email, MAX_INPUT, stdin);
            email[strcspn(email, "\n")] = '\0';

            printf("Enter private key filename: ");
            fgets(key_file, MAX_INPUT, stdin);
            key_file[strcspn(key_file, "\n")] = '\0';

            snprintf(cmd, BUFFER_SIZE,
                     "gpg --armor --export-secret-keys \"%s\" > \"%s\"",
                     email, key_file);
            execute_command(cmd);
        }
        else if (strcmp(command, "gpg-delete-key") == 0) {
            printf("Enter email address to delete: ");
            fgets(email, MAX_INPUT, stdin);
            email[strcspn(email, "\n")] = '\0';

            snprintf(cmd, BUFFER_SIZE,
                     "gpg --batch --yes --delete-secret-and-public-key \"%s\"",
                     email);
            execute_command(cmd);
        }
        else if (strcmp(command, "gpg-import-key") == 0) {
            printf("Enter public key filename: ");
            fgets(key_file, MAX_INPUT, stdin);
            key_file[strcspn(key_file, "\n")] = '\0';

            snprintf(cmd, BUFFER_SIZE, "gpg --import \"%s\"", key_file);
            execute_command(cmd);
        }
        else {
            printf("Invalid command. Please try again.\n");
        }
    }
}

int main() {
    aes_gpg();
    return 0;
}
