# 🐚 Minishell

A custom shell implementation developed as part of the **42 Network** curriculum.  
This project recreates a simplified version of a Unix shell, handling command parsing, job control, and execution.

---

## 👥 Team

- [**mouchtach**](https://github.com/mouchtach) — Execution engine: forking, piping, redirection, environment handling, built-in commands.  
- [**azh4rrr**](https://github.com/azh4rrr) — Lexer, parser, and syntax validation.

---

## 🚀 Features

- ✅ Built-in commands: `cd`, `echo`, `env`, `export`, `unset`, `pwd`, `exit`
- ✅ External command execution using `$PATH`
- ✅ Pipes: `ls | grep txt | wc -l`
- ✅ Redirections: `>`, `<`, `>>`, `<<` (heredoc)
- ✅ Environment variable expansion: `$HOME`, `$PATH`, etc.
- ✅ Quoting support: handles `'single'` and `"double"` quotes
- ✅ Signal handling: `Ctrl+C`, `Ctrl+\`
- ✅ Error messages matching `bash` behavior
- ✅ Memory safe: no leaks (checked with `valgrind`)

---

## 🛠️ Build & Run

```bash
make
./minishell
````
---

## 🗂 Project Structure

```
minishell/
├── builtin/             # Built-in shell command implementations
│   ├── cd.c
│   ├── echo.c
│   └── ...
├── execution/           # Execution logic (fork, execve, redirections, pipes)
│   ├── execution.c
│   ├── redirection.c
│   └── ...
├── parsing/             # Lexer, parser, syntax validator
│   ├── lexer.c
│   ├── parser.c
│   └── ...
├── utils/               # Utility functions (e.g., string and memory helpers)
│   ├── string_utils.c
│   └── ...
├── minishell.c          # Entry point
├── minishell.h          # Header file
└── Makefile
```

---

## 📚 42 Norm & Compliance

* ✅ No use of `system()`
* ✅ Strict memory management (verified with `valgrind`)
* ✅ Norminette-compliant code
* ✅ Proper signal handling and interactive loop behavior
* ✅ Mimics `bash` behavior (as required)

---

