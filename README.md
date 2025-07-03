
## 🐚 Minishell 

> A custom shell implementation as part of the **42 Network** curriculum.
> The goal is to recreate a simplified version of a Unix shell with essential job control, parsing, and execution logic.

---

### 📦 Versions Included

This repository contains two versions of the Minishell project:

#### 🔹 Version 1

* Developed with [azh4rrr](https://github.com/azh4rrr)
* **azh4rrr**: Parser, lexer, syntax validation
* **mouchtach**: Execution engine (forking, piping, redirection, environment)

#### 🔸 Version 2

* Developed with [qwww-12](https://github.com/qwww-12)
* **qwww-12**: Parser, lexer, syntax validation
* **mouchtach**: Execution engine (forking, piping, redirection, environment)

---

### 🚀 Features

* Built-in commands: `cd`, `echo`, `env`, `export`, `unset`, `pwd`, `exit`
* External command execution using PATH
* Piping: `ls | grep txt | wc -l`
* Redirections: `>`, `<`, `>>`, `<<` (heredoc)
* Environment variable expansion: `$HOME`, `$PATH`
* Quoting: single and double quotes handling
* Signal handling: `Ctrl+C`, `Ctrl+\`
* Error handling (syntax and system-level)

---

### 🛠️ Build & Run

```bash
cd minishell_v1   # or minishell_v2
make
./minishell
```

> ⚠️ **Note:** Compatible with Unix-based systems (macOS/Linux).
> Requires `bash` behavior emulation and strict memory management (no leaks allowed).

---

### 🗂 Project Structure

```bash
minishell_v1/
├── builtin/             # Built-in shell commands
│   ├── cd.c
│   ├── echo.c
│   └── ...
├── execution/           # Execution logic (fork, execve, pipes)
│   ├── execution.c
│   ├── redirection.c
│   └── ...
├── parsing/             # Lexer, parser, syntax checking
│   ├── lexer.c
│   ├── parser.c
│   └── ...
├── utils/               # Utility functions (string, memory)
│   ├── string_utils.c
│   └── ...
├── minishell.c          # Entry point
├── minishell.h          # Header file
└── Makefile
```

> V2 has similar structure with improved file separation and abstraction.

---

### 📸 Screenshots

> 📝 **Note**: Screenshots or GIFs can be added here to demonstrate terminal usage.
> You can record usage with tools like `asciinema`, `peek`, or simply take static terminal screenshots.

---

### 🤝 Contributors

| Version | Author                                    | Role                  |
| ------- | ----------------------------------------- | --------------------- |
| v1/v2   | [mouchtach](https://github.com/mouchtach) | Execution & structure |
| v1      | [azh4rrr](https://github.com/azh4rrr)     | Parsing & tokens      |
| v2      | [qwww-12](https://github.com/qwww-12)     | Parsing & tokens      |

---

### 📚 42 Norm & Rules Compliance

* No use of `system()`
* Proper memory handling (checked via `valgrind`)
* Norminette-compliant code style
* Signal safety and interactive shell behavior
* Reproduces `bash`-like behavior (within limits)

