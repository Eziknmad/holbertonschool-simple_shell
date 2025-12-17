# Simple Shell

## Description
Simple Shell (`hsh`) is a basic UNIX command line interpreter written in C.  
It replicates core behaviors of `/bin/sh`, allowing users to execute commands
in both interactive and non-interactive modes.

The shell reads commands from standard input, parses them, resolves executable
paths using the `PATH` environment variable, creates child processes, and
executes commands using system calls.

## Features
- Interactive and non-interactive modes
- Executes commands using full paths
- PATH resolution
- Process creation with `fork`
- Program execution with `execve`
- Parent/child synchronization with `wait`
- Proper error handling
- Environment inheritance

## Usage

### Interactive mode
```sh
$ ./hsh
($) /bin/ls
($) exit
