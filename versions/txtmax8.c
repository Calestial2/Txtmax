#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

#define MAX_INPUT_SIZE 256
#define MAX_CONTENT 1024

// ANSI Colors for Syntax Highlighting
#define COLOR_RESET "\033[0m"
#define COLOR_KEYWORD "\033[1;32m"
#define COLOR_STRING "\033[1;34m"
#define COLOR_COMMENT "\033[1;33m"
#define COLOR_NUMBER "\033[1;31m"
#define COLOR_FUNCTION "\033[1;36m"

const char *keywords_c[] = {"int", "return", "if", "else", "while", "for", "void", "char", "include", "define", NULL};
const char *keywords_python[] = {"def", "return", "if", "else", "while", "for", "import", "in", "from", "print", "class", NULL};
const char *keywords_java[] = {"public", "private", "protected", "class", "static", "void", "new", "return", "if", "else", "while", "for", "import", NULL};
const char *keywords_js[] = {"function", "var", "let", "const", "if", "else", "while", "for", "return", "class", "import", "export", NULL};
const char *keywords_cpp[] = {"int", "return", "if", "else", "while", "for", "void", "class", "include", "define", "public", "private", "protected", NULL};
const char *keywords_rust[] = {"fn", "let", "mut", "struct", "impl", "pub", "mod", "use", "return", "if", "else", "while", "for", NULL};
const char *keywords_ruby[] = {"def", "end", "if", "else", "elsif", "while", "for", "class", "module", "require", "return", NULL};
const char *keywords_elixir[] = {"def", "end", "if", "else", "do", "case", "defmodule", "import", "super", "IO", NULL};
const char *keywords_kotlin[] = {"fun", "val", "var", "return", "if", "else", "while", "for", "class", "object", "interface", "import", NULL};
const char *keywords_swift[] = {"func", "let", "var", "if", "else", "while", "for", "return", "class", "import", "struct", NULL};
const char *keywords_typescript[] = {"function", "let", "const", "if", "else", "while", "for", "return", "class", "interface", "import", "export", NULL};
const char *keywords_dart[] = {"void", "return", "if", "else", "while", "for", "class", "import", "int", "double", "String", NULL};
const char *keywords_go[] = {"func", "package", "import", "var", "const", "if", "else", "for", "return", "int", "float64", "string", NULL};
const char *keywords_haskell[] = {"import", "let", "in", "if", "then", "else", "data", "type", "class", "instance", "do", NULL};
const char *keywords_r[] = {"if", "else", "for", "while", "return", "function", "TRUE", "FALSE", "NULL", "library", "require", NULL};
const char *keywords_php[] = {"<?php", "echo", "if", "else", "for", "while", "function", "return", "class", "public", "private", "require", "include", NULL};
const char *keywords_lua[] = {"local", "function", "if", "else", "for", "while", "return", "end", "require", "print", NULL};
const char *keywords_objc[] = {"@interface", "@implementation", "if", "else", "return", "int", "char", "void", "NSString", "NSLog", "while", "for", "id", NULL};
const char *keywords_groovy[] = {"def", "if", "else", "for", "while", "return", "class", "package", "public", "private", "static", NULL};
const char *keywords_erlang[] = {"module", "export", "import", "if", "case", "receive", "fun", "end", "apply", "spawn", "node", "catch", NULL};
const char *keywords_bash[] = {"if", "then", "else", "elif", "fi", "for", "while", "until", "do", "done", "function", "return", NULL};
const char *keywords_julia[] = {"function", "end", "if", "else", "elseif", "for", "while", "return", "begin", "mutable", "const", "global", NULL};
const char *keywords_fsharp[] = {"let", "in", "if", "then", "else", "match", "return", "type", "new", "abstract", "class", "module", NULL};
const char *keywords_csharp[] = {"namespace", "class", "public", "private", "protected", "static", "void", "int", "return", "if", "else", "for", "while", NULL};
const char *keywords_scheme[] = {"define", "lambda", "if", "else", "cond", "begin", "quote", "set!", "let", "define-macro", NULL};
const char *keywords_clojure[] = {"def", "let", "if", "do", "fn", "defn", "quote", "case", "map", "reduce", "filter", "defmulti", NULL};
const char *keywords_fortran[] = {"program", "end", "if", "else", "do", "return", "function", "subroutine", "type", "integer", "real", "character", NULL};
const char *keywords_cobol[] = {"IDENTIFICATION", "PROGRAM", "DIVISION", "DATA", "SECTION", "PROCEDURE", "IF", "ELSE", "END-IF", "DISPLAY", "MOVE", "ACCEPT", NULL};
const char *keywords_vhdl[] = {"architecture", "entity", "if", "else", "process", "begin", "end", "signal", "variable", "constant", "port", "procedure", NULL};
const char *keywords_lisp[] = {"defun", "if", "else", "cond", "lambda", "let", "setq", "setq", "defvar", "loop", NULL};
const char *keywords_sql[] = {"SELECT", "FROM", "WHERE", "INSERT", "UPDATE", "DELETE", "CREATE", "DROP", "ALTER", "JOIN", "INNER", "OUTER", "GROUP BY", "ORDER BY", "LIMIT", "HAVING", "AND", "OR", "NOT", "NULL", "IS", "IN", "BETWEEN", "LIKE", "DISTINCT", "UNION", NULL};
const char *keywords_matlab[] = {"if", "else", "elseif", "for", "while", "end", "return", "function", "switch", "case", "otherwise", "try", "catch", "global", "persistent", "import", "clear", "clc", "disp", "fprintf", NULL};
const char *keywords_perl[] = {"sub", "if", "else", "elsif", "foreach", "while", "return", "my", "use", "require", "package", "print", "chomp", "open", "close", "exit", "die", "qw", "eval", "BEGIN", "END", NULL};
const char *keywords_scala[] = {"def", "val", "var", "class", "object", "trait", "import", "package", "extends", "with", "return", "if", "else", "match", NULL};
const char *keywords_html[] = {"html", "head", "body", "title", "div", "span", "p", "a", "img", "script", "link", "style", "table", "ul", "ol", "li", "input", "form", NULL};
const char *keywords_postgresql[] = {"SELECT", "INSERT", "UPDATE", "DELETE", "CREATE", "DROP", "ALTER", "GRANT", "REVOKE", "WHERE", "FROM", "JOIN", "HAVING", "GROUP BY", "ORDER BY", "DISTINCT", "LIMIT", "RETURNING", "CAST", "TABLE", "SCHEMA", NULL};
const char *keywords_nosql[] = {"db", "find", "insert", "update", "delete", "aggregate", "match", "group", "sort", "limit", "projection", "collection", NULL};
const char *keywords_actionscript[] = {"function", "var", "const", "if", "else", "while", "for", "return", "class", "public", "private", "import", "package", "extends", "implements", NULL};

// Function to check if a word is a keyword
int is_keyword(const char *word, const char **keywords) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Syntax Highlighting Function
void syntax_highlight(const char *line, const char *extension) {
    char buffer[MAX_INPUT_SIZE];
    int idx = 0;
    int in_string = 0, in_comment = 0;

const char **keywords;

// Match file extension to keywords
if (strcmp(extension, ".py") == 0) {
    keywords = keywords_python;
} else if (strcmp(extension, ".java") == 0) {
    keywords = keywords_java;
} else if (strcmp(extension, ".js") == 0) {
    keywords = keywords_js;
} else if (strcmp(extension, ".cpp") == 0 || strcmp(extension, ".cc") == 0) {
    keywords = keywords_cpp;
} else if (strcmp(extension, ".rs") == 0) {
    keywords = keywords_rust;
} else if (strcmp(extension, ".rb") == 0) {
    keywords = keywords_ruby;
} else if (strcmp(extension, ".ex") == 0 || strcmp(extension, ".exs") == 0) {
    keywords = keywords_elixir;
} else if (strcmp(extension, ".kt") == 0) {
    keywords = keywords_kotlin;
} else if (strcmp(extension, ".swift") == 0) {
    keywords = keywords_swift;
} else if (strcmp(extension, ".ts") == 0) {
    keywords = keywords_typescript;
} else if (strcmp(extension, ".dart") == 0) {
    keywords = keywords_dart;
} else if (strcmp(extension, ".go") == 0) {
    keywords = keywords_go;
} else if (strcmp(extension, ".hs") == 0) {
    keywords = keywords_haskell;
} else if (strcmp(extension, ".r") == 0) {
    keywords = keywords_r;
} else if (strcmp(extension, ".php") == 0) {
    keywords = keywords_php;
} else if (strcmp(extension, ".lua") == 0) {
    keywords = keywords_lua;
} else if (strcmp(extension, ".m") == 0 || strcmp(extension, ".h") == 0) {
    keywords = keywords_objc;
} else if (strcmp(extension, ".groovy") == 0) {
    keywords = keywords_groovy;
} else if (strcmp(extension, ".sql") == 0) {
    keywords = keywords_sql;
} else if (strcmp(extension, ".m") == 0) {
    keywords = keywords_matlab;
} else if (strcmp(extension, ".pl") == 0) {
    keywords = keywords_perl;
} else if (strcmp(extension, ".scala") == 0) {
    keywords = keywords_scala;
} else if (strcmp(extension, ".html") == 0) {
    keywords = keywords_html;
} else if (strcmp(extension, ".psql") == 0 || strcmp(extension, ".pgsql") == 0) {
    keywords = keywords_postgresql;
} else if (strcmp(extension, ".nosql") == 0) {
    keywords = keywords_nosql;
} else if (strcmp(extension, ".as") == 0) {
    keywords = keywords_actionscript;
} else {
    keywords = keywords_c; // Default to C
}

    for (int i = 0; line[i]; i++) {
        if (line[i] == '\"') {
            if (!in_comment) {
                in_string = !in_string;
                printf(COLOR_STRING "%c" COLOR_RESET, line[i]);
                continue;
            }
        } else if (line[i] == '/' && line[i + 1] == '/') {
            if (!in_string) {
                in_comment = 1;
                printf(COLOR_COMMENT "%s" COLOR_RESET, line + i);
                break;
            }
        }

        if (in_string || in_comment) {
            printf("%c", line[i]);
            continue;
        }

        if (isdigit(line[i])) {
            printf(COLOR_NUMBER "%c" COLOR_RESET, line[i]);
            continue;
        }

        if (isalnum(line[i]) || line[i] == '_') {
            buffer[idx++] = line[i];
        } else {
            if (idx > 0) {
                buffer[idx] = '\0';
                if (is_keyword(buffer, keywords))
                    printf(COLOR_KEYWORD "%s" COLOR_RESET, buffer);
                else
                    printf("%s", buffer);
                idx = 0;
            }
            printf("%c", line[i]);
        }
    }
    if (idx > 0) {
        buffer[idx] = '\0';
        if (is_keyword(buffer, keywords))
            printf(COLOR_KEYWORD "%s" COLOR_RESET, buffer);
        else
            printf("%s", buffer);
    }
}

// Improved Git Integration with better error handling
void git_commit(const char *filename, const char *commit_message, const char *branch, const char *version) {
    char command[MAX_INPUT_SIZE];

    // Initialize Git repository if not already initialized
    if (system("git rev-parse --is-inside-work-tree > /dev/null 2>&1") != 0) {
        if (system("git init") != 0) {
            printf("Error initializing Git repository.\n");
            return;
        }
    }

    // Add file to Git
    snprintf(command, sizeof(command), "git add %s", filename);
    if (system(command) != 0) {
        printf("Error adding file to Git.\n");
        return;
    }

    // Commit with message
    snprintf(command, sizeof(command), "git commit -m \"%s\"", commit_message);
    if (system(command) != 0) {
        printf("Error committing file to Git.\n");
        return;
    }

    // Create or checkout to the specified branch
    snprintf(command, sizeof(command), "git checkout -b %s", branch);
    if (system(command) != 0) {
        snprintf(command, sizeof(command), "git checkout %s", branch);
        if (system(command) != 0) {
            printf("Error checking out branch '%s'.\n", branch);
            return;
        }
    }

    // Tag the commit with the version
    snprintf(command, sizeof(command), "git tag %s", version);
    if (system(command) != 0) {
        printf("Error tagging commit with version '%s'.\n", version);
        return;
    }

    printf("File committed to branch '%s' with version '%s'.\n", branch, version);
}

// Command Handlers
void create_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error creating file");
        return;
    }
    printf("Enter content (type ':wq' to save and quit):\n");
    char line[MAX_INPUT_SIZE];
    while (1) {
        fgets(line, MAX_INPUT_SIZE, stdin);
        if (strcmp(line, ":wq\n") == 0)
            break;
        fprintf(file, "%s", line);
    }
    fclose(file);
    printf("File '%s' created and saved locally.\n", filename);

    // Git Integration
    char commit_message[MAX_INPUT_SIZE];
    char branch[MAX_INPUT_SIZE];
    char version[MAX_INPUT_SIZE];

    printf("Enter commit message: ");
    fgets(commit_message, sizeof(commit_message), stdin);
    commit_message[strcspn(commit_message, "\n")] = 0;

    printf("Enter branch name: ");
    fgets(branch, sizeof(branch), stdin);
    branch[strcspn(branch, "\n")] = 0;

    printf("Enter version (e.g., v1.0.0): ");
    fgets(version, sizeof(version), stdin);
    version[strcspn(version, "\n")] = 0;

    git_commit(filename, commit_message, branch, version);
}

void list_files() {
    struct dirent *entry;
    DIR *dir = opendir(".");
    if (!dir) {
        perror("Error opening directory");
        return;
    }
    printf("Files in the local directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) // Only list regular files
            printf("  %s\n", entry->d_name);
    }
    closedir(dir);
}

void view_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    const char *ext = strrchr(filename, '.');
    if (!ext) ext = "";  // Default to empty string if no extension

    char line[MAX_INPUT_SIZE];
    int line_number = 1;
    printf("Contents of '%s':\n", filename);
    while (fgets(line, sizeof(line), file)) {
        printf("%3d | ", line_number++);
        // Call the syntax_highlight function to highlight keywords and syntax
        syntax_highlight(line, ext);
    }
    fclose(file);
}

void edit_file(const char *filename, int line_to_edit) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Error opening file for editing");
        return;
    }

    char content[MAX_CONTENT][MAX_INPUT_SIZE];
    int total_lines = 0;

    while (fgets(content[total_lines], MAX_INPUT_SIZE, file)) {
        total_lines++;
    }

    if (line_to_edit < 1 || line_to_edit > total_lines) {
        printf("Invalid line number. The file has %d lines.\n", total_lines);
        fclose(file);
        return;
    }

    printf("Current line %d: %s", line_to_edit, content[line_to_edit - 1]);
    printf("Enter the new content for line %d: ", line_to_edit);
    fgets(content[line_to_edit - 1], MAX_INPUT_SIZE, stdin);

    freopen(filename, "w", file); // Reopen file in write mode to overwrite content
    for (int i = 0; i < total_lines; i++) {
        fputs(content[i], file);
    }

    fclose(file);
    printf("Line %d updated successfully in '%s'.\n", line_to_edit, filename);
}

void delete_file(const char *filename) {
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Error deleting file");
    }
}

void search_files(const char *filename) {
    struct dirent *entry;
    DIR *dir = opendir(".");
    if (!dir) {
        perror("Error opening directory");
        return;
    }

    printf("Searching for files with name '%s':\n", filename);
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && strstr(entry->d_name, filename)) {
            printf("  %s\n", entry->d_name);
        }
    }
    closedir(dir);
}

void file_info(const char *filename) {
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        perror("Error getting file information");
        return;
    }

    char time_created[64], time_modified[64];
    strftime(time_created, sizeof(time_created), "%Y-%m-%d %H:%M:%S", localtime(&file_stat.st_ctime));
    strftime(time_modified, sizeof(time_modified), "%Y-%m-%d %H:%M:%S", localtime(&file_stat.st_mtime));

    // Get Git information
    char branch[MAX_INPUT_SIZE];
    if (system("git rev-parse --abbrev-ref HEAD > temp.txt") == 0) {
        FILE *git_file = fopen("temp.txt", "r");
        fgets(branch, sizeof(branch), git_file);
        fclose(git_file);
        branch[strcspn(branch, "\n")] = 0;
    } else {
        strcpy(branch, "N/A");
    }

    // Get version information
    char version[MAX_INPUT_SIZE];
    if (system("git describe --tags > temp.txt") == 0) {
        FILE *git_file = fopen("temp.txt", "r");
        fgets(version, sizeof(version), git_file);
        fclose(git_file);
        version[strcspn(version, "\n")] = 0;
    } else {
        strcpy(version, "N/A");
    }

    const char *ext = strrchr(filename, '.');
    if (!ext) ext = "None";  // Default to "None" if no extension

    printf("File Info:\n");
    printf("  Name: %s\n", filename);
    printf("  Extension: %s\n", ext);
    printf("  Created: %s\n", time_created);
    printf("  Last Modified: %s\n", time_modified);
    printf("  Branch: %s\n", branch);
    printf("  Version: %s\n", version);
}

void help() {
    printf("Commands:\n");
    printf("  help                    Show this help message\n");
    printf("  create <filename>       Create a new file and save locally\n");
    printf("  files                   List all files in the current directory\n");
    printf("  search <filename>       Search for files with the specified name\n");
    printf("  view <filename>         View file contents with syntax highlighting\n");
    printf("  edit <filename> <line>  Edit a specific line in the file\n");
    printf("  delete <filename>       Delete a file\n");
    printf("  info <filename>         Show file info (name, extension, creation time, modification time)\n");
    printf("  examples                Show Hello World examples in various languages\n");
    printf("  sql                     Show SQL code examples\n");
    printf("  exit                    Exit txtmax\n");
}

void examples() {
    printf("Hello World Examples in Various Languages:\n");

    // C
    printf("C: \n");
    printf("  #include <stdio.h>\n  int main() {\n    printf(\"Hello, World!\\n\");\n    return 0;\n  }\n\n");

    // Python
    printf("Python:\n");
    printf("  print('Hello, World!')\n\n");

    // Java
    printf("Java:\n");
    printf("  public class Main {\n    public static void main(String[] args) {\n      System.out.println('Hello, World!');\n    }\n  }\n\n");

    // JavaScript
    printf("JavaScript:\n");
    printf("  console.log('Hello, World!');\n\n");

    // C++
    printf("C++:\n");
    printf("  #include <iostream>\n  int main() {\n    std::cout << 'Hello, World!' << std::endl;\n    return 0;\n  }\n\n");

    // Rust
    printf("Rust:\n");
    printf("  fn main() {\n    println!(\"Hello, World!\");\n  }\n\n");

    // Ruby
    printf("Ruby:\n");
    printf("  puts 'Hello, World!'\n\n");

    // Elixir
    printf("Elixir:\n");
    printf("  IO.puts 'Hello, World!'\n\n");

    // Kotlin
    printf("Kotlin:\n");
    printf("  fun main() {\n    println('Hello, World!')\n  }\n\n");

    // Swift
    printf("Swift:\n");
    printf("  print('Hello, World!')\n\n");

    // TypeScript
    printf("TypeScript:\n");
    printf("  console.log('Hello, World!');\n\n");

    // Dart
    printf("Dart:\n");
    printf("  void main() {\n    print('Hello, World!');\n  }\n\n");

    // Go
    printf("Go:\n");
    printf("  package main\n  import \"fmt\"\n  func main() {\n    fmt.Println(\"Hello, World!\")\n  }\n\n");

    // Haskell
    printf("Haskell:\n");
    printf("  main :: IO ()\n  main = putStrLn \"Hello, World!\"\n\n");

    // R
    printf("R:\n");
    printf("  print('Hello, World!')\n\n");

    // PHP
    printf("PHP:\n");
    printf("  <?php\n    echo 'Hello, World!';\n  ?>\n\n");

    // Lua
    printf("Lua:\n");
    printf("  print('Hello, World!')\n\n");

    // Objective-C
    printf("Objective-C:\n");
    printf("  #import <Foundation/Foundation.h>\n\n");
    printf("  int main() {\n");
    printf("    @autoreleasepool {\n");
    printf("      NSLog(@\"Hello, World!\");\n");
    printf("    }\n");
    printf("    return 0;\n");
    printf("  }\n\n");

    // Groovy
    printf("Groovy:\n");
    printf("  println 'Hello, World!'\n\n");
}

void sql_examples() {
    printf("SQL Examples:\n");

    // SQL - Basic Query
    printf("Basic SQL Query:\n");
    printf("  SELECT * FROM users WHERE age > 30;\n\n");

    // PostgreSQL
    printf("PostgreSQL Example:\n");
    printf("  SELECT name, age FROM employees WHERE department = 'Sales';\n\n");

    // NoSQL Example (MongoDB)
    printf("NoSQL (MongoDB) Example:\n");
    printf("  db.users.find({ age: { $gt: 30 } });\n\n");
}

int main() {
    char command[MAX_INPUT_SIZE];
    printf("Welcome to txtmax! Type 'help' for a list of commands.\n");

    while (1) {
        printf("\n~/txtmax ");
        fgets(command, MAX_INPUT_SIZE, stdin);
        command[strcspn(command, "\n")] = 0;  // Remove the newline at the end of input

        if (strcmp(command, "help") == 0) {
            help();
        } else if (strncmp(command, "create", 6) == 0) {
            char filename[MAX_INPUT_SIZE];
            sscanf(command + 7, "%s", filename);
            create_file(filename);
        } else if (strcmp(command, "files") == 0) {
            list_files();
        } else if (strncmp(command, "search", 6) == 0) {
            char filename[MAX_INPUT_SIZE];
            sscanf(command + 7, "%s", filename);
            search_files(filename);
        } else if (strncmp(command, "view", 4) == 0) {
            char filename[MAX_INPUT_SIZE];
            sscanf(command + 5, "%s", filename);
            view_file(filename);
        } else if (strncmp(command, "edit", 4) == 0) {
            char filename[MAX_INPUT_SIZE];
            int line_to_edit;
            sscanf(command + 5, "%s %d", filename, &line_to_edit);
            edit_file(filename, line_to_edit);
        } else if (strncmp(command, "delete", 6) == 0) {
            char filename[MAX_INPUT_SIZE];
            sscanf(command + 7, "%s", filename);
            delete_file(filename);
        } else if (strncmp(command, "info", 4) == 0) {
            char filename[MAX_INPUT_SIZE];
            sscanf(command + 5, "%s", filename);
            file_info(filename);
        } else if (strcmp(command, "examples") == 0) {
            examples();
        } else if (strcmp(command, "sql") == 0) {
            sql_examples();
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting txtmax...\n");
            break;
        } else {
            printf("Unknown command: %s\n", command);
        }
    }

    return 0;
}
