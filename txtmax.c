#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <regex.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 256
#define MAX_CONTENT 1024
#define MAX_URL_LENGTH 2048
#define MAX_LINE_LENGTH 1024
#define MAX_FILENAME_LENGTH 256
#define MAX_CONTENT_LENGTH 1024
#define MAX_INPUT_SIZE 256
#define MAX_FILENAME 256
#define MAX_LINE 1024

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
const char *keywords_ada[] = {"procedure", "function", "if", "else", "begin", "end", "loop", "return", "declare", "type", "private", "public", NULL};
const char *keywords_nim[] = {"proc", "var", "const", "if", "else", "for", "while", "return", "type", "import", NULL};
const char *keywords_crystal[] = {"def", "return", "if", "else", "elsif", "for", "while", "class", "module", "private", "public", NULL};
const char *keywords_d[] = {"void", "int", "if", "else", "for", "while", "return", "class", "struct", "import", "alias", NULL};
const char *keywords_purescript[] = {"let", "if", "else", "case", "of", "data", "type", "import", "foreign", "module", "instance", NULL};
const char *keywords_assembly[] = {"mov", "add", "sub", "jmp", "cmp", "je", "jne", "call", "ret", "push", "pop", NULL};
const char *keywords_prolog[] = {":-", "if", "else", "end", "assert", "fail", "true", "false", "query", "fact", NULL};
const char *keywords_zig[] = {"const", "var", "fn", "return", "if", "else", "while", "for", "try", "catch", "defer", NULL};
const char *keywords_brainfuck[] = {">", "<", "+", "-", ".", ",", "[", "]", NULL};
const char *keywords_algol[] = {"begin", "end", "if", "then", "else", "for", "while", "procedure", "function", "integer", "real", "boolean", "array", NULL};
const char *keywords_labview[] = {"while", "for", "if", "case", "end", "else", "true", "false", "break", "continue", "function", "subVI", NULL};
const char *keywords_mercury[] = {"module", "end_module", "import", "type", "func", "pred", "if", "then", "else", "true", "false", "forall", NULL};
const char *keywords_dart_shell[] = {"#!/bin/bash", "echo", "if", "then", "else", "fi", "for", "while", "return", "function", "export", NULL};
const char *keywords_ocaml[] = {"let", "in", "if", "then", "else", "match", "with", "type", "module", "open", "rec", "and", "fun", NULL};
const char *keywords_txl[] = {"def", "if", "then", "else", "while", "for", "return", "class", "module", "type", "eval", NULL};
const char *keywords_xojo[] = {"dim", "if", "then", "else", "for", "while", "return", "function", "class", "end", "public", "private", NULL};
const char *keywords_forth[] = {"if", "else", "then", "begin", "again", "loop", "do", "while", "return", "create", "colon", "exit", NULL};
const char *keywords_verilog[] = {"module", "endmodule", "input", "output", "wire", "assign", "always", "if", "else", "begin", "end", "for", NULL};
const char *keywords_awk[] = {"BEGIN", "END", "if", "else", "while", "for", "print", "next", "return", "function", "match", "split", NULL};
const char *keywords_turing[] = {"put", "get", "var", "if", "then", "else", "elsif", "loop", "exit", "procedure", "function", "return", "end", NULL};
const char *keywords_gdscript[] = {"func", "if", "elif", "else", "for", "while", "match", "extends", "var", "const", "tool", "class_name", "return", NULL};
const char *keywords_fantom[] = {"class", "mixins", "const", "type", "static", "abstract", "new", "return", "if", "else", "while", "for", "using", "func", NULL};
const char *keywords_zsh[] = {"if", "then", "else", "fi", "for", "while", "do", "done", "case", "esac", "function", "return", "echo", "export", NULL};
const char *keywords_autohotkey[] = {"if", "else", "loop", "return", "send", "set", "global", "local", "exit", "msgbox", "run", "hotkey", "while", NULL};
const char *keywords_ceylon[] = {"module", "import", "class", "object", "interface", "function", "value", "variable", "if", "else", "return", "for", "while", "switch", "case", NULL};
const char *keywords_chuck[] = {"if", "else", "for", "while", "until", "spork", "class", "fun", "return", "gain", "dur", "time", "void", NULL};
const char *keywords_natural[] = {"DEFINE", "IF", "THEN", "ELSE", "END-DEFINE", "READ", "WRITE", "DISPLAY", "MOVE", "ADD", "DELETE", "RETURN", NULL};
const char *keywords_pike[] = {"int", "float", "string", "if", "else", "while", "for", "return", "function", "class", "inherit", "void", NULL};
const char *keywords_oberon[] = {"MODULE", "IMPORT", "BEGIN", "END", "IF", "THEN", "ELSE", "ELSIF", "WHILE", "DO", "PROCEDURE", "VAR", "CONST", "TYPE", "RECORD", "ARRAY", "OF", "RETURN", NULL};
const char *keywords_xml[] = {"<", "</", ">", "/>", "<?", "?>", "<!--", "-->", "<![CDATA[", "DOCTYPE", "ELEMENT", "ATTLIST", "ENTITY", NULL};
const char *keywords_yaml[] = {"-", ":", "?", "|", ">", "true", "false", "null", "~", ">", "|", "!!", "key", "value", NULL};
const char *keywords_json[] = {"{", "}", "[", "]", ":", ",", "true", "false", "null", "\"", "key", "value", NULL};
const char *keywords_vb[] = {"Dim", "If", "Then", "Else", "ElseIf", "End If", "For", "Each", "Next", "While", "Do", "Loop", "Sub", "Function", "End Sub", "End Function", "Return", "Class", "Public", "Private", "Protected", "Static", "New", "Set", "Get", "Property", "Module", "Imports", "Try", "Catch", "Finally", "Throw", "True", "False", "Nothing", "And", "Or", "Not", "Is", "As", NULL};
const char *keywords_html5[] = {"<!DOCTYPE", "<html>", "<head>", "<body>", "<title>", "<div>", "<span>", "<p>", "<a>", "<img>", "<script>", "<link>", "<style>", "<table>", "<ul>", "<ol>", "<li>", "<form>", "<input>", "<textarea>", "<button>", "<nav>", "<footer>", NULL};
const char *keywords_css[] = {"body", "div", "span", "p", "a", "h1", "h2", "h3", "h4", "h5", "h6", "width", "height", "margin", "padding", "border", "color", "font-size", "font-family", "display", "position", "flex", "grid", "background", "box-shadow", "text-align", "float", "clear", "overflow", "z-index", "transition", "transform", "media", NULL};
const char *keywords_sass[] = {"@import", "@mixin", "@include", "@extend", "@function", "@if", "@else", "@for", "@while", "$", "color", "font-size", "padding", "margin", "border", "background", "box-shadow", "display", "position", "flex", "grid", "text-align", "font-family", NULL};
const char *keywords_babel[] = {"import", "export", "function", "class", "let", "const", "var", "if", "else", "for", "while", "return", "async", "await", "promise", "new", "extends", "super", "constructor", "this", "super", "import.meta", NULL};
const char *keywords_sas[] = {"data", "set", "input", "datalines", "proc", "run", "if", "else", "then", "end", "var", "array", "retain", "format", "length", "merge", "sort", "by", "sum", "mean", "proc print", "proc freq", NULL};
const char *keywords_plsql[] = {"DECLARE", "BEGIN", "END", "IF", "ELSE", "ELSIF", "FOR", "LOOP", "WHILE", "CURSOR", "EXCEPTION", "SELECT", "INSERT", "UPDATE", "DELETE", "COMMIT", "ROLLBACK", "RETURN", "FUNCTION", "PROCEDURE", "TRIGGER", NULL};
const char *keywords_graphql[] = {"query", "mutation", "subscription", "type", "interface", "union", "input", "schema", "enum", "directive", "fragment", "extends", "implements", "resolve", "field", "scalar", "ID", "String", "Int", "Float", "Boolean", "List", NULL};
const char *keywords_sqlite[] = {"SELECT", "INSERT", "UPDATE", "DELETE", "FROM", "WHERE", "ORDER BY", "GROUP BY", "HAVING", "JOIN", "INNER", "LEFT", "RIGHT", "OUTER", "DISTINCT", "LIMIT", "OFFSET", "CREATE", "DROP", "ALTER", "TABLE", "INDEX", "VIEW", "TRANSACTION", "BEGIN", "COMMIT", "ROLLBACK", NULL};

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
} else if (strcmp(extension, ".matlab") == 0) {
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
} else if (strcmp(extension, ".ada") == 0) {
    keywords = keywords_ada;
} else if (strcmp(extension, ".nim") == 0) {
    keywords = keywords_nim;
} else if (strcmp(extension, ".cr") == 0) {
    keywords = keywords_crystal;
} else if (strcmp(extension, ".d") == 0) {
    keywords = keywords_d;
} else if (strcmp(extension, ".purs") == 0) {
    keywords = keywords_purescript;
} else if (strcmp(extension, ".asm") == 0 || strcmp(extension, ".s") == 0) {
    keywords = keywords_assembly;
} else if (strcmp(extension, ".plg") == 0) {
    keywords = keywords_prolog;
} else if (strcmp(extension, ".zig") == 0) {
    keywords = keywords_zig;
} else if (strcmp(extension, ".bf") == 0) {
    keywords = keywords_brainfuck;
} else if (strcmp(extension, ".algol") == 0) {
    keywords = keywords_algol;
} else if (strcmp(extension, ".lv") == 0) {
    keywords = keywords_labview;
} else if (strcmp(extension, ".m") == 0) {
    keywords = keywords_mercury;
} else if (strcmp(extension, ".sh") == 0) {
    keywords = keywords_dart_shell;
} else if (strcmp(extension, ".ml") == 0) {
    keywords = keywords_ocaml;
} else if (strcmp(extension, ".txl") == 0) {
    keywords = keywords_txl;
} else if (strcmp(extension, ".xojo") == 0) {
    keywords = keywords_xojo;
} else if (strcmp(extension, ".4th") == 0) {
    keywords = keywords_forth;
} else if (strcmp(extension, ".v") == 0) {
    keywords = keywords_verilog;
} else if (strcmp(extension, ".awk") == 0) {
    keywords = keywords_awk;
} else if (strcmp(extension, ".gd") == 0) {
    keywords = keywords_gdscript;
} else if (strcmp(extension, ".fan") == 0) {
    keywords = keywords_fantom;
} else if (strcmp(extension, ".zsh") == 0) {
    keywords = keywords_zsh;
} else if (strcmp(extension, ".oberon") == 0) {
    keywords = keywords_oberon;
} else if (strcmp(extension, ".ahk") == 0) {
    keywords = keywords_autohotkey;
} else if (strcmp(extension, ".ceylon") == 0) {
    keywords = keywords_ceylon;
} else if (strcmp(extension, ".ck") == 0) {
    keywords = keywords_chuck;
} else if (strcmp(extension, ".natural") == 0) {
    keywords = keywords_natural;
} else if (strcmp(extension, ".pike") == 0) {
    keywords = keywords_pike;
} else if (strcmp(extension, ".xml") == 0) { // XML
    keywords = keywords_xml;
} else if (strcmp(extension, ".yaml") == 0 || strcmp(extension, ".yml") == 0) { // YAML
    keywords = keywords_yaml;
} else if (strcmp(extension, ".json") == 0) { // JSON
    keywords = keywords_json;
} else if (strcmp(extension, ".vb") == 0) { // JSON
    keywords = keywords_vb;
} else {
if (strcmp(extension, ".html5") == 0) { // HTML5
} else if (strcmp(extension, ".css") == 0) { // CSS
    keywords = keywords_css;
} else if (strcmp(extension, ".sass") == 0) { // SASS
    keywords = keywords_sass;
} else if (strcmp(extension, ".babel") == 0) { // Babel
    keywords = keywords_babel;
} else if (strcmp(extension, ".sas") == 0) { // SAS
    keywords = keywords_sas;
} else if (strcmp(extension, ".plsql") == 0) { // PL SQL
    keywords = keywords_plsql;
} else if (strcmp(extension, ".graphql") == 0) { // GraphQL
    keywords = keywords_graphql;
} else if (strcmp(extension, ".sqlite") == 0) { // SQLite
    keywords = keywords_sqlite;
}
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

// Function to convert input to lowercase for case-insensitive matching
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
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

void quick_run() {
    char filename[MAX_INPUT_SIZE];
    char compiler[MAX_INPUT_SIZE];
    char command[MAX_INPUT_SIZE];

    // Prompt for filename
    printf("Enter the file name with extension (e.g., program.c, script.py): ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove trailing newline

    // Check if the file exists
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error: File does not exist");
        return;
    }
    fclose(file);

    // Prompt for compiler/interpreter
    printf("Enter the compiler or interpreter (gcc, clang, python, node, nasm, tcl, bash): ");
    fgets(compiler, sizeof(compiler), stdin);
    compiler[strcspn(compiler, "\n")] = 0; // Remove trailing newline

    // Match compiler/interpreter and build the command
    const char *ext = strrchr(filename, '.'); // Get file extension
    if (!ext) {
        printf("Error: Unable to detect file extension.\n");
        return;
    }

    if (strcmp(compiler, "gcc") == 0 || strcmp(compiler, "clang") == 0) {
        if (strcmp(ext, ".c") == 0) {
            snprintf(command, sizeof(command), "%s %s -o output && ./output", compiler, filename);
        } else {
            printf("Error: %s is only compatible with C files.\n", compiler);
            return;
        }
    } else if (strcmp(compiler, "python") == 0) {
        if (strcmp(ext, ".py") == 0) {
            snprintf(command, sizeof(command), "python %s", filename);
        } else {
            printf("Error: Python is only compatible with .py files.\n");
            return;
        }
    } else if (strcmp(compiler, "node") == 0) {
        if (strcmp(ext, ".js") == 0) {
            snprintf(command, sizeof(command), "node %s", filename);
        } else {
            printf("Error: Node.js is only compatible with .js files.\n");
            return;
        }
    } else if (strcmp(compiler, "nasm") == 0) {
        if (strcmp(ext, ".asm") == 0) {
            snprintf(command, sizeof(command), "nasm -f elf64 %s -o output.o && gcc output.o -o output && ./output", filename);
        } else {
            printf("Error: NASM is only compatible with .asm files.\n");
            return;
        }
    } else if (strcmp(compiler, "tcl") == 0) {
        if (strcmp(ext, ".tcl") == 0) {
            snprintf(command, sizeof(command), "tclsh %s", filename);
        } else {
            printf("Error: TCL is only compatible with .tcl files.\n");
            return;
        }
    } else if (strcmp(compiler, "bash") == 0) {
        if (strcmp(ext, ".sh") == 0) {
            snprintf(command, sizeof(command), "bash %s", filename);
        } else {
            printf("Error: Bash is only compatible with .sh files.\n");
            return;
        }
    } else {
        printf("Error: Unsupported compiler or interpreter '%s'.\n", compiler);
        return;
    }

    // Execute the commandgfg
    printf("Running command: %s\n", command);
    if (system(command) != 0) {
        printf("Error: Failed to execute the command.\n");
    } else {
        printf("Execution completed successfully.\n");
    }
}

void packages() {
    char package_manager[MAX_INPUT_SIZE];
    char package_name[MAX_INPUT_SIZE];
    char command[MAX_INPUT_SIZE];

    printf("Enter package manager (pip/npm/gem/go/yarn/composer/cargo/nuget/apt): ");
    fgets(package_manager, sizeof(package_manager), stdin);
    package_manager[strcspn(package_manager, "\n")] = 0; // Remove trailing newline

    // Check for valid package manager
    if (strcmp(package_manager, "pip") != 0 &&
        strcmp(package_manager, "npm") != 0 &&
        strcmp(package_manager, "gem") != 0 &&
        strcmp(package_manager, "go") != 0 &&
        strcmp(package_manager, "yarn") != 0 &&
        strcmp(package_manager, "composer") != 0 &&
        strcmp(package_manager, "cargo") != 0 &&
        strcmp(package_manager, "nuget") != 0 &&
        strcmp(package_manager, "apt") != 0) {
        printf("Error: Unsupported package manager '%s'.\n", package_manager);
        return;
    }

    printf("Enter package name: ");
    fgets(package_name, sizeof(package_name), stdin);
    package_name[strcspn(package_name, "\n")] = 0; // Remove trailing newline

    // Construct the installation command based on the package manager
    if (strcmp(package_manager, "pip") == 0) {
        snprintf(command, sizeof(command), "pip install %s", package_name);
    } else if (strcmp(package_manager, "npm") == 0) {
        snprintf(command, sizeof(command), "npm install %s", package_name);
    } else if (strcmp(package_manager, "gem") == 0) {
        snprintf(command, sizeof(command), "gem install %s", package_name);
    } else if (strcmp(package_manager, "go") == 0) {
        snprintf(command, sizeof(command), "go install %s@latest", package_name);
    } else if (strcmp(package_manager, "yarn") == 0) {
        snprintf(command, sizeof(command), "yarn add %s", package_name);
    } else if (strcmp(package_manager, "composer") == 0) {
        snprintf(command, sizeof(command), "composer require %s", package_name);
    } else if (strcmp(package_manager, "cargo") == 0) {
        snprintf(command, sizeof(command), "cargo install %s", package_name);
    } else if (strcmp(package_manager, "nuget") == 0) {
        snprintf(command, sizeof(command), "nuget install %s", package_name);
    } else if (strcmp(package_manager, "apt") == 0) {
        snprintf(command, sizeof(command), "sudo apt-get install %s", package_name);
    }

    // Execute the installation command
    printf("Running command: %s\n", command);
    if (system(command) != 0) {
        printf("Error: Failed to install the package '%s' using %s.\n", package_name, package_manager);
    } else {
        printf("Package '%s' installed successfully using %s.\n", package_name, package_manager);
    }
}

void api() {
    char url[MAX_URL_LENGTH];
    char command[MAX_URL_LENGTH + 10]; // To accommodate "curl " and null terminator

    // Prompt the user for a URL
    printf("Enter the URL to fetch data from: ");
    if (fgets(url, sizeof(url), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return;
    }

    // Remove newline character from the URL, if present
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[len - 1] = '\0';
    }

    // Validate the URL
    if (strlen(url) == 0) {
        fprintf(stderr, "Error: URL cannot be empty.\n");
        return;
    }

    // Ensure the command does not exceed the buffer size
    if (snprintf(command, sizeof(command), "curl \"%s\"", url) >= sizeof(command)) {
        fprintf(stderr, "Error: URL is too long.\n");
        return;
    }

    // Execute the curl command using system()
    int ret = system(command);
    if (ret == -1) {
        perror("Error executing system command");
    }
}

// Function prototypes
void jumpToLine(FILE *file, int lineNumber);
void searchInFile(FILE *file, const char *searchPattern);
void countWordOccurrences(FILE *file, const char *word);

void advance() {
    char fileName[256];
    char searchPattern[256];
    char wordToCount[256];
    int lineNumber;

    // Prompt for file name
    printf("Enter the file name (with extension): ");
    scanf("%255s", fileName);

    // Open the file
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Jump to a specific line
    printf("Jumping: Enter the line number to jump to: ");
    scanf("%d", &lineNumber);
    jumpToLine(file, lineNumber);

    // Search using regex
    printf("Regex Search: Enter the pattern to search for: ");
    scanf(" %[^\n]s", searchPattern); // Read pattern including spaces
    searchInFile(file, searchPattern);

    // Word count
    printf("Word Count: Enter the word to count occurrences: ");
    scanf(" %[^\n]s", wordToCount);
    countWordOccurrences(file, wordToCount);

    // Close the file
    fclose(file);
}

void jumpToLine(FILE *file, int lineNumber) {
    char buffer[MAX_LINE_LENGTH];
    int currentLine = 1;

    rewind(file); // Reset file pointer to the beginning
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (currentLine == lineNumber) {
            printf("Line %d: %s", currentLine, buffer);
            return;
        }
        currentLine++;
    }
    printf("Line %d not found.\n", lineNumber);
}

void searchInFile(FILE *file, const char *searchPattern) {
    char buffer[MAX_LINE_LENGTH];
    int lineNumber = 0;
    int found = 0;

    regex_t regex;
    if (regcomp(&regex, searchPattern, REG_EXTENDED | REG_NOSUB) != 0) {
        printf("Invalid regex pattern.\n");
        return;
    }

    rewind(file); // Reset file pointer to the beginning
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        lineNumber++;
        if (regexec(&regex, buffer, 0, NULL, 0) == 0) {
            printf("Found match at line %d: %s", lineNumber, buffer);
            found = 1;
        }
    }

    regfree(&regex); // Free regex memory

    if (!found) {
        printf("No matches found for pattern '%s'.\n", searchPattern);
    }
}

void countWordOccurrences(FILE *file, const char *word) {
    char buffer[MAX_LINE_LENGTH];
    int count = 0;
    int wordLength = strlen(word);

    rewind(file); // Reset file pointer to the beginning
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char *pos = buffer;
        while ((pos = strstr(pos, word)) != NULL) {
            // Ensure it's a standalone word
            if ((pos == buffer || !isalnum(*(pos - 1))) && !isalnum(*(pos + wordLength))) {
                count++;
            }
            pos += wordLength; // Move past the found word
        }
    }

    printf("The word '%s' appears %d times in the file.\n", word, count);
}

void tarball() {
    char project_name[100], filename[100], command[300];

    // Get project name
    printf("Enter the project name: ");
    if (fgets(project_name, sizeof(project_name), stdin) == NULL) {
        perror("Error reading project name");
        return;
    }
    project_name[strcspn(project_name, "\n")] = '\0'; // Remove newline

    // Get filename (with extension)
    printf("Enter the filename (including extension, e.g., file.txt): ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        perror("Error reading filename");
        return;
    }
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline

    // Check if the file exists
    if (access(filename, F_OK) != 0) {
        printf("Error: File '%s' does not exist!\n", filename);
        return;
    }

    // Construct and execute tar command
    snprintf(command, sizeof(command), "tar -czvf %s.tar.gz %s", project_name, filename);
    printf("Executing: %s\n", command);
    
    if (system(command) == -1) {
        perror("Error executing tar command");
    } else {
        printf("Tarball created successfully: %s.tar.gz\n", project_name);
    }
}

void api_axios() {
    char filename[MAX_FILENAME_LENGTH];
    char content[MAX_CONTENT_LENGTH];
    char command[MAX_FILENAME_LENGTH + 10]; // +10 to store "node " and ".js"

    // Ask for the filename
    printf("Enter the filename (without extension): ");
    fgets(filename, MAX_FILENAME_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove trailing newline if any

    // Open the file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Ask for the content
    printf("Enter content (type ':wq' to save and quit):\n");
    while (1) {
        // Get user input
        if (fgets(content, MAX_CONTENT_LENGTH, stdin) == NULL) {
            break; // Exit on EOF or error
        }

        // Check for ":wq" to quit and save
        if (strncmp(content, ":wq", 3) == 0) {
            break; // Exit loop to save and quit
        }

        // Write content to the file
        fputs(content, file);
    }

    // Close the file after saving
    fclose(file);
    printf("File saved as %s.js\n", filename);

    // Create and execute the command to run the file with Node.js
    snprintf(command, sizeof(command), "node %s.js", filename);
    int result = system(command);
    
    if (result == -1) {
        perror("Error running system command");
    } else {
        printf("Node.js command executed successfully.\n");
    }
}

void dewarn() {
    char mode[10], project[100], filename[200], command[500];

    // Prompt user for "debug" or "warning"
    while (1) {
        printf("Enter mode (debug/warning): ");
        scanf("%9s", mode);

        if (strcmp(mode, "debug") == 0 || strcmp(mode, "warning") == 0) {
            break; // Valid input, exit loop
        } else {
            printf("Invalid input! Please type 'debug' or 'warning'.\n");
        }
    }

    // Get the project name
    printf("Enter project name: ");
    scanf("%99s", project);

    // Get the filename with extension
    printf("Enter filename with extension (e.g., main.c): ");
    scanf("%199s", filename);

    // Construct the GCC command based on the mode
    if (strcmp(mode, "debug") == 0) {
        snprintf(command, sizeof(command), "gcc -g %s -o %s", filename, project);
    } else {
        snprintf(command, sizeof(command), "gcc -Wall %s -o %s", filename, project);
    }

    // Execute the compiled command
    printf("Running: %s\n", command);
    int status = system(command);

    // Check for compilation success
    if (status == 0) {
        printf("Compilation successful! Executable: %s\n", project);
    } else {
        printf("Compilation failed! Please check your file and try again.\n");
    }
}

void terminal() {
    char command[256];  // Buffer to hold the command input

    while (1) {
        // Display the prompt
        printf("Type Commands: ");
        
        // Get the command from user input
        if (fgets(command, sizeof(command), stdin) != NULL) {
            // Remove trailing newline character from fgets
            command[strcspn(command, "\n")] = '\0';

            // If the user types "exit", break out of the loop
            if (strcmp(command, "exit") == 0) {
                break;
            }

            // Run the system command
            system(command);
        }
    }
}

void latex() {
    char filename[MAX_FILENAME];
    FILE *file;
    char line[MAX_LINE];

    // Prompt for filename with extension
    printf("Enter LaTeX filename (with extension, e.g., document.tex): ");
    scanf("%255s", filename);
    getchar(); // Clear newline from buffer

    // Open the file for writing
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;  // Fixed: No return value in a void function
    }

    printf("Enter LaTeX code (type ':wq' on a new line to save and exit):\n");

    // Read user input and write to file
    while (1) {
        fgets(line, MAX_LINE, stdin);

        // Check for save and quit command
        if (strncmp(line, ":wq", 3) == 0 && (line[3] == '\n' || line[3] == '\0')) {
            break;
        }

        // Write input to file
        fputs(line, file);
    }

    fclose(file);
    printf("File saved as %s\n", filename);

    // Construct and execute the pdflatex command
    char command[MAX_FILENAME + 20];
    snprintf(command, sizeof(command), "pdflatex %s", filename);
    printf("Running: %s\n", command);
    int status = system(command);

    if (status == 0) {
        printf("LaTeX compilation successful!\n");
    } else {
        printf("Error: LaTeX compilation failed!\n");
    }
}

// Function to display AI usage manual
void manualAI() {
    printf("\n--- Txtmax AI Usage Manual ---\n");
    printf("\nWelcome to Txtmax AI! This AI assists with common Txtmax commands.\n");
    printf("\nHow to Use:\n");
    printf("1. Type a query related to Txtmax, and AI will respond with relevant commands.\n");
    printf("2. The AI recognizes keywords related to:\n");
    printf("   - Running code (e.g., 'run my code')\n");
    printf("   - Creating files (e.g., 'create a file')\n");
    printf("   - Searching files (e.g., 'search a file')\n");
    printf("   - Debugging C programs (e.g., 'debug c files')\n");
    printf("   - API testing (e.g., 'test APIs')\n");
    printf("   - Installing packages (e.g., 'install package')\n");
    printf("   - Editing LaTeX files (e.g., 'latex files')\n");
    printf("3. If the AI does not understand your query, try rewording it to match Txtmax commands.\n");
    printf("\nStart interacting with the AI by typing a query below!\n");
}

// AI function for pattern matching
void ai() {
    char input[256]; // User query

    printf("\nAsk me something about Txtmax:\n> ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character

    // Convert input to lowercase for case-insensitive matching
    to_lowercase(input);

    // Pattern Matching Responses
    if (strstr(input, "run my code") || strstr(input, "how to run")) {
        printf("\nSure, you can run your code by following these steps:\n\n");
        printf("- Step 1: \"Run Command\"\n  Type \"run\" in Txtmax, and it will ask for the filename including its extension.\n");
        printf("- Step 2: \"Choosing Compiler\"\n  Choose a compiler or interpreter such as GCC, Clang, Python, Node, Ruby, etc.\n");
        printf("- Step 3: \"Run Your Code\"\n  Txtmax will seamlessly run your code.\n");
    } 
    else if (strstr(input, "examples of hello world") || strstr(input, "hello world example")) {
        printf("\nType 'examples' command in Txtmax to get Hello World examples in various languages.\n");
    } 
    else if (strstr(input, "create a file") || strstr(input, "how to create")) {
        printf("\nTo create a file in Txtmax, type:\n  \"create <filename>\"\nThen write contents and save with :wq.\n");
    } 
    else if (strstr(input, "delete a file") || strstr(input, "remove file")) {
        printf("\nTo delete a file, type:\n  \"delete <filename>\"\nThis will remove the specified file.\n");
    } 
    else if (strstr(input, "search a file") || strstr(input, "find file")) {
        printf("\nTo search for a file, type:\n  \"search <filename>\"\nIt will locate files matching the given name.\n");
    } 
    else if (strstr(input, "list all files") || strstr(input, "view files in directory")) {
        printf("\nTo list all files in the current directory, type:\n  \"files\"\n");
    } 
    else if (strstr(input, "edit file") || strstr(input, "modify file")) {
        printf("\nTo edit a file, type:\n  \"edit <filename> <line>\"\n");
    } 
    else if (strstr(input, "get file info") || strstr(input, "file details")) {
        printf("\nTo get file details, type:\n  \"info <filename>\"\n");
    } 
    else if (strstr(input, "debug c files") || strstr(input, "check c code errors")) {
        printf("\nTo debug C files, type \"debug\" and provide the project name and filename.\n");
    }
    else if (strstr(input, "test apis") || strstr(input, "fetch restful api data")) {
        printf("\nTo test RESTful APIs, use:\n  \"api\" or \"axios\" command.\n");
    }
    else if (strstr(input, "convert file to tarball") || strstr(input, "make tar file")) {
        printf("\nTo create a tarball file, type:\n  \"tarball <filename>\"\n");
    }
    else if (strstr(input, "install package") || strstr(input, "package manager")) {
        printf("\nTo install a package, use:\n  \"packages\" command and choose a package manager.\n");
    }
    else if (strstr(input, "latex files") || strstr(input, "edit latex")) {
        printf("\nTo create and edit LaTeX files, use:\n  \"latex <filename>.tex\"\n");
    }
    else {
        printf("\nI'm sorry, I don't understand your query. Try asking something related to Txtmax commands!\n");
    }
}

void renameFile() {
    char oldName[256], newName[256];

    // Prompt user for old file name
    printf("Enter the current filename (with extension): ");
    fgets(oldName, sizeof(oldName), stdin);
    
    // Remove newline character if present
    oldName[strcspn(oldName, "\n")] = 0;

    // Prompt user for new file name
    printf("Enter the new filename (with extension): ");
    fgets(newName, sizeof(newName), stdin);
    
    // Remove newline character if present
    newName[strcspn(newName, "\n")] = 0;

    // Attempt to rename the file
    if (rename(oldName, newName) == 0) {
        printf("File renamed successfully from \"%s\" to \"%s\".\n", oldName, newName);
    } else {
        perror("Error renaming file");
    }
}

void man_txtmax() {
   printf("                     Txtmax Manual                      \n\n");
    printf("NAME\n");
    printf("       txtmax - Lightweight Advanced Text Editor for Linux\n\n");

    printf("                      DESCRIPTION\n");
    printf("       Txtmax is a lightweight, fast, and fully open-source text editor designed for Linux and Unix-like\n");
    printf("       systems. It provides an easy-to-use command-line interface for text file creation, editing,\n");
    printf("       viewing, and management. Txtmax supports syntax highlighting, integrated code execution, file\n");
    printf("       versioning via Git, and many advanced features for developers.\n\n");

    printf("                      COMMANDS\n");
    printf("       help\n");
    printf("           Display a list of all available commands and their descriptions.\n\n");

    printf("       create <filename>\n");
    printf("           Create a new text file and save it locally. You can write code in over 50 programming\n");
    printf("           languages, with syntax highlighting and support for version control (commit message, branch, version).\n\n");

    printf("       rename\n");
    printf("           Rename Files\n\n");
    
    printf("       files\n");
    printf("           List all regular files in the current directory.\n\n");

    printf("       view <filename>\n");
    printf("           View the contents of a specified text file with syntax highlighting for code readability.\n\n");

    printf("       edit <filename> <line>\n");
    printf("           Edit a specific line in an existing file.\n\n");

    printf("       delete <filename>\n");
    printf("           Delete the specified file from the current directory.\n\n");

    printf("       search <filename>\n");
    printf("           Search for files by name across all directories.\n\n");

    printf("       info <filename>\n");
    printf("           Retrieve detailed information about a file, including its name, extension, creation time,\n");
    printf("           modification time, version control, commit message, branch, and version.\n\n");

    printf("       examples\n");
    printf("           Show example code snippets for popular programming languages like C, Python, Java, JavaScript,\n");
    printf("           C++, Rust, Ruby, Kotlin, and more.\n\n");

    printf("       sql\n");
    printf("           Show SQL examples and query syntax for relational and NoSQL databases like MySQL, PostgreSQL, and MongoDB.\n\n");

    printf("       run\n");
    printf("           Run code written in the text file. Txtmax supports running code using compilers and interpreters\n");
    printf("           like GCC, Clang, Python, Node.js, and more.\n\n");

    printf("       packages\n");
    printf("           Install Python (pip) or Node.js (npm) or Gem (Ruby) or Go (Golang) and many other packages from the terminal. You can choose the package manager\n");
    printf("           and install the required package.\n\n");

    printf("       api\n");
    printf("           Test Restful APIs Directly in the Editor.\n\n");

    printf("       advance\n");
    printf("           Open File and jump into an content and search for specific text/code in it.\n\n");

    printf("       axios\n");
    printf("           Fetch Data from URL.\n\n");
    
    printf("       debug\n");
    printf("           Debug and Warning your C Code.\n\n");

    printf("       terminal\n");
    printf("           Built-in Terminal.\n\n");

    printf("       latex\n");
    printf("           Edit Latex Files.\n\n");

    printf("       tarball\n");
    printf("           Convert Files to Tarball.\n\n");

    printf("       manai\n");
    printf("           Comprehensive Manual of using the AI.\n\n");

    printf("       ai\n");
    printf("          Chat with the Txtmax AI.\n\n");
  
    printf("       exit\n");
    printf("           Exit the Txtmax editor.\n\n");
  
    printf("                      FEATURES\n");
    printf("       - File Creation, Viewing, Editing, Deletion, and Management\n");
    printf("       - Syntax Highlighting for Programming Languages\n");
    printf("       - Run Code Quickly with Integrated Compilers and Interpreters\n");
    printf("       - Git Integration for Version Control and Commit Management\n");
    printf("       - Support for Over 40 Programming Languages\n");
    printf("       - Installation of Python and Node.js Packages\n\n");

    printf("USAGE\n");
    printf("       To start using Txtmax:\n");
    printf("         1. Clone the repository:\n");
    printf("              git clone https://github.com/Calestial2/Txtmax.git\n");
    printf("           2. Navigate to the directory:\n");
    printf("              cd Txtmax\n");
    printf("           3. Compile the code:\n");
    printf("              gcc txtmax.c -o txtmax\n");
    printf("           4. Run Txtmax:\n");
    printf("              ./txtmax10\n\n");

    printf("       Alternatively, use the Makefile to install the latest version with:\n");
    printf("           make ./txtmax\n\n");

    printf("EXAMPLES\n");
    printf("       - Create a new C file:\n");
    printf("           create hello.c\n\n");

    printf("       - View a file with syntax highlighting:\n");
    printf("           view hello.c\n\n");

    printf("       - Edit the first line of the file:\n");
    printf("           edit hello.c 1\n\n");

    printf("       - Run the C code:\n");
    printf("           run\n\n");

    printf("       - Install a Python package:\n");
    printf("           packages pip requests\n\n");

    printf("       - Search for a file:\n");
    printf("           search hello.c\n\n");

    printf("SUPPORTED LANGUAGES\n");
    printf("       C, Python, Java, JavaScript, C++, Rust, Ruby, Kotlin, Swift, TypeScript, Dart, Go, Haskell,\n");
    printf("       R, PHP, Lua, Objective-C, Groovy, Erlang, Bash, Julia, F#, C#, Scheme, Clojure, Fortran, Cobol,\n");
    printf("       VHDL, Lisp, SQL, Matlab, Perl, Scala, PostgreSQL, NoSQL, ActionScript, Ada, Nim, Crystal,\n");
    printf("       D, Assembly, Purescript, Prolog, Zig, Brainfu*k, HTML and many More\n\n");

    printf("                    LICENSE\n");
    printf("       Txtmax is licensed under the GNU General Public License v3.0. You are free to use, modify, and distribute the software according to the terms of the license.\n\n");

    printf("                   AUTHOR\n");
    printf("             Calestial Ashley <calestialashley@gmail.com>\n");
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
    printf("  man txtmax              Comprehensive Manual\n");
    printf("  create <filename>       Create a new file and save locally\n");
    printf("  rename                  Rename Files\n");
    printf("  files                   List all files in the current directory\n");
    printf("  search <filename>       Search for files with the specified name\n");
    printf("  view <filename>         View file contents with syntax highlighting\n");
    printf("  edit <filename> <line>  Edit a specific line in the file\n");
    printf("  delete <filename>       Delete a file\n");
    printf("  info <filename>         Show file info (name, extension, creation time, modification time)\n");
    printf("  run                     Excute Your Code without exiting\n");
    printf("  packages                Install Packages\n");
    printf("  axios                   Fetch Data with Axios\n");
    printf("  api                     Test Restful APis directly in the editor\n");
    printf("  advance                 Open Files and Jump to Specfic line of it and Search for an Specfic Text/Code\n");
    printf("  examples                Show Hello World examples in various languages\n");
    printf("  debug                   Debug and Warning C Files\n");
    printf("  terminal                Built-in Terminal\n");
    printf("  latex                   Edit Latex Files\n");
    printf("  tarball                 Convert your Files to Tarball\n");
    printf("  sql                     Show SQL code examples\n");
    printf("  ai                      Use and Chat with the AI\n");
    printf("  manai                   Comprehensive Manual of How to use Txtmax\n");
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
        } else if (strcmp(command, "run") == 0) {
        quick_run();
            } else if (strcmp(command, "packages") == 0) {
        packages();
            } else if (strcmp(command, "man txtmax") == 0) {
        man_txtmax();
            } else if (strcmp(command, "api") == 0) {
        api();
            } else if (strcmp(command, "advance") == 0) {
        advance();
            } else if (strcmp(command, "axios") == 0) {
        api_axios();
           } else if (strcmp(command, "debug") == 0) {
        dewarn();
            } else if (strcmp(command, "terminal") == 0) {
        terminal();
            } else if (strcmp(command, "latex") == 0) {
        latex();
            } else if (strcmp(command, "ai") == 0) {
        ai();
            } else if (strcmp(command, "manai") == 0) {
        manualAI();
            } else if (strcmp(command, "rename") == 0) {
        renameFile();
            } else if (strcmp(command, "tarball") == 0) {
        tarball();
           } else if (strcmp(command, "exit") == 0) {
            printf("Exiting txtmax...\n");
            break;
        } else {
            printf("Unknown command: %s\n", command);
        }
    }

    return 0;
}
