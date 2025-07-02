
# 🐚 minishell

**minishell** is a simplified UNIX shell built as part of the **42 Network** curriculum.
It reproduces basic functionalities of Bash, allowing command execution, pipes, redirections, environment handling, and more.

---

## ⚙️ Features

* 📥 **Prompt**: Custom shell prompt with input parsing
* 🧠 **Built-in Commands**:

  * `cd`, `echo`, `env`, `exit`, `export`, `unset`, `pwd`
* ⚙️ **Execution**:

  * Binary execution with `PATH` lookup
  * Pipelines (`|`)
  * Redirections: `>`, `<`, `>>`, `<<` (heredoc)
* 🌍 **Environment**: Full support for env variable manipulation
* 🧹 **Signal Handling**: Proper handling of `SIGINT`, `SIGQUIT`, etc.
* 🐛 Error messages for invalid syntax, command not found, etc.

---

## 🚀 Build & Run

### 1. Clone & Build

```bash
git clone https://github.com/your-username/minishell.git
cd minishell
make
```

### 2. Launch the Shell

```bash
./minishell
```

---

## 💻 Example Usage

```bash
$ echo hello | grep h > output.txt
$ cat << EOF
> hello
> world
> EOF
```

---

## 📁 Project Structure

```
minishell/
├── minishell.c            # Main loop
├── minishell.h            # Header declarations
├── builtin/               # Built-in command logic
├── execution/             # Execution, redirection, piping
├── parsing/               # Input parsing and tokenization
├── Makefile
```

---

## 🧠 Notes

* Uses only allowed C functions (no `system`, `printf`, etc.)
* Norm-compliant and adheres to 42 shell subject
* Project focuses on memory management, parsing, and process handling

