![Image](https://github.com/Calestial2/Txtmax/blob/f7a65e499d29e184e6d06263250e8f16b753b5ba/ascii-text-art.png)
          
[![Typing SVG](https://readme-typing-svg.demolab.com?font=Fira+Code&pause=1000&color=F7992D&background=FF8C1100&width=435&lines=++++++++++++++++++++++++++++++++++Txtmax;Linux+Text-based+Editor)](https://git.io/typing-svg)

![Build Status](https://img.shields.io/badge/build-passing-brightgreen?style=flat-square&logo=github) ![Version](https://img.shields.io/badge/version-12.1.1-blue?style=flat-square) ![License](https://img.shields.io/badge/license-GPL%20v3-blue?style=flat-square) ![Coverage](https://img.shields.io/badge/coverage-85%25-yellowgreen?style=flat-square)

## Text Management And Extended Editor (known as Txtmax)

Txtmax is a modern, powerful, lightweight, fast, completely free, open-source advanced text editor designed for Linux. It features syntax highlighting and various file management capabilities. This program allows you to create, view, edit, delete, and get information about text files and more from the command line with ease.

## Features

- **Create Files:** Create new text files and save them locally.
- **View Files:** View the contents of text files with syntax highlighting for keywords, strings, and comments.
- **Edit Files:** Edit specific lines in existing text files.
- **List Files:** List all regular files in the current directory.
- **Delete Files:** Delete specified text files.
- **Search Files:** Search for files by name.
- **Get File Info:** Retrieve detailed information about a file, including its name, extension, creation time, modification time, and version control.
- **Line Numbering and Jumping to Specific line**
- **Search and Replace**
- **Compiling and Running Code**
- **Move Multiple Files to a Folder**
- **Copy Multiple Files to an Folder**
- **Pattern-Matching AI for Helping Users use Txtmax**
- **Rename an File**
- **Test and Fetch Data's of Restful APIs**
- **Debug and Warn C Files**
- **Built-in Terminal**
- **Edit Latex Files**
- **Convert Files to Tarball**
- **Package and Dependencies Management**
- **Build and Test a Project with make**
- **Build and Test a Java Project with Gradle**
- **Automation**
- **Support for .NET Framework**
- **Run Flask and Python App on Web Server**
- **Robust Error Handling:** Better error handling.
- **Robust Git Integration:** Supports Git branch, version, commit, and version tracking.

## Commands

- **help:** List all available commands.
- **man txtmax:** Comprehensive manual.
- **create <filename>:** Create a new file and type code in 80 languages, save and quit with :wq, type a commit message, branch, and version, and save it locally.
- **man txtmax**: comprehensive manual
- **rename**: Rename an file
- **movef**: Move Multiple Files to an Folder
- **copy**: Copy Multiple Files to an Folder
- **files:** List all files in the current directory.
- **view <filename>:** View the contents of a file with syntax highlighting.
- **edit <filename> <line>:** Edit a specific line in the file.
- **delete <filename>:** Delete a specified file.
- **search <filename>:** Search for files with the specified name.
- **info <filename>:** Get detailed information about the file (name, extension, creation time, modification time, version control such as commit message, branch, version).
- **examples:** Show examples of "Hello, World!" programs in C, Python, Java, JavaScript, C++, Rust, Ruby, Elixir, Kotlin, TypeScript, Dart, Objective-C, Go, etc.
- **sql:** Show example queries for SQL databases such as SQL, PostgreSQL, NoSQL (MongoDB).
- **run:** Run your code quickly without exiting Txtmax with compilers and interpreters such as GCC, Clang, g++, Python, Lua, Ruby, nasm, tcl, Node. First, it will ask for the file name and extension, then the compiler name, and it will run it.
- **packages:** Install Packages. First, it will ask which package manager to choose (pip or npm or gem or go or yarn or composer or cargo or nuget or apt), then type the package name, and it will install it. (Must have Python and Node.js and the others installed installed already)
- **api**: Test Restful APIs Data Directly in the Editor, First will ask for putting url and it will fetch data via curl
- **axios**: Another Command allows to Fetch Restful APIs Data From their Url, First it will ask for filename and then allows to write codes and quit with :wq and it will run it
- **advance**: type an file name with it's extension, it will show it's content and allows to jump into an specific line in it and Search and Replace
- **debug**: Get Debug And Warns for C Files, first will ask for debugging code or running code, if choose debugging code it will ask for project name and then filename including it's extension and then you can see debug, of choose warning it will ask for project name and then filename including it's extension and then it will run it
- **latex**: Edit Latex Files
- **dotnet**: Supports .NET Framework, it's first will ask for choosing an .NET Components (Currently Supprots .NET Sdk and ASP.NET) and then will ask for an Filename including it's extension and then it will ask for contents and then exit with :wq and then it will run the code, for using nuget you can use packages command (must install .net already)
- **tarball**: Convert your files to Tarball 
- **terminal**: A Built-in Terminal to type commands directly on the editor
- **localhost**: Start your Python and Flask App on web server, It will prompt for choosing flask or pythonhttp and then it will prompt for filename including it's extension and it will run it on localhost:8080 
- **recycle**: Recover your all deleted files, It will show list of all deleted files and you can type "recover <filename>.<extension> to recover it
- **exit:** Exit the Txtmax editor.

## Automation

We Introduced an Automation Feature to Automate Your Task 

**Commands**:
- **make**: Build and Test a project with make, first will ask for project name and filename including it's extension and Txtmax will generate an code and run it
- **gradle**: Build and test a Java Project with Gradle, First will ask for necessary inputs and then will generate an code based on inputs and run it

## AI

We Introduced an Pattern-Matching AI to help users use Txtmax Better it's had many Predefined Questions 

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

## UI

Terminal-based, very feature-rich, user-friendly, and lightweight. It will show "~/txtmax" as a prompt and allows writing commands.

## Syntax Highlighting

Txtmax uses ANSI colors for syntax highlighting to enhance readability. The following colors are used:

- **Keywords:** Green
- **Strings:** Blue
- **Comments:** Yellow

## Installation and Usage

To get started with Txtmax, follow these steps:

1. **Install:** Install it by running:
```bash
git clone https://github.com/Calestial2/Txtmax 
cd Txtmax
cd src
gcc txtmax.c -o txtmax
./txtmax
```

2. **Makefile**: You can use Makefile:
```bash
git clone https://github.com/Calestial2/Txtmax
cd Txtmax
cd src
make
make clean
./txtmax
```

## OS Compatibility 

Available on Linux and Unix-like systems (macOS and BSD) 🐧🐧🐧. For Other OS use Emulators like WSL 

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

## Supported Languages

Supports Many Popular Programming Language (Low Level and High Level of such many categories) and many Functional Languages and Many Old Languages that are still used today and Game Engine Language and Educational Languages and Many Rare Less common language 

Supports:

1. C
2. Python
3. Java
4. JavaScript (JS)
5. C++
6. Rust
7. Ruby
8. Elixir
9. Kotlin
10. Swift
11. TypeScript
12. Dart
13. Go
14. Haskell
15. R
16. PHP
17. Lua
18. Objective-C (ObjC)
19. Groovy
20. Erlang
21. Bash
22. Julia
23. F# (F-sharp)
24. C# (C-sharp)
25. Scheme
26. Clojure
27. Fortran
28. COBOL
29. VHDL
30. Lisp
31. SQL
32. MATLAB
33. Perl
34. Scala
35. HTML
36. PostgreSQL
37. NoSQL
38. ActionScript
39. Ada
40. Nim
41. Crystal
42. D
43. PureScript
44. Assembly
45. Prolog
46. Zig
47. Brainfuck
48. Algol
49. LabVIEW
50. Mercury
51. Shellscript 
52. OCaml
53. TXL
54. Xojo
55. Forth
56. Verilog
57. AWK
58. Turing
59. GDScript
60. Fantom
61. Zsh
62. AutoHotKey
63. Ceylon
64. ChucK
65. Natural
66. Pike
67. Oberon
68. XML
69. Yaml
70. JSON 
71. Visual Basic 
72. HTML5 
73. CSS 
74. Babel 
75. Sass 
76. Babel 
77. SAS 
78. Pl SQL 
79. Graphql 
80. SQLite 

## Libraries

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <regex.h>
#include <fcntl.h>
#include <unistd.h>
```

## Txtmax Source Code Files

- **README.md**: The README file
- **LICENSE.md**: The License file (GNU General Public License)
- **src/txtmax.c**: The source code of Txtmax
- **Makefile**: Makefile to automate the process
- **CHANGELOG.md**: Document detailing changes
- **CONTRIBUTING.md**: Comprehensive guidelines for contributing to Txtmax

When we Release an Update we keep updating it until another version 

We Recommend You use Latest Version always

## Why Choose Txtmax?

- **Comprehensive File Management:** Txtmax offers comprehensive file management, including creating, listing, viewing, searching files, deleting, and editing files and jumping to specific lines and Search And Replace.
- **Version Control and Git Integration:** Supports robust Git integration and robust error handling for every command.
- **Open Source and Free:** Fully open source and completely free (no hidden costs) under the GNU General Public License.
- **Syntax Highlighting and Multi-Language Support:** Supports over 80 languages with extensive syntax highlighting.
- **Compiling and Running Code:** Compile and run C, Python, JavaScript codes with compilers and interpreters such as GCC, Clang, Python, Node, Nasm, Tcl, Bash. without leaving Txtmax.
- **Package and Dependency Management:** Install packages directly from the editor easily.
- **Rich Documentation:** Detailed help and comprehensive manual for beginners and Had Examples of Hello world for various languages to get started 
- **Extremely Fast and Easy to Use:** Faster than GNU Nano and Vim, and very easy to use with commands that are easy to understand and use, offering a lower learning curve.
- **Terminal Integration**: Supports typing Terminal Commands in the Editor
- **Frequent Major Updates:** Frequent new major updates
