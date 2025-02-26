![Image](https://github.com/Calestial2/Txtmax/blob/8d27fd91a4ca8f583cdbe33f4ae5717a41127b4c/images/banner-image.png)

<div style="display: flex; flex-wrap: wrap; gap: 10px; justify-content: center; align-items: center; text-align: center;">
    <img src="https://img.shields.io/badge/build-passing-brightgreen" alt="Build Status">
    <img src="https://img.shields.io/badge/license-GPL%20v3-red" alt="License">
    <img src="https://img.shields.io/badge/version-14.5.14-blue" alt="Version">
    <img src="https://img.shields.io/github/forks/Calestial2/Txtmax?style=social" alt="Forks">
    <img src="https://img.shields.io/github/contributors/Calestial2/Txtmax" alt="Contributors">
    <img src="https://img.shields.io/github/downloads/Calestial2/Txtmax/total" alt="Downloads">
</div>

## Txtmax 

Txtmax is a modern, powerful, lightweight, fast, completely free, open-source advanced text editor designed for Linux. It features syntax highlighting and various file management capabilities. This program allows you to create, view, edit, delete, and get information about text files and more from the command line with ease.

## Features

- **Feature-rich:** Txtmax is very powerful and robust making it ideal for developers wanting an robust text editor
- **Lightweight and Fast:** Despite being Feature-rich, it is also lightweight with a super small size making it ideal for lower end environments and also had very fast performance
- **Rich Resources:** There's resources like built-in help command, comprehensive manual, detailed readme and also had an active community with consist new updates

## Commands

- **help:** List all available commands.
- **man txtmax:** Access the comprehensive manual for Txtmax.
- **txtmax <filename>:** Create a new file, write code in 80 languages, save and quit with :wq, type a commit message, branch, and version, and save it locally.
- **rename:** Rename a file.
- **movef:** Move multiple files to a folder.
- **copy:** Copy multiple files to a folder.
- **files:** List all files in the current directory.
- **view <filename>:** View the contents of a file with syntax highlighting.
- **edit <filename> <line>:** Edit a specific line in the file.
- **delete <filename>:** Delete a specified file.
- **search <filename>:** Search for files by name.
- **info <filename>:** Get detailed information about the file (name, extension, creation time, modification time, and version control such as commit message, branch, and version).
- **examples:** Show examples of "Hello, World!" programs in various languages including C, Python, Java, JavaScript, C++, Rust, Ruby, Elixir, Kotlin, TypeScript, Dart, Objective-C, and Go.
- **sql:** Display example queries for SQL databases, including SQL, PostgreSQL, and NoSQL (MongoDB).
- **run:** Run your code quickly without exiting Txtmax using compilers and interpreters such as GCC, Clang, g++, Python, Lua, Ruby, nasm, tcl, and rustc, perl, go, Node.js. It will prompt for the file name and extension, followed by the compiler or interpreter name, and then prompts for an external library name if theres no then type "n" and then execute the code.
- **packages:** Install packages by choosing a package manager (pip, npm, gem, go, yarn, composer, cargo, nuget, or apt), entering the package name, and installing it. (Requires prior installation of Python, Node.js, and other dependencies)
- **api:** Test RESTful APIs directly in the editor by entering a URL to fetch data via curl.
- **axios:** Fetch RESTful API data from a URL by entering a filename, writing code, quitting with :wq, and running it.
- **advance:** Enter a file name with its extension to view its content, jump to specific lines, and perform search and replace operations.
- **debug:** Debug and warn C files. Choose between debugging code or running code, then provide the project name and filename including its extension to see debug or warning messages.
- **latex:** Edit LaTeX files.
- **dotnet:** Support for .NET Framework. Choose a .NET component (currently supports .NET SDK and ASP.NET), enter a filename including its extension, write content, quit with :wq, and run the code. Use the packages command for nuget (requires prior installation of .NET).
- **tarball:** Convert files to tarball format.
- **terminal:** Access a built-in terminal to type commands directly in the editor.
- **localhost:** Start a Python or Flask app on a web server. Choose between Flask or PythonHTTP, enter a filename including its extension, and run it on localhost:8080.
- **recycle:** Recover deleted files by listing all deleted files and typing "recover <filename>.<extension>" to restore them.
- **environment:** Store your API key secrets securely. You will be prompted to provide database credentials, the API name, and its secrets. You can type 'y' or 'n' for "Debug Mode," and then you will be asked for the server port. Based on your inputs, a `.env` file will be generated.
- **ignore:** Create a `.gitignore` file. You will be prompted to choose from options such as "nodejs," "env," or "log." Based on your selection, a `.gitignore` file will be generated.
- **version:** Although not included in manual and help, it creates a version.txtmax to see details like Name, Size, Maintainer
- **sqlite:** Work with an SQLite database. You will be prompted to provide a filename, including its extension. Then, enter your SQLite code, and it will be saved locally and it will run it
- **openai:** **Integration with OpenAI** prompts for a filename, including its extension. It then prompts for Pasting OpenAI API key, it prompts for the OpenAI model name. Based on the provided inputs, it generates an python code of using OpenAI API Key and executes that Python code.
- **size:** Retrieve File Size, This prompts the user for a filename, including its extension, and then displays the file size.
- **benchmark:** Shows Execution time and CPU Usage and Additional things like System CPU Time and Total CPU Time and Max Memory usage and Page Faults and Context Switches
- **markdown:** Create Markdown files that prompt for a filename. You can write Markdown codes as easily as writing plain text. Additionally, you can use text formatting with simple commands. For example, typing `:bold hello` will highlight the text in bold, typing `:italic hello` will highlight the text in italics, and typing `:bold + italic hello` will highlight the text in bold italics. Furthermore, typing `:underlined hello` will underline the text, and typing `:strike through hello` will strike through the text. To save the file locally, use the `:wq` command to exit and save
- **format:** Format your code using `clang-format` or `black`. The process will prompt you to choose either "clang-format" or "black." Once you make a selection, for example, "clang-format," it will request the filename, including its extension, and then proceed to format the code.
- **react:** Run React Directly in Txtmax, it prompts for the app name and then creates a React app using `npx`. Next, it asks whether the user wants to create a file. If the user types 'y', the application will prompt for the filename, including its extension, and allow the user to start typing React code. Typing `:wq` will exit the editor, saving the file locally. Upon exiting, the application will ask if this is the last file and whether the user wants to start the server or continue editing. If the user types 'y', they can continuously create files; if they type 'n', a localhost server will be created
- **mongodb:** Run MongoDB Commands Directly in Txtmax, it will check if MongoDB is installed, and then you can type MongoDB codes or commands, which will be executed accordingly.
- **exit:** Exit the Txtmax editor.

## Automation

We have introduced an automation feature to simplify your tasks.

**Commands:**
- **make:** Build and test a project with Make. Enter the project name and filename including its extension, and Txtmax will generate an Makefile based on inputs and run the code.
- **gradle:** Build and test a Java project with Gradle. Provide the necessary inputs, and Txtmax will generate and run the code based on the inputs.

## AI

We Introduced an Pattern-Matching AI to help users use Txtmax Better it's had many Predefined Questions and increase your productivity.

Conversations:
1. **Running Code**
   - Queries: "run my code", "how to run"
   - Response: Steps to run code in Txtmax:
     - Step 1: Type "run" in Txtmax, and it will ask for the filename including its extension.
     - Step 2: Choose a compiler or interpreter such as GCC, Clang, Python, Node, Ruby, etc.
     - Step 3: Txtmax will seamlessly run your code.

2. **Hello World Examples**
   - Queries: "examples of hello world", "hello world example"
   - Response: Type "examples" command in Txtmax to get Hello World examples in various languages.

3. **Creating a File**
   - Queries: "create a file", "how to create"
   - Response: To create a file in Txtmax, type "create <filename>". Then write contents and save with :wq.

4. **Deleting a File**
   - Queries: "delete a file", "remove file"
   - Response: To delete a file, type "delete <filename>". This will remove the specified file.

5. **Searching for a File**
   - Queries: "search a file", "find file"
   - Response: To search for a file, type "search <filename>". It will locate files matching the given name.

6. **Listing All Files**
   - Queries: "list all files", "view files in directory"
   - Response: To list all files in the current directory, type "files".

7. **Editing a File**
   - Queries: "edit file", "modify file"
   - Response: To edit a file, type "edit <filename> <line>".

8. **Getting File Information**
   - Queries: "get file info", "file details"
   - Response: To get file details, type "info <filename>".

9. **Debugging C Files**
   - Queries: "debug c files", "check c code errors"
   - Response: To debug C files, type "debug" and provide the project name and filename.

10. **Testing APIs**
    - Queries: "test apis", "fetch restful api data"
    - Response: To test RESTful APIs, use "api" or "axios" command.

11. **Creating a Tarball**
    - Queries: "convert file to tarball", "make tar file"
    - Response: To create a tarball file, type "tarball <filename>".

12. **Installing Packages**
    - Queries: "install package", "package manager"
    - Response: To install a package, use "packages" command and choose a package manager.

13. **Editing LaTeX Files**
    - Queries: "latex files", "edit latex"
    - Response: To create and edit LaTeX files, use "latex <filename>.tex".

14. **Unrecognized Queries**
    - Response: If the query is not understood, it will respond with "I'm sorry, I don't understand your query. Try asking something related to Txtmax commands!".

## Txtmax Notebook 

**Txtmax Notebook** is an interactive notebook for Python developers written in C. 

**Features:**

- **File Handling:** You'll be prompted to enter a filename, including its extension.
- **Text-Based Cells:** Write your Python code in text-based cells with syntax highlighting.
    - `If-else` statements are highlighted in green.
    - `Int` types are highlighted in blue.
    - Comments are highlighted in black.
    - Variables are highlighted in light blue.
    - Loops are highlighted in pink.
    - `Print` and `input` functions are highlighted in orange.
- **Automatic Execution:** When you write your Python code, it will automatically execute.
- **Package Management:** You can also install packages using pip.

**Commands:**

- `save`: Creates a `.txtmaxnb` file, storing cells and their outputs.
- `exit`: Exits the Txtmax Notebook.

In Txtmax, type the command `notebook`. It will go to `system()`, compile `notebook.c`, and run `notebook.c`, allowing you to use Txtmax Notebook.

## Txtmax Auto Completion 

We introduced Txtmax Auto Completion to streamline the process of writing code, specifically C code. It's built from scratch to enhance your coding efficiency.

In Txtmax, you can use the command `auto_completion` to activate Txtmax Auto Completion. 

Upon activation, it will prompt you for the filename, including its extension. You can then write the file's contents and exit with `:wq`.

Additionally, Txtmax offers syntax highlighting:
- Keywords such as `int`, `float`, `if`, and `return` are highlighted in green.
- Loops are highlighted in magenta.
- Built-in functions (e.g., `printf`) are highlighted in red.
- Comments are highlighted in blue.

As you type code, Txtmax will suggest relevant keywords to assist you.

## Txtmax Tmux Intregration 

The Txtmax Tmux Integration enables efficient multi-task management within Txtmax through seamless integration with Tmux.

**Getting Started:**
To begin using Txtmax Tmux Integration, type "multiplexer" within Txtmax.

**How It Works:**
1. **Session Initialization:**
   - Prompts the user for a session name.
   - Creates a new Tmux session with the specified name.
   - Enters an interactive loop where the user can input commands to be sent to the Tmux session.
   - After the user types "exit," they are attached to the session to view the results of the executed commands.

**Key Features:**

1. **Session Management:**
   - Creates a new detached Tmux session.
   - Validates successful session creation.
   - Handles session names cleanly.

2. **Command Execution:**
   - Provides an interactive command prompt.
   - Executes commands within the Tmux session.
   - Supports multi-word commands.
   - Includes a built-in 'exit' command to terminate input.

3. **Safety Features:**
   - Sanitizes input to prevent errors.
   - Performs error checking for system calls.
   - Prevents buffer overflow.

4. **User Experience:**
   - Offers clear prompts and status messages.
   - Ensures a 1-second delay between commands for reliability.
   - Attaches the final sesion for direct user interaction.

**Note:** 
Tmux must be installed on the system. Tested on Linux systems with Tmux version 3.2+.

## Txtmax Security 

**Txtmax Security is a feature integrated with Txtmax. It integrates AES via OpenSSL and GPG.**

To start using Txtmax Security, type "security" in Txtmax.

You will see:
```
Welcome to Txtmax's Security with AES and GPG Integration.

Enter command (type 'help' for options):
```

**Commands:**
- `aes-encrypt`: Encrypts a file using AES-256-CBC. You will be prompted for the input file name and the encrypted output file name.
- `aes-decrypt`: Decrypts an AES-encrypted file. You will be prompted for the encrypted file name, the decrypted output file name, and the decryption password.
- `gpg-export-key`: Exports a GPG secret key. You will be asked for an email address and the private key filename.
- `gpg-delete-key`: Deletes a GPG key. You will be asked for an email address.
- `gpg-import-key`: Imports a GPG public key. You will be asked for the private key.
- `help`: Displays this help message.
- `exit`: Exits the program.

**Features:**

1. **Security Enhancements:**
   - Password input hiding during entry.
   - Uses PBKDF2 for key derivation (modern security practice).
   - Suppresses error messages for OpenSSL commands.

2. **Robust Input Handling:**
   - Proper input sanitization.
   - Filename quoting to handle spaces in paths.
   - Buffer overflow prevention.

3. **Advanced GPG Operations:**
   - Complete key deletion (both secret and public).
   - Armored key export.
   - Batch mode operations for non-interactive execution.

4. **User Experience:**
   - Clear command prompts.
   - Helpful command list.
   - Error handling for failed operations.

**Note:** This code requires OpenSSL and GPG to be installed on the system. The functionality has been tested on Linux systems and may require adjustments for other platforms.

## Txtmax Deploy 

Txtmax Deploy is an integrated feature within Txtmax designed to deploy your code effortlessly to Heroku CLI.

**Usage:**
To utilize Txtmax Deploy, simply type the command `deploy` within Txtmax.

**Features:**
- Upon activation, you will be prompted to enter the Heroku app name.
- The system will then check for the existence of `package.json`. If it does not exist, It will initialize one
- You will be asked to provide the main filename, including its extension, allowing you to write code and save it locally using the command `:wq`.
- The feature will automatically create a `Procfile` and a `.gitignore` file, including node modules and environment variables.
- Following this, a Git repository will be initialized, and you will be prompted to enter a commit message.
- Finally, the application will be pushed and deployed to Heroku CLI, and it will open in your browser.

**Note:**
Ensure that Heroku CLI is installed on your Linux system.

## Txtmax Themes

**Txtmax Themes:**

Txtmax Themes is a feature in Txtmax for installing a variety of themes.

**Commands:**
- `list`: List all available themes.
- `install [theme-name]`: Install the specified theme.
- `exit`: Exit the theme installation process.

**Txtmax Themes:**
Express yourself with Txtmax's themes! There are a variety of themes to choose from:

1. **Ubuntu-like Theme**: A polished, Ubuntu-like theme with deep purple and lighter text. Requires TrueColor (24-bit format) and RGB. Install using: `install-deep-purple`
2. **Deep Dark Theme**: A deep black theme. Install using: `install-black-theme`
3. **Greyish Theme**: A gray theme. Install using: `install-gray-theme`

## Txtmax API Tester 

**Txtmax API Tester** is an advanced tool that enables comprehensive API testing. It supports request methods via `curl`, authentication, and scripting. This allows users to test APIs directly within Txtmax, eliminating the need for external tools like Postman. While Txtmax previously had API testing commands such as `api` and `axios`, this new API Tester is significantly more advanced.

To use the Txtmax API Tester, type `testapi` within Txtmax.

**Commands:**

- **list**: Displays all available commands.
- **test**: Tests your APIs. You can specify a request method name like GET, GET with Headers, DELETE, GET with Query Parameters, GET with JSON via `curl`. For instance, when you type GET, it will prompt you for a URL and then execute the request. The process is similar for other methods.
- **auth**: Authenticates with API providers such as Google and Twitter. Typing "Google" will prompt you for a link, after which it will execute a `curl` command via `popen()`. The process is the same for Twitter.
- **script**: Tests APIs using scripting. You can specify a library name, either "axios" for JavaScript or "requests" for Python. It will then prompt you for a filename (including its extension), allow you to write your code, and execute the script automatically after saving and exiting with `:wq`.

**Features:**

- Supports request methods with real `curl` command output.
- Supports authentication.
- Supports testing.

## UI

Terminal-based, feature-rich, user-friendly, and lightweight, it presents '~/txtmax' as the command prompt, enabling users to enter commands. Upon launching, it greets with: 
```bash
Welcome to Txtmax, a Powerful Text Editor and IDE for Linux and Unix-like Systems

* Documentation: https://github.com/Calestial2/Txtmax/blob/main/README.md
* Access Manual: `man txtmax`
* Code: https://github.com/Calestial2/Txtmax/tree/main/src'
```

## Syntax Highlighting

Txtmax uses ANSI colors for syntax highlighting to enhance readability. The following colors are used:

- **Keywords:** Green
- **Strings:** Blue
- **Comments:** Yellow

## Installation and Usage

Txtmax is available on Linux, macOS, and other Unix-like systems. For Windows users, it is recommended to use WSL (Windows Subsystem for Linux) or Cygwin.

To install Txtmax, run the following command:

```bash
curl -O https://github.com/Calestial2/Txtmax/raw/main/install.sh
```

## OS Compatibility 

Available on Linux and Unix-like systems (macOS and BSD). For Other OS use Emulators like WSL and Cwgwin or MinGW

## Performance 

Extremely fast and lightweight, faster than GNU Nano and Vim because:

- C is fast in itself.
- It uses many standard libraries.

## License

This project is licensed under the GNU General Public License v3.0.
You are free to use, modify, and distribute this software under the terms of the license. See the [LICENSE](LICENSE) file for more information.

## Contributing

Contributions are welcome! Here's how you can help:

- Report bugs or request features using [GitHub Issues](https://github.com/Calestial2/Txtmax/issues)
- Submit pull requests with clear descriptions of changes.
- Ensure your code follows the style and design of the project.

For detailed guidelines, see [CONTRIBUTING.md](CONTRIBUTING.md).
