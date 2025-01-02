# Txtmax - Advanced Linux Text Editor

Txtmax is an advanced text editor designed for Linux, featuring syntax highlighting and various file management capabilities. This program allows you to create, view, edit, and delete text files from the command line with ease.

## Features

- **Create Files**: Create new text files and save them locally.
- **View Files**: View the contents of text files with syntax highlighting for keywords, strings, and comments.
- **Edit Files**: Edit specific lines in existing text files.
- **List Files**: List all regular files in the current directory.
- **Delete Files**: Delete specified text files.

## Commands

- **help**: Show the help message with a list of available commands.
- **create <filename>**: Create a new file and save it locally.
- **files**: List all files in the current directory.
- **view <filename>**: View the contents of a file with syntax highlighting.
- **edit <filename> <line>**: Edit a specific line in the file.
- **delete <filename>**: Delete a specified file.
- **exit**: Exit the Txtmax editor.

## Syntax Highlighting

Txtmax uses ANSI colors for syntax highlighting to enhance readability. The following colors are used:

- **Keywords**: Green
- **Strings**: Blue
- **Comments**: Yellow

## Installation and Usage

To get started with Txtmax, follow these steps:

1. **Clone the repository**:
    ```bash
    git clone https://github.com/Calestial2/Txtmax.git
    ```
   
2. **Navigate to the Txtmax directory**:
    ```bash
    cd Txtmax
    ```

3. **Compile the code**:
    ```bash
    gcc txtmax.c -o txtmax
    ```

4. **Run the Txtmax editor**:
    ```bash
    ./txtmax
    ```

## Detailed Command Usage

### Create a File

To create a new file, use the `create` command followed by the filename:
```bash
create <filename>
```
You will be prompted to enter the content for the file. Type `:wq` to save and quit.

### List Files

To list all files in the current directory, use the `files` command:
```bash
files
```

### View a File

To view the contents of a file with syntax highlighting, use the `view` command followed by the filename:
```bash
view <filename>
```

### Edit a File

To edit a specific line in a file, use the `edit` command followed by the filename and the line number:
```bash
edit <filename> <line>
```
You will be prompted to enter the new content for the specified line.

### Delete a File

To delete a file, use the `delete` command followed by the filename:
```bash
delete <filename>
```

### Help

To display the help message with a list of available commands, use the `help` command:
```bash
$ help
```

### Exit

To exit the Txtmax editor, use the `exit` command:
```bash
exit
```

## License

This project is licensed under the GNU General Public License (GPL). See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Feel free to submit issues and pull requests to improve Txtmax.

## Contact

For any questions or feedback, please contact the project maintainer.
