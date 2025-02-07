#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define INPUT_SIZE 1024
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

void print_help() {
    printf("\nAvailable commands:\n"
           "  aes-encrypt    - Encrypt file with AES-256-CBC\n"
           "  aes-decrypt    - Decrypt AES-encrypted file\n"
           "  gpg-export-key - Export GPG secret key\n"
           "  gpg-delete-key - Delete GPG key\n"
           "  gpg-import-key - Import GPG public key\n"
           "  help           - Show this help message\n"
           "  exit           - Exit program\n");
}

void aes_gpg() {
    printf("Welcome to Txtmax's Security with AES, GPG Integration\n");

    char command[INPUT_SIZE];
    char input_file[INPUT_SIZE];
    char output_file[INPUT_SIZE];
    char password[INPUT_SIZE];
    char email[INPUT_SIZE];
    char key_file[INPUT_SIZE];
    char cmd[BUFFER_SIZE];

    while (1) {
        printf("\nEnter command (type 'help' for options): ");
        fgets(command, INPUT_SIZE, stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }
        else if (strcmp(command, "help") == 0) {
            print_help();
        }
        else if (strcmp(command, "aes-encrypt") == 0) {
            printf("Enter input filename: ");
            fgets(input_file, INPUT_SIZE, stdin);
            input_file[strcspn(input_file, "\n")] = '\0';

            printf("Enter encrypted output filename: ");
            fgets(output_file, INPUT_SIZE, stdin);
            output_file[strcspn(output_file, "\n")] = '\0';

            printf("Enter encryption password: ");
            get_password(password, INPUT_SIZE);

            snprintf(cmd, BUFFER_SIZE,
                     "openssl enc -aes-256-cbc -salt -pbkdf2 -in \"%s\" -out \"%s\" -pass pass:\"%s\" 2>/dev/null",
                     input_file, output_file, password);
            execute_command(cmd);
        }
        else if (strcmp(command, "aes-decrypt") == 0) {
            printf("Enter encrypted filename: ");
            fgets(input_file, INPUT_SIZE, stdin);
            input_file[strcspn(input_file, "\n")] = '\0';

            printf("Enter decrypted output filename: ");
            fgets(output_file, INPUT_SIZE, stdin);
            output_file[strcspn(output_file, "\n")] = '\0';

            printf("Enter decryption password: ");
            get_password(password, INPUT_SIZE);

            snprintf(cmd, BUFFER_SIZE,
                     "openssl enc -aes-256-cbc -d -pbkdf2 -in \"%s\" -out \"%s\" -pass pass:\"%s\" 2>/dev/null",
                     input_file, output_file, password);
            execute_command(cmd);
        }
        else if (strcmp(command, "gpg-export-key") == 0) {
            printf("Enter email address: ");
            fgets(email, INPUT_SIZE, stdin);
            email[strcspn(email, "\n")] = '\0';

            printf("Enter private key filename: ");
            fgets(key_file, INPUT_SIZE, stdin);
            key_file[strcspn(key_file, "\n")] = '\0';

            snprintf(cmd, BUFFER_SIZE,
                     "gpg --armor --export-secret-keys \"%s\" > \"%s\"",
                     email, key_file);
            execute_command(cmd);
        }
        else if (strcmp(command, "gpg-delete-key") == 0) {
            printf("Enter email address to delete: ");
            fgets(email, INPUT_SIZE, stdin);
            email[strcspn(email, "\n")] = '\0';

            snprintf(cmd, BUFFER_SIZE,
                     "gpg --batch --yes --delete-secret-and-public-key \"%s\"",
                     email);
            execute_command(cmd);
        }
        else if (strcmp(command, "gpg-import-key") == 0) {
            printf("Enter public key filename: ");
            fgets(key_file, INPUT_SIZE, stdin);
            key_file[strcspn(key_file, "\n")] = '\0';

            snprintf(cmd, BUFFER_SIZE, "gpg --import \"%s\"", key_file);
            execute_command(cmd)
        }
        else {
            printf("Invalid command. Type 'help' for a list of commands.\n");
        }
    }
}

int main() {
    aes_gpg();
    return 0;
}
