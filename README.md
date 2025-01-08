![Image](https://github.com/Calestial2/Txtmax/blob/f7a65e499d29e184e6d06263250e8f16b753b5ba/ascii-text-art.png)
          
[![Typing SVG](https://readme-typing-svg.demolab.com?font=Fira+Code&pause=1000&color=F7992D&background=FF8C1100&width=435&lines=++++++++++++++++++++++++++++++++++Txtmax;Linux+Text-based+Editor)](https://git.io/typing-svg)
# Txtmax - Advanced Linux Text Editor

Txtmax is an advanced text editor designed for Linux, featuring syntax highlighting and various file management capabilities. This program allows you to create, view, edit, delete, and get information about text files from the command line with ease.

## Features

- **Create Files**: Create new text files and save them locally.
- **View Files**: View the contents of text files with syntax highlighting for keywords, strings, and comments.
- **Edit Files**: Edit specific lines in existing text files.
- **List Files**: List all regular files in the current directory.
- **Delete Files**: Delete specified text files.
- **Search Files**: Search for files by name in the current directory.
- **Get File Info**: Retrieve Detailed information about a file, including its name, extension, creation time, and modification time.

## Commands

- **help**: Show the help message with a list of available commands.
- **create <filename>**: Create a new file and save it locally.
- **files**: List all files in the current directory.
- **view <filename>**: View the contents of a file with syntax highlighting.
- **edit <filename> <line>**: Edit a specific line in the file.
- **delete <filename>**: Delete a specified file.
- **search <filename>**: Search for files with the specified name in the current directory.
- **info <filename>**: Get detailed information about the file (name, extension, creation time, modification time).
- **Git Integration**: Supports Git Branch, Version 
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
    gcc txtmax7.c -o txtmax7
    ```

4. **Run the Txtmax editor**:
    ```bash
    ./txtmax7
    ```

## Detailed Command Usage

### Create a File

To create a new file, use the `create` command followed by the filename:
```bash
create <filename>

You will be prompted to enter the content for the file. Type :wq to save and quit.

List Files

To list all files in the current directory, use the files command:

files

View a File

To view the contents of a file with syntax highlighting, use the view command followed by the filename:

view <filename>

Edit a File

To edit a specific line in a file, use the edit command followed by the filename and the line number:

edit <filename> <line>

You will be prompted to enter the new content for the specified line.

Delete a File

To delete a file, use the delete command followed by the filename:

delete <filename>

Search Files

To search for files with a specified name in the current directory, use the search command followed by the search string:

search <filename>

Get File Info

To view detailed information about a file, such as its name, extension, creation time, and modification time, use the info command followed by the filename:

info <filename>

Examples

Examples of Hello World in Different Programming Languages type:

examples

Help

To display the help message with a list of available commands, use the help command:

$ help

Exit

To exit the Txtmax editor, use the exit command:

exit
```

## License

This project is licensed under the GNU General Public License v3.0.
You are free to use, modify, and distribute this software under the terms of the license. See the LICENSE file for more information.

## Contributing

Contributions are welcome! Here's how you can help:
- Report bugs or request features using [GitHub Issue](https://github.com/Calestial2/Txtmax/issue)
- Submit pull requests with clear descriptions of changes.
- Ensure your code follows the style and design of the project.

### Contact

For any questions or feedback, please contact the project maintainer.
