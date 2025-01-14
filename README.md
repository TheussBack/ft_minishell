---

# Minishell

## Introduction

Minishell is a project where you will build your own shell, similar to bash, from scratch. This project helps you understand and interact with low-level concepts like processes, file descriptors, and memory management. It aims to simulate the behavior of a real shell by supporting command execution, redirections, pipes, environment variables, and more.

## Features

- **Command Prompt**: Displays a prompt waiting for user input.
- **Command History**: Supports storing and retrieving previous commands.
- **Command Execution**: Launches executables based on the user's input (via PATH or relative/absolute paths).
- **Signal Handling**: Implements proper signal handling to avoid issues with global variables.
- **Quotes Handling**: Supports single and double quotes, preventing the shell from interpreting metacharacters inside the quotes.
- **Redirections**: Handles standard input/output redirection and append redirection.
- **Pipes**: Supports piping between commands, connecting output of one command to input of another.
- **Environment Variables**: Expands `$VAR` to the value of the environment variable.
- **Special Characters Handling**: Supports special characters like `$?` to get the exit status of the last command.
- **Built-in Commands**:
  - `echo` (with the `-n` option)
  - `cd` (relative or absolute paths only)
  - `pwd` (no options)
  - `export` (no options)
  - `unset` (no options)
  - `env` (no options or arguments)
  - `exit` (no options)

### Interactive Mode:
- **ctrl-C**: Displays a new prompt.
- **ctrl-D**: Exits the shell.
- **ctrl-\**: Does nothing.

## Requirements

- **Language**: C
- **External Functions**: `readline`, `rl_clear_history`, `fork`, `execve`, `dup`, `pipe`, `getcwd`, `chdir`, and more.
- **Libft**: You are allowed to use your own `libft` library.

## Mandatory Part

In the mandatory part of the project, your shell must:
- Display a prompt when waiting for commands.
- Handle environment variables (like `$HOME`, `$PATH`, etc.).
- Implement basic file redirection (`<`, `>`, `<<`, `>>`).
- Support piping between commands (`|`).
- Handle special characters like `$?` for the exit status.
- Implement basic signal handling.
- Support interactive features like ctrl-C, ctrl-D, and ctrl-\.

Your shell must support a functional history, execute commands in background or foreground, and manage the terminal’s input/output correctly.

### Example Usage

```bash
$ ./minishell
> echo Hello, World!
Hello, World!
> pwd
/home/user
> cd /home/user/another-directory
> echo $PWD
/home/user/another-directory
> exit
```

## Bonus Part

The bonus part will only be evaluated if the mandatory part is **perfect**. The bonus includes:
- **Logical Operators**: Support for `&&` (AND) and `||` (OR) with parentheses for command grouping and priority.
- **Wildcard Expansion**: Implement wildcard (`*`) expansion for the current directory.

If you complete the mandatory part correctly, you can further enhance your shell by adding these bonus features for extra points.

## How to Build and Run

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/minishell.git
   cd minishell
   ```

2. Compile the project:
   ```bash
   make
   ```

3. Run the shell:
   ```bash
   ./minishell
   ```

## Testing

- Create test cases for each feature, including command execution, redirection, piping, and built-ins.
- You can use the provided tests or create your own to verify that the shell behaves as expected.

## License

This project is licensed under the MIT License.
