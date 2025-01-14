![Image](https://github.com/Calestial2/Txtmax/blob/f7a65e499d29e184e6d06263250e8f16b753b5ba/ascii-text-art.png)
          
[![Typing SVG](https://readme-typing-svg.demolab.com?font=Fira+Code&pause=1000&color=F7992D&background=FF8C1100&width=435&lines=++++++++++++++++++++++++++++++++++Txtmax;Linux+Text-based+Editor)](https://git.io/typing-svg)
## Text Management And Extended Editor (Txtmax)
Txtmax is a powerful, lightweight, fast, completely free, open-source advanced text editor designed for Linux Built from Termux. It features syntax highlighting and various file management capabilities. This program allows you to create, view, edit, delete, and get information about text files and jumping to line and searching spectic line from the command line with ease.

**Programming Language:** C (main) (100% code is in C)  
**Developer:** Calestial Ashley  
**Nature:** Fully and completely open source  
**Contact:** Contact at calestialashley@gmail.com, or friend Calestial Ashley (username: calestial_ashley) on Discord and DM  
**Release Date:** January 2, 2025 (12 days old)  
**Size:** 44 KB (It's weird because the code is too long but it’s small in size due to many libraries)  
**Lines of Code:** 1044

## Features

- **Create Files:** Create new text files and save them locally.
- **View Files:** View the contents of text files with syntax highlighting for keywords, strings, and comments.
- **Edit Files:** Edit specific lines in existing text files.
- **List Files:** List all regular files in the current directory.
- **Delete Files:** Delete specified text files.
- **Search Files:** Search for files by name.
- **Get File Info:** Retrieve detailed information about a file, including its name, extension, creation time, modification time, and version control.
- **Robust Error Handling:** Better error handling.
- **Robust Git Integration:** Supports Git branch, version, commit, and version tracking.

## Commands

- **help:** List all available commands.
- **man txtmax:** Comprehensive manual.
- **create <filename>:** Create a new file and type code in 60+ languages, save and quit with :wq, provide a commit message, branch, and version, and save it locally.
- **files:** List all files in the current directory.
- **view <filename>:** View the contents of a file with syntax highlighting.
- **edit <filename> <line>:** Edit a specific line in the file.
- **delete <filename>:** Delete a specified file.
- **search <filename>:** Search for files with the specified name.
- **info <filename>:** Get detailed information about the file (name, extension, creation time, modification time, version control such as commit message, branch, version).
- **examples:** Show examples of "Hello, World!" programs in C, Python, Java, JavaScript, C++, Rust, Ruby, Elixir, Kotlin, TypeScript, Dart, Objective-C, Go, etc.
- **sql:** Show example queries for SQL databases such as SQL, PostgreSQL, NoSQL (MongoDB).
- **run:** Run your code quickly without exiting Txtmax with compilers and interpreters such as GCC, Clang, Python, Node. First, it will ask for the file name and extension, then the compiler name, and it will run it.
- **packages:** Install pip and npm packages. First, it will ask which package manager to choose (pip or npm), then type the package name, and it will install it. (Must have Python and Node.js installed already)
- **exit:** Exit the Txtmax editor.

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
git clone https://github.com/Calestial2/Txtmax cd Txtmax cd versions gcc gcc txtmax10.c -o txtmax10 ./txtmax10
```

## OS Compatibility 

Available on Linux and Unix-like systems (macOS and BSD) 🐧🐧🐧. Other OS:

- **Windows:** Run an emulator like WSL 🙃 (because dirent.h is not available by default)
- **Android:** Use Termux (works well on Termux because itself developed from Termux)

## Performance 

Extremely fast and lightweight, faster than GNU Nano and Vim because:

- C is fast in itself.
- It uses many standard libraries.

## License

This project is licensed under the GNU General Public License v3.0.
You are free to use, modify, and distribute this software under the terms of the license. See the LICENSE file for more information.

## Contributing

Contributions are welcome! Here's how you can help:

- Report bugs or request features using [GitHub Issues](https://github.com/Calestial2/Txtmax/issues)
- Submit pull requests with clear descriptions of changes.
- Ensure your code follows the style and design of the project.

## Supported Languages

Supports:

1. C
2. Python
3. Java
4. JavaScript
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
18. Objective-C
19. Groovy
20. Erlang
21. Bash
22. Julia
23. F#
24. C#
25. Scheme
26. Clojure
27. Fortran
28. Cobol
29. VHDL
30. Lisp
31. SQL
32. Matlab
33. Perl
34. Scala
35. PostgreSQL
36. NoSQL
37. ActionScript
38. Ada 
39. Nim
40. Crystal
41. D
42. Assembly Language 
43. PureScript 
44. Prolog 
45. Zig
46. Brainfuck
47. OCaml 
48. Txl
49. Xojo
50. Forth
51. Verilog 
52. Algol
53. LabVIEW 
54. Mercury 
55. Shellscript 
56. Turing
57. GDscript 
58. fantom 
59. Zsh 
60. Oberon 
61. Auto Hotkey
62. Ceylon 
63. ChucK 
64. natural 
65. Pike
 
### Markup Languages:
1. HTML

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
```

## Txtmax Source Code Files

The Txtmax text editor code is in the versions folder.

In the versions folder, there are files such as:

- **txtmax1.c:** The first version of Txtmax (0.0.1)
- **txtmax2.c:** The second version of Txtmax (0.0.2)
- **txtmax3.c:** The third version of Txtmax (0.0.3)
- **txtmax4.c:** Skipped
- **txtmax5.c:** The fifth version of Txtmax (0.0.5)
- **txtmax6.c:** The sixth version of Txtmax (0.0.6) 
- **txtmax7.c:** The seventh version of Txtmax (0.0.7) 
- **txtmax8.c:** The eighth version of Txtmax (0.0.8)
- **txtmax9.c:** The ninth version of Txtmax (0.0.9)
- **txtmax10.c:** The tenth and Latest Version of Txtmax (0.1.0)

## Why Choose Txtmax?

- **Comprehensive File Management:** Txtmax offers comprehensive file management, including creating, listing, viewing, searching, deleting, and editing files.
- **Version Control and Git Integration:** Supports robust Git integration and error handling for every command.
- **Open Source and Free:** Fully open source and completely free (no hidden costs) under the GNU General Public License.
- **Syntax Highlighting and Multi-Language Support:** Supports 50+ languages with extensive syntax highlighting.
- **Compiling and Running Code:** Compile and run C, Python, JavaScript codes with compilers and interpreters such as GCC, Clang, Python, Node without leaving Txtmax.
- **Package and Dependency Management:** Install packages directly from the editor easily.
- **Rich Documentation:** Detailed help and comprehensive manual for beginners.
- **Extremely Fast and Easy to Use:** Faster than GNU Nano and Vim, and very easy to use with commands that are easy to understand and use, offering a lower learning curve.
- **Frequent Major Updates:** Frequent new major updates 

 ## Reviews 

We're Having Very Good Positive Reviews by our users. So what are you waiting for? use the 5-star tool now 🔥
