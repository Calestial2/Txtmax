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
#include <fcntl.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAX_INPUT_SIZE 256
#define MAX_CONTENT 1024
#define MAX_URL_LENGTH 2048
#define MAX_LINE_LENGTH 1024
#define MAX_FILENAME_LENGTH 256
#define MAX_CONTENT_LENGTH 1024
#define MAX_INPUT_SIZE 256
#define MY_MAX_INPUT 1024
#define MAX_FILENAME 256
#define MAX_LINE 1024
#define MAX_FILES 100
#define MAX_FILENAME 256
#define MAX_PATH 1024   
#define MAX_FILE_NAME 255 
#define MAX_LEN 100
#define RECYCLE_BIN "recycle_bin"
#define MAX_FILENAME_LEN 256
#define MAX_COMMAND_LENGTH 256
#define MAX_FILENAME_LENGTH 200

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

void deploy() {
    system("gcc deploy.c -o deploy && ,/deploy");
}

void getFileSize() {
    char filename[256]; // Buffer for filename
    FILE *file;
    long size;

    // Ask for the filename
    printf("Enter the filename (with extension): ");
    scanf("%255s", filename);

    // Open the file in read mode
    file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: Could not open file \"%s\"\n", filename);
        return;
    }

    // Seek to end of file to determine size
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    
    // Close the file
    fclose(file);

    // Display the size
    printf("Size of \"%s\": %ld bytes\n", filename, size);
}

void benchmark() {
    struct timeval start_wall, end_wall;
    struct rusage start_usage, end_usage;
    double wall_time, user_time, system_time, cpu_percent;
    long max_rss;

    // Get starting time and resources
    gettimeofday(&start_wall, NULL);
    getrusage(RUSAGE_SELF, &start_usage);

    // Start of benchmarked code
    // Example computation: calculate sum of square roots
    volatile double sum = 0; // volatile prevents optimization
    for (long i = 0; i < 10000000L; i++) {
        sum += sqrt(i);
    }
    // End of benchmarked code

    // Get ending time and resources
    gettimeofday(&end_wall, NULL);
    getrusage(RUSAGE_SELF, &end_usage);

    // Calculate wall-clock time
    wall_time = (end_wall.tv_sec - start_wall.tv_sec) +
                (end_wall.tv_usec - start_wall.tv_usec) / 1000000.0;

    // Calculate CPU times
    user_time = (end_usage.ru_utime.tv_sec - start_usage.ru_utime.tv_sec) +
                (end_usage.ru_utime.tv_usec - start_usage.ru_utime.tv_usec) / 1000000.0;

    system_time = (end_usage.ru_stime.tv_sec - start_usage.ru_stime.tv_sec) +
                  (end_usage.ru_stime.tv_usec - start_usage.ru_stime.tv_usec) / 1000000.0;

    // Calculate CPU usage percentage
    cpu_percent = ((user_time + system_time) / wall_time) * 100.0;

    // Get maximum resident set size (memory usage)
    max_rss = end_usage.ru_maxrss; // In KB on Linux, bytes on BSD

    // Print results
    printf("Execution Metrics:\n");
    printf("------------------\n");
    printf("Wall-clock time:   %.6f seconds\n", wall_time);
    printf("User CPU time:     %.6f seconds\n", user_time);
    printf("System CPU time:   %.6f seconds\n", system_time);
    printf("Total CPU time:    %.6f seconds\n", user_time + system_time);
    printf("CPU Usage:         %.2f%%\n", cpu_percent);
    printf("Max memory usage:  %ld KB\n", max_rss);
    printf("Page faults:       %ld (minor) / %ld (major)\n", 
           end_usage.ru_minflt - start_usage.ru_minflt,
           end_usage.ru_majflt - start_usage.ru_majflt);
    printf("Context switches:  %ld (voluntary) / %ld (involuntary)\n",
           end_usage.ru_nvcsw - start_usage.ru_nvcsw,
           end_usage.ru_nivcsw - start_usage.ru_nivcsw);
}

void format_code() {
    char formatter[MAX_COMMAND_LENGTH];
    char filename[MAX_FILENAME_LENGTH];
    char command[MAX_COMMAND_LENGTH];

    // Prompt for formatter
    printf("Choose formatter (clang-format/black): ");
    if (scanf("%255s", formatter) != 1) {
        fprintf(stderr, "Error reading input.\n");
        return;
    }

    // Validate choice
    if (strcmp(formatter, "clang-format") != 0 && strcmp(formatter, "black") != 0) {
        fprintf(stderr, "Invalid choice. Please enter 'clang-format' or 'black'.\n");
        return;
    }

    // Prompt for filename
    printf("Enter filename (including extension): ");
    if (scanf("%199s", filename) != 1) {
        fprintf(stderr, "Error reading filename.\n");
        return;
    }

    // Construct command
    if (strcmp(formatter, "clang-format") == 0) {
        snprintf(command, sizeof(command), "clang-format -i %s", filename);
    } else {
        snprintf(command, sizeof(command), "black %s", filename);
    }

    // Execute command
    int status = system(command);
    if (status == -1) {
        perror("system() failed");
    } else {
        printf("Formatting completed successfully.\n");
    }
}

void quick_run() {
    char filename[MAX_INPUT_SIZE];
    char compiler[MAX_INPUT_SIZE];
    char libraries[MAX_INPUT_SIZE];
    char command[MAX_INPUT_SIZE];
    char temp[MAX_INPUT_SIZE];

    // Prompt for filename
    printf("Enter the file name with extension (e.g., program.c, script.py): ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        fprintf(stderr, "Error reading file name.\n");
        return;
    }
    filename[strcspn(filename, "\n")] = 0; // Remove trailing newline

    // Check if the file exists
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error: File does not exist");
        return;
    }
    fclose(file);

    // Prompt for compiler/interpreter
    printf("Enter the compiler or interpreter (gcc, g++, clang, python, node, nasm, tcl, bash, ruby, perl, rustc, go): ");
    if (fgets(compiler, sizeof(compiler), stdin) == NULL) {
        fprintf(stderr, "Error reading compiler or interpreter.\n");
        return;
    }
    compiler[strcspn(compiler, "\n")] = 0; // Remove trailing newline

    // Prompt for external libraries
    printf("Enter the external libraries (or 'n' if none): ");
    if (fgets(libraries, sizeof(libraries), stdin) == NULL) {
        fprintf(stderr, "Error reading libraries.\n");
        return;
    }
    libraries[strcspn(libraries, "\n")] = 0; // Remove trailing newline

    // Match compiler/interpreter and build the command
    const char *ext = strrchr(filename, '.'); // Get file extension
    if (!ext) {
        printf("Error: Unable to detect file extension.\n");
        return;
    }

    if (strcmp(compiler, "gcc") == 0 || strcmp(compiler, "clang") == 0) {
        if (strcmp(ext, ".c") == 0) {
            snprintf(command, sizeof(command), "%s %s %s -o output && ./output", compiler, filename, strcmp(libraries, "n") == 0 ? "" : libraries);
        } else {
            printf("Error: %s is only compatible with C files.\n", compiler);
            return;
        }
    } else if (strcmp(compiler, "g++") == 0) {
        if (strcmp(ext, ".cpp") == 0 || strcmp(ext, ".cxx") == 0 || strcmp(ext, ".cc") == 0) {
            snprintf(command, sizeof(command), "g++ %s %s -o output && ./output", filename, strcmp(libraries, "n") == 0 ? "" : libraries);
        } else {
            printf("Error: g++ is only compatible with C++ files (.cpp, .cxx, .cc).\n");
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
            snprintf(command, sizeof(command), "nasm -f elf64 %s -o output.o && gcc %s output.o -o output && ./output", filename, strcmp(libraries, "n") == 0 ? "" : libraries);
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
    } else if (strcmp(compiler, "ruby") == 0) {
        if (strcmp(ext, ".rb") == 0) {
            snprintf(command, sizeof(command), "ruby %s", filename);
        } else {
            printf("Error: Ruby is only compatible with .rb files.\n");
            return;
        }
    } else if (strcmp(compiler, "perl") == 0) {
        if (strcmp(ext, ".pl") == 0) {
            snprintf(command, sizeof(command), "perl %s", filename);
        } else {
            printf("Error: Perl is only compatible with .pl files.\n");
            return;
        }
    } else if (strcmp(compiler, "rustc") == 0) {
        if (strcmp(ext, ".rs") == 0) {
            snprintf(command, sizeof(command), "rustc %s %s -o output && ./output", filename, strcmp(libraries, "n") == 0 ? "" : libraries);
        } else {
            printf("Error: rustc is only compatible with .rs files.\n");
            return;
        }
    } else if (strcmp(compiler, "go") == 0) {
        if (strcmp(ext, ".go") == 0) {
            snprintf(command, sizeof(command), "go run %s", filename);
        } else {
            printf("Error: Go is only compatible with .go files.\n");
            return;
        }
    } else {
        printf("Error: Unsupported compiler or interpreter '%s'.\n", compiler);
        return;
    }

    // Execute the command
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

void sqlite() {
    char filename[256];
    char command[1024];
    FILE *file;
    
    // Ask for the filename
    printf("Enter SQLite filename (including extension): ");
    scanf("%255s", filename);
    
    // Open the file for writing
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter SQLite command (use ':wq' to save and exit):\n");
    
    // Read a single command from user
    if (fgets(command, sizeof(command), stdin) == NULL) {
        fclose(file);
        return;  // Exit if no command is provided
    }

    // Check for exit command ':wq'
    if (strncmp(command, ":wq", 3) == 0) {
        fclose(file);
        printf("Exiting without saving.\n");
        return;  // Exit if user enters ':wq'
    }

    // Write the command to the file
    fputs(command, file);

    // Close the file after writing
    fclose(file);

    // Run the SQLite command with the provided file
    char system_command[128];
    snprintf(system_command, sizeof(system_command), "sqlite3 %s < %s", filename, filename);
    system(system_command);

    printf("SQLite command saved and executed.\n");
}

// Function prototypes
void jumpToLine(FILE *file, int lineNumber);
void searchInFile(FILE *file, const char *fileName, const char *searchPattern); // Pass fileName
void countWordOccurrences(FILE *file, const char *word);

void advance() {
    char fileName[256];
    char searchPattern[256];
    char wordToCount[256];
    int lineNumber;

    // Prompt for file name
    printf("Enter the file name (with extension): ");
    if (scanf("%255s", fileName) != 1) {
        fprintf(stderr, "Error reading file name.\n");
        return;
    }

    // Open the file
    FILE *file = fopen(fileName, "r+"); // Open in read/write mode
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Jump to a specific line
    printf("Jumping: Enter the line number to jump to: ");
    if (scanf("%d", &lineNumber) != 1) {
        fprintf(stderr, "Error reading line number.\n");
        fclose(file);
        return;
    }
    jumpToLine(file, lineNumber);

    // Search using regex and edit
    printf("Regex Search: Enter the pattern to search for: ");
    if (scanf(" %[^\n]s", searchPattern) != 1) { // Read pattern including spaces
        fprintf(stderr, "Error reading search pattern.\n");
        fclose(file);
        return;
    }
    searchInFile(file, fileName, searchPattern); // Pass fileName to searchInFile

    // Word count
    printf("Word Count: Enter the word to count occurrences: ");
    if (scanf(" %[^\n]s", wordToCount) != 1) {
        fprintf(stderr, "Error reading word to count.\n");
        fclose(file);
        return;
    }
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

void searchInFile(FILE *file, const char *fileName, const char *searchPattern) {  // Receive fileName
    char buffer[MAX_LINE_LENGTH];
    char tempFileName[] = "temp.txt";
    FILE *tempFile = fopen(tempFileName, "w+"); // Temporary file for writing
    if (tempFile == NULL) {
        perror("Error opening temporary file");
        return;
    }

    int lineNumber = 0;
    int found = 0;

    regex_t regex;
    if (regcomp(&regex, searchPattern, REG_EXTENDED) != 0) {
        printf("Invalid regex pattern.\n");
        fclose(tempFile);
        return;
    }

    rewind(file); // Reset file pointer to the beginning
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        lineNumber++;
        if (regexec(&regex, buffer, 0, NULL, 0) == 0) {
            printf("Found match at line %d: %s", lineNumber, buffer);
            found = 1;
            char replacement[MAX_LINE_LENGTH];
            printf("Enter the replacement text: ");
            if (scanf(" %[^\n]s", replacement) != 1) { // Read replacement text including spaces
                fprintf(stderr, "Error reading replacement text.\n");
                break;
            }
            fprintf(tempFile, "%s\n", replacement); // Write replacement to temp file
        } else {
            fprintf(tempFile, "%s", buffer); // Write original line to temp file
        }
    }

    regfree(&regex); // Free regex memory

    fclose(tempFile);

    if (found) {
        // Replace original file with the temporary file
        if (freopen(fileName, "w+", file) == NULL) { // Use fileName
            perror("Error reopening original file for writing");
            return;
        }
        tempFile = fopen(tempFileName, "r");
        if (tempFile == NULL) {
            perror("Error reopening temporary file for reading");
            return;
        }
        while (fgets(buffer, sizeof(buffer), tempFile) != NULL) {
            fputs(buffer, file);
        }
        fclose(tempFile);
        remove(tempFileName); // Remove temporary file
        printf("File has been updated with the replacements.\n");
    } else {
        printf("No matches found for pattern '%s'.\n", searchPattern);
        remove(tempFileName); // Remove temporary file
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

void tmux_integration() {
    char session_name[256];
    char command[1024];
    int result;

    // Get session name from user
    printf("Enter tmux session name: ");
    if (!fgets(session_name, sizeof(session_name), stdin)) {
        perror("Error reading input");
        return;
    }
    session_name[strcspn(session_name, "\n")] = '\0'; // Remove newline

    // Create new detached session
    snprintf(command, sizeof(command), "tmux new-session -d -s \"%s\"", session_name);
    if ((result = system(command)) != 0) {
        fprintf(stderr, "Error creating tmux session (code %d)\n", result);
        return;
    }

    // Command input loop
    printf("Enter commands to execute in the session (type 'exit' to finish):\n");
    while (1) {
        printf("tmux> ");
        if (!fgets(command, sizeof(command), stdin)) break;
        command[strcspn(command, "\n")] = '\0'; // Remove newline

        if (strcmp(command, "exit") == 0) break;

        // Send command to tmux session
        snprintf(command, sizeof(command), 
                "tmux send-keys -t \"%s\" \"%s\" Enter",
                session_name, command);
        
        if ((result = system(command)) != 0) {
            fprintf(stderr, "Error executing command (code %d)\n", result);
        }
        sleep(1); // Allow time for command execution
    }

    // Attach to session
    printf("Attaching to session '%s'...\n", session_name);
    snprintf(command, sizeof(command), "tmux attach -t \"%s\"", session_name);
    system(command);
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

void openai() {
    char filename[256], apiKey[256], modelName[256];
    FILE *file;

    // Prompt for filename
    printf("Enter the filename (including extension): ");
    scanf("%255s", filename);

    // Prompt for API key
    printf("Enter your API Key Secret: ");
    scanf("%255s", apiKey);

    // Prompt for model name
    printf("Enter Model Name: ");
    scanf("%255s", modelName);

    // Create the file
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file!\n");
        return;
    }

    // Write content to the file
    fprintf(file, 
        "import openai\n"
        "import os\n"
        "from time import sleep\n"
        "import sys\n\n"
        "# Check if any command line arguments are provided\n"
        "if len(sys.argv) < 2:\n"
        "    print(\"Usage: ask < Question >\")\n"
        "    sys.exit(1)\n\n"
        "# Combine all command line arguments (excluding the script name) into a single string\n"
        "askx = ' '.join(sys.argv[1:])\n\n"
        "API = \"%s\"\n\n"
        "try:\n"
        "    openai.api_key = (API)\n\n"
        "    response = openai.Completion.create(\n"
        "                            model='%s',\n"
        "                            prompt=askx,\n"
        "                            max_tokens=3048,\n"
        "                            top_p=1.0,\n"
        "    presence_penalty=0.0)\n\n"
        "    print( response.choices[0].text + \"\\n\") # type:ignore\n"
        "except Exception as e:\n"
        "    print(e)\n", apiKey, modelName);

    fclose(file);

    // Run the Python file using system()
    char command[512];
    snprintf(command, sizeof(command), "python %s", filename);
    system(command);
}

void txtmaxnote() {
    system("gcc notebook.c -o notebook && ./notebook");
}

void auto_completion() {
    system("gcc -o auto_completion auto_completion.c -lncurses && ./auto_completion");
}

void security() {
    system("gcc security.c -o security -lssl -lcrypto && ./security");
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

typedef struct {
    const char *command;
    const char *ansi_code;
} FormatCommand;

const FormatCommand commands[] = {
    {"bold + italic", "\033[1;3m"},
    {"strike through", "\033[9m"},
    {"underlined", "\033[4m"},
    {"inverse", "\033[7m"},
    {"bold", "\033[1m"},
    {"italic", "\033[3m"},
};

const int num_commands = sizeof(commands) / sizeof(commands[0]);

void process_line(const char *line, FILE *file) {
    if (strncmp(line, ":wq", 3) == 0) {
        exit(0);
    }

    if (line[0] == ':') {
        const char *cmd_start = line + 1;
        while (*cmd_start && isspace(*cmd_start)) cmd_start++;

        for (int i = 0; i < num_commands; i++) {
            size_t cmd_len = strlen(commands[i].command);
            if (strncmp(cmd_start, commands[i].command, cmd_len) == 0) {
                const char *text = cmd_start + cmd_len;
                while (*text && isspace(*text)) text++;

                if (*text) {
                    fprintf(file, "%s%s\033[0m\n", commands[i].ansi_code, text);
                }
                return;
            }
        }
    }
    fprintf(file, "%s\n", line);
}

void markdown() {
    char filename[MY_MAX_INPUT];
    printf("Enter filename: ");
    fgets(filename, MY_MAX_INPUT, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    printf("Enter text (type :wq to save and exit):\n");
    
    while (1) {
        char line[MY_MAX_INPUT];
        if (!fgets(line, MY_MAX_INPUT, stdin)) break;

        line[strcspn(line, "\n")] = '\0';
        process_line(line, file);
    }

    fclose(file);
    printf("File saved successfully.\n");
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

void movef() {
    char files[MAX_FILES][MAX_FILENAME];  // Array to store filenames
    char folder[MAX_FILENAME];            // Destination folder
    int file_count = 0;

    printf("Enter filenames (type 'done' to finish):\n");

    // Input filenames
    while (file_count < MAX_FILES) {
        printf("File %d: ", file_count + 1);
        fgets(files[file_count], MAX_FILENAME, stdin);
        files[file_count][strcspn(files[file_count], "\n")] = '\0';  // Remove newline

        if (strcmp(files[file_count], "done") == 0) {
            break;  // Stop if user enters "done"
        }

        file_count++;
    }

    if (file_count == 0) {
        printf("No files entered.\n");
        return;
    }

    // Input destination folder
    printf("Enter destination folder name: ");
    fgets(folder, MAX_FILENAME, stdin);
    folder[strcspn(folder, "\n")] = '\0';  // Remove newline

    // Moving files
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i], "done") == 0) {
            break;
        }

        char new_path[MAX_PATH];
        snprintf(new_path, MAX_PATH, "%s/%s", folder, files[i]);

        if (rename(files[i], new_path) == 0) {
            printf("Moved: %s -> %s\n", files[i], new_path);
        } else {
            perror("Error moving file");
        }
    }

    printf("File move operation completed.\n");
} 

// Function to copy a file
void copy_file(const char *source_file, const char *destination_file) {
    FILE *src = fopen(source_file, "rb");
    if (src == NULL) {
        perror("Error opening source file");
        return;
    }

    FILE *dest = fopen(destination_file, "wb");
    if (dest == NULL) {
        perror("Error opening destination file");
        fclose(src);
        return;
    }

    // Copy content from source file to destination file
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    printf("Successfully copied: %s to %s\n", source_file, destination_file);

    fclose(src);
    fclose(dest);
}

// Function to copy multiple files to the given folder
void copy_files_to_folder() {
    char files[10][MAX_FILE_NAME];  // Array to store up to 10 filenames
    char folder[MAX_PATH];
    char destination[MAX_PATH];
    int num_files = 0;

    // Prompt for filenames
    printf("Enter filenames with extension (separate with spaces, max 10 files): ");
    while (scanf("%s", files[num_files]) == 1 && num_files < 10) {
        num_files++;
        if (getchar() == '\n') break;  // break if user presses Enter (no more filenames)
    }

    // Prompt for destination folder
    printf("Enter the folder name where files will be copied: ");
    scanf("%s", folder);

    // Ensure folder path ends with a '/'
    if (folder[strlen(folder) - 1] != '/') {
        strcat(folder, "/");
    }

    // Try to create the folder if it does not exist
    struct stat st = {0};
    if (stat(folder, &st) == -1) {
        if (mkdir(folder, 0700) == -1) {
            perror("Error creating directory");
            return;
        }
    }

    // Copy each file to the folder
    for (int i = 0; i < num_files; i++) {
        snprintf(destination, sizeof(destination), "%s%s", folder, files[i]);
        copy_file(files[i], destination);  // Call the copy_file function with the right arguments
    }
}

void generateGradleScript() {
    char pluginName[100], dependencyName[100], dirName[100], taskName[100], printMessage[100];
    FILE *gradleFile;
    
    // Prompt for plugin name
    printf("Enter plugin name (e.g., 'java', 'application'): ");
    scanf("%s", pluginName);

    // Prompt for dependency name
    printf("Enter dependency name (e.g., 'com.google.guava:guava:30.1-jre'): ");
    scanf("%s", dependencyName);

    // Prompt for directory name
    printf("Enter the directory name for the project: ");
    scanf("%s", dirName);

    // Prompt for task name
    printf("Enter the task name to run (e.g., 'build', 'test'): ");
    scanf("%s", taskName);

    // Prompt for a message to print
    printf("Enter the message that the task should print: ");
    scanf(" %[^\n]%*c", printMessage);  // To allow spaces in the input

    // Create the directory if it doesn't exist
    char createDirCmd[150];
    snprintf(createDirCmd, sizeof(createDirCmd), "mkdir -p %s", dirName);
    system(createDirCmd);

    // Navigate into the directory
    chdir(dirName);

    // Create the build.gradle file
    gradleFile = fopen("build.gradle", "w");
    if (gradleFile == NULL) {
        printf("Error: Unable to create build.gradle file.\n");
        return;
    }

    // Write the Gradle script to the file
    fprintf(gradleFile, "plugins {\n");
    fprintf(gradleFile, "    id '%s'\n", pluginName);
    fprintf(gradleFile, "}\n\n");

    fprintf(gradleFile, "dependencies {\n");
    fprintf(gradleFile, "    implementation '%s'\n", dependencyName);
    fprintf(gradleFile, "}\n\n");

    fprintf(gradleFile, "task %s {\n", taskName);
    fprintf(gradleFile, "    doLast {\n");
    fprintf(gradleFile, "        println '%s'\n", printMessage);
    fprintf(gradleFile, "    }\n");
    fprintf(gradleFile, "}\n");

    // Close the file
    fclose(gradleFile);

    // Run Gradle command to execute the task
    char gradleCmd[150];
    snprintf(gradleCmd, sizeof(gradleCmd), "gradle %s", taskName);
    printf("Running Gradle task '%s'...\n", taskName);
    system(gradleCmd);
}

void create_dotnet_project() {
    char component[20];
    char filename[100];
    char file_content[500];
    char file_path[200];
    FILE *file;

    // Step 1: Ask the user to choose a component
    printf("Choose a component (dotnet sdk / asp.dotnet): ");
    fgets(component, sizeof(component), stdin);
    component[strcspn(component, "\n")] = 0;  // Remove newline character

    if (strcmp(component, "dotnet sdk") != 0 && strcmp(component, "asp.dotnet") != 0) {
        printf("Invalid component. Exiting...\n");
        return;
    }

    // Step 2: Ask for the directory path (optional, default is current directory)
    printf("Enter the directory to save the file (or press enter to save in the current directory): ");
    fgets(file_path, sizeof(file_path), stdin);
    file_path[strcspn(file_path, "\n")] = 0;  // Remove newline character

    // Default to the current directory if no path is provided
    if (strlen(file_path) == 0) {
        getcwd(file_path, sizeof(file_path));  // Get the current working directory
    }

    // Step 3: Ask for the filename (including extension)
    printf("Enter the filename (including extension, e.g., MyProgram.cs): ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;  // Remove newline character

    // Combine directory path and filename
    snprintf(file_path, sizeof(file_path), "%s/%s", file_path, filename);

    // Step 4: Open file for writing content
    file = fopen(file_path, "w");
    if (file == NULL) {
        printf("Error opening file. Exiting...\n");
        return;
    }

    // Step 5: Prompt user to write content
    printf("Write the .NET file content (type :wq to finish):\n");
    while (1) {
        fgets(file_content, sizeof(file_content), stdin);
        if (strcmp(file_content, ":wq\n") == 0) {
            break;
        }
        fprintf(file, "%s", file_content);
    }

    // Close the file after writing
    fclose(file);

    // Step 6: Run system commands
    printf("Building and running the .NET project...\n");

    // Run dotnet build (assuming the file is part of a .NET project)
    char build_command[200];
    snprintf(build_command, sizeof(build_command), "dotnet build %s", file_path);
    system(build_command);

    // Run dotnet run (assuming the file is a runnable .NET program)
    char run_command[200];
    snprintf(run_command, sizeof(run_command), "dotnet run %s", file_path);
    system(run_command);

    printf("Process completed.\n");
}

void ignore() {
    char choice[10];
    
    // Prompt the user for input
    printf("What secret you want to store (nodejs/env/log): ");
    scanf("%s", choice);
    
    // Open the .gitignore file for writing
    FILE *gitignore = fopen(".gitignore", "w");
    if (gitignore == NULL) {
        printf("Error creating .gitignore file.\n");
        return;
    }
    
    // Process user choice and generate the corresponding .gitignore content
    if (strcmp(choice, "nodejs") == 0) {
        fprintf(gitignore, "node_modules/\n*.log\nnpm-debug.log\n.yarn-debug.log\n.yarn-error.log\n");
    } 
    else if (strcmp(choice, "env") == 0) {
        fprintf(gitignore, ".env\n.env.local\n.env.*\n");
    } 
    else if (strcmp(choice, "log") == 0) {
        fprintf(gitignore, "*.log\n*.out\n*.err\n");
    } 
    else {
        printf("Invalid choice. Please type 'nodejs', 'env', or 'log'.\n");
        fclose(gitignore);
        return;
    }
    
    // Close the file after writing
    fclose(gitignore);
    printf(".gitignore file has been created.\n");
}

void make() {
    char projectName[MAX_LEN];
    char fileName[MAX_LEN];
    char compilerName[MAX_LEN];
    char makefileName[MAX_LEN] = "Makefile";
    FILE *makefile;
    
    // Prompt for project name
    printf("Enter the project name: ");
    fgets(projectName, MAX_LEN, stdin);
    projectName[strcspn(projectName, "\n")] = '\0';  // Remove newline character

    // Prompt for file name including extension
    printf("Enter the filename (with extension, e.g., main.c): ");
    fgets(fileName, MAX_LEN, stdin);
    fileName[strcspn(fileName, "\n")] = '\0';  // Remove newline character

    // Prompt for compiler name
    printf("Enter the compiler name (e.g., gcc, g++, clang): ");
    fgets(compilerName, MAX_LEN, stdin);
    compilerName[strcspn(compilerName, "\n")] = '\0';  // Remove newline character

    // Create a Makefile
    makefile = fopen(makefileName, "w");
    if (makefile == NULL) {
        perror("Error opening Makefile");
        return;
    }

    // Write the Makefile content
    fprintf(makefile, "# Makefile for project: %s\n", projectName);
    fprintf(makefile, "CC = %s\n", compilerName);
    fprintf(makefile, "CFLAGS = -Wall -g\n");  // Default flags; can be adjusted
    fprintf(makefile, "OBJ = %s.o\n", fileName);  // Object file name from the source file

    // Target to compile the program
    fprintf(makefile, "\n%s: $(OBJ)\n", projectName);
    fprintf(makefile, "\t$(CC) $(OBJ) -o %s\n", projectName);

    // Target to compile the .c file to .o
    fprintf(makefile, "\n$(OBJ): %s\n", fileName);
    fprintf(makefile, "\t$(CC) $(CFLAGS) -c %s\n", fileName);

    // Clean target
    fprintf(makefile, "\nclean:\n");
    fprintf(makefile, "\trm -f $(OBJ) %s\n", projectName);

    // Close the Makefile
    fclose(makefile);
    printf("Makefile generated successfully.\n");

    // Run the makefile using system()
    printf("Running 'make' command...\n");
    if (system("make") != 0) {
        printf("Error: make command failed.\n");
    } else {
        printf("Make completed successfully.\n");
    }
}

// Function to list all deleted files (in the recycle bin)
void list_deleted_files() {
    DIR *dir = opendir(RECYCLE_BIN);
    if (dir == NULL) {
        perror("Error opening recycle bin");
        return;
    }

    struct dirent *entry;
    printf("Deleted files in the Recycle Bin:\n");
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {  // Ignore "." and ".."
            printf("- %s\n", entry->d_name);
        }
    }
    closedir(dir);
}

// Function to recover a file from the recycle bin
void recover_file(const char *filename) {
    char old_path[MAX_FILENAME_LEN], new_path[MAX_FILENAME_LEN];
    struct stat st;

    // Construct the full path of the file in the recycle bin
    snprintf(old_path, sizeof(old_path), "%s/%s", RECYCLE_BIN, filename);

    // Check if the file exists in the recycle bin
    if (stat(old_path, &st) != 0) {
        perror("File not found in recycle bin");
        return;
    }

    // Ask the user for the destination path to recover to
    printf("Enter the destination path to recover '%s': ", filename);
    char dest_path[MAX_FILENAME_LEN];
    fgets(dest_path, sizeof(dest_path), stdin);
    dest_path[strcspn(dest_path, "\n")] = '\0';  // Remove newline character

    // Construct the destination path
    snprintf(new_path, sizeof(new_path), "%s/%s", dest_path, filename);

    // Recover the file by renaming (moving) it
    if (rename(old_path, new_path) == 0) {
        printf("File '%s' successfully recovered to '%s'.\n", filename, new_path);
    } else {
        perror("Error recovering the file");
    }
}

// Main function for handling the recycle bin logic
void recycle_bin() {
    char command[512];
    while (1) {
        // Show deleted files
        list_deleted_files();

        printf("\nEnter a command (e.g., 'recover <filename>') or 'exit' to quit: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';  // Remove newline character

        if (strncmp(command, "recover ", 8) == 0) {
            // Extract the filename from the command
            char filename[MAX_FILENAME_LEN];
            sscanf(command + 8, "%s", filename);

            // Recover the file
            recover_file(filename);
        } else {
            printf("Invalid command. Try 'recover <filename>' or 'exit'.\n");
        }
    }
}

void versionf() {
    FILE *file = fopen("version.txtmax", "w");
    
    if (file == NULL) {
        printf("Error creating file!\n");
        return;
    }

    fprintf(file, "Name: txtmax\n");
    fprintf(file, "Size: around 200 KB\n");
    fprintf(file, "Version: 13.8.15\n");
    fprintf(file, "Maintainer: Calestial Ashley\n");

    fclose(file);
}

void localhost() {
    char framework[20];
    char filename[100];
    
    printf("Choose framework (flask/pythonhttp): ");
    scanf("%19s", framework);

    if (strcmp(framework, "flask") == 0) {
        printf("Enter the filename (including extension, e.g., app.py): ");
        scanf("%99s", filename);

        // Construct command
        char command[150];
        snprintf(command, sizeof(command), "python %s", filename);

        // Execute command
        printf("Running: %s\n", command);
        system(command);
    } 
    else if (strcmp(framework, "pythonhttp") == 0) {
        printf("Starting Python HTTP server on port 8080...\n");
        system("python -m http.server 8080");
    } 
    else {
        printf("Invalid framework selection!\n");
    }
}

void createEnvFile() {
    char db_name[100], db_user[100], db_password[100], db_host[100];
    char api_name[100], api_secret[100], debug_choice;
    int db_port, app_port;

    // Prompt for Database Details
    printf("Enter Database Name: ");
    scanf("%99s", db_name);

    printf("Enter Database User: ");
    scanf("%99s", db_user);

    printf("Enter Database Password: ");
    scanf("%99s", db_password);

    printf("Enter Database Host: ");
    scanf("%99s", db_host);

    printf("Enter Database Port: ");
    scanf("%d", &db_port);

    // Prompt for API Details
    printf("Enter API Name: ");
    scanf("%99s", api_name);

    printf("Enter API Secret: ");
    scanf("%99s", api_secret);

    // Prompt for Debug Mode
    printf("Is Debug Mode? (y/n): ");
    scanf(" %c", &debug_choice);

    // Prompt for Application Port
    printf("Enter Application Port: ");
    scanf("%d", &app_port);

    // Open .env file for writing
    FILE *envFile = fopen(".env", "w");
    if (envFile == NULL) {
        perror("Error opening file");
        return;
    }

    // Write environment variables to file
    fprintf(envFile, "DB_NAME=%s\n", db_name);
    fprintf(envFile, "DB_USER=%s\n", db_user);
    fprintf(envFile, "DB_PASSWORD=%s\n", db_password);
    fprintf(envFile, "DB_HOST=%s\n", db_host);
    fprintf(envFile, "DB_PORT=%d\n", db_port);
    fprintf(envFile, "API_NAME=%s\n", api_name);
    fprintf(envFile, "API_SECRET=%s\n", api_secret);
    fprintf(envFile, "DEBUG_MODE=%s\n", (debug_choice == 'y' || debug_choice == 'Y') ? "true" : "false");
    fprintf(envFile, "APP_PORT=%d\n", app_port);

    // Close the file
    fclose(envFile);

    printf(".env file created successfully!\n");
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

    printf("       copy\n");
    printf("           Copy Single or Multiple Files to an Folder\n\n");

    printf("       movef\n");
    printf("           Move Single or Multiple Files to an folder\n\n");
    
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

    printf("       make\n");
    printf("           Build an Test an Project with make.\n\n");

    printf("       gradle\n");
    printf("           Build and Test an Java Project with Gradle.\n\n");

    printf("       dotnet\n");
    printf("           Supports .NET Framework.\n\n");

    printf("       recycle\n");
    printf("           Recover your Deleted files.\n\n");

    printf("       localhost\n");
    printf("           Start your Flask and Python App on Localhost.\n\n");

    printf("       environment\n");
    printf("           Store your API Secrets.\n\n");

    printf("       ignore");
    printf("           Create an .gitignore file.\n\n");

    printf("       sqlite\n");
    printf("           Work with SQLite Database.\n\n");

    printf("       openai\n");
    printf("           Integration with OpenAI API Key.\n\n");

    printf("       size\n");
    printf("           Retrieve File Size.\n\n");

    printf("       multiplexer\n");
    printf("            Integration with Tmux.\n\n");

    printf("       benchmark\n");
    printf("             Shows Execution time and CPU Usage and Additional things like System CPU Time and Total CPU Time and Max Memory usage and Page Faults and Context Switches.\n\n");

    printf("       deploy\n");
    printf("           Deploy your code to Heroku CLI.\n\n");
    
    printf("       markdown\n");
    printf("           Create Markdown Files.\n\n");
    
    printf("       exit\n");
    printf("           Exit the Txtmax editor.\n\n");
  
    printf("                      FEATURES\n");
    printf("       - Syntax Highlighting for Programming Languages\n");
    printf("       - Run Code Quickly with Integrated Compilers and Interpreters\n");
    printf("       - Git Integration for Version Control and Commit Management\n");
    printf("       - Support for Over 80 Programming Languages\n");
    printf("       - Installation of Python and Node.js Packages and many more!\n\n");

    printf("USAGE\n");
    printf("       To start using Txtmax:\n");
    printf("         1. Clone the repository:\n");
    printf("              git clone https://github.com/Calestial2/Txtmax.git\n");
    printf("           2. Navigate to the directory:\n");
    printf("              cd Txtmax\n");
    printf("           3. Compile the code:\n");
    printf("              gcc txtmax.c -o txtmax\n");
    printf("           4. Run Txtmax:\n");
    printf("              ./txtmax\n\n");

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
    printf("  movef                   Move Single or Multiple Files to an Folder.\n");
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
    printf("  copy                    Copy Single or Multiple files to an Folder\n");
    printf("  make                    Build and Test a Project with Make\n");
    printf("  gradle                  Build and Test an Java Project with Gradle\n");
    printf("  dotnet                  Supports .NET Framework\n");
    printf("  recycle                 Recover your all Deleted files\n");
    printf("  localhost               Start your Flask and Python App on localhost\n");
    printf("  environment             Store your API Secrets\n");
    printf("  ignore                  Create a .gitignore file\n");
    printf("  sqlite                  Work with SQLite Database\n");
    printf("  openai                  Integration with OpenAI API Key\n");
    printf("  size                    Retrieval File Size,\n");
    printf("  multiplexer             Integration with Tmux.\n");
    printf("  benchmark               Shows Execution time and CPU Usage and Additional things like System CPU Time and Total CPU Time and Max Memory usage and Page Faults and Context Switches.\n");
    printf("  markdown                Create Markdown Files\n");
    printf("  deploy                  Deploy your code to Heroku CLI\n");
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

    printf("Welcome to Txtmax, a Powerful Text Editor and IDE for Linux and Unix-like Systems\n\n");
    printf("* Documentation: https://github.com/Calestial2/Txtmax/blob/main/README.md\n");
    printf("* Access Manual: `man txtmax`\n");
    printf("* Code: https://github.com/Calestial2/Txtmax/tree/main/src\n");

    while (1) {
        printf("\n~/txtmax ");
        fgets(command, MAX_INPUT_SIZE, stdin);
        command[strcspn(command, "\n")] = 0;  // Remove the newline character from input

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
        } else if (strcmp(command, "movef") == 0) {
            movef();
        } else if (strcmp(command, "copy") == 0) {
            copy_files_to_folder();
        } else if (strcmp(command, "make") == 0) {
            make();
        } else if (strcmp(command, "gradle") == 0) {
            generateGradleScript();
        } else if (strcmp(command, "dotnet") == 0) {
            create_dotnet_project();
        } else if (strcmp(command, "recycle") == 0) {
            recycle_bin();
        } else if (strcmp(command, "localhost") == 0) {
            localhost();
        } else if (strcmp(command, "version") == 0) {
            versionf();
        } else if (strcmp(command, "environment") == 0) {
            createEnvFile();
        } else if (strcmp(command, "ignore") == 0) {
            ignore();
        } else if (strcmp(command, "sqlite") == 0) {
            sqlite();
        } else if (strcmp(command, "openai") == 0) {
            openai();
        } else if (strcmp(command, "auto_completion") == 0) {
            auto_completion();
        } else if (strcmp(command, "notebook") == 0) {
            txtmaxnote();
        } else if (strcmp(command, "size") == 0) {
            getFileSize();
        } else if (strcmp(command, "multiplexer") == 0) {
            tmux_integration();
        } else if (strcmp(command, "benchmark") == 0) {
            benchmark();
        } else if (strcmp(command, "security") == 0) {
            security();
        } else if (strcmp(command, "markdown") == 0) {
            markdown();
        } else if (strcmp(command, "deploy") == 0) {
            deploy();
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
