# minishell

## Final grade 100/100
  
## Description
  Group with [cquintana001](https://github.com/Cquintana001) – about 210 hours

The objective of this project is for you to create a simple shell. Yes, your little bash or zsh. You will learn a lot about processes and file descriptors.

## Table of Contents

- [Installation](#installation)
- [Mandatory](#Mandatory)

## Installation

Clone this repository using the following command.

    git clone https://github.com/andonimarz/minishell.git

## Mandatory

Your shell should:

• Not interpret unclosed quotes or unspecified special characters like \ or ;.

• Not use more than one global variable, think about it and be ready to explain why you do it.

• Show a prompt when waiting for a new command.

• Have a working History.

• Search and launch the right executable (based on the PATH variable or by using relative or absolute path)

• It must implement the builtins:

      ◦ echo with option -n

      ◦ cd with only a relative or absolute path

      ◦ pwd with no options

      ◦ export with no options

      ◦ unset with no options

      ◦ env with no options or arguments

      ◦ exit with no options

• ’ inhibit all interpretation of a sequence of characters.

• " inhibit all interpretation of a sequence of characters except for $.

• Redirections:

      ◦ < should redirect input.

      ◦ > should redirect output.

      ◦ “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!

      ◦ “>>” should redirect output with append mode.

• Pipes | The output of each command in the pipeline is connected via a pipe to the input of the next command.

• Environment variables ($ followed by characters) should expand to their values.

• $? should expand to the exit status of the most recently executed foreground pipeline.

• ctrl-C ctrl-D ctrl-\ should work like in bash.

• When interactive:

      ◦ ctrl-C print a new prompt on a newline.

      ◦ ctrl-D exit the shell.

      ◦ ctrl-\ do nothing.

readline function can produce some leak you don’t need to fix this.

But beware your own code should not produce leaks.

You should limit yourself to the subject description.

Anything not asked is not required.

For every point, if you have any doubt take bash as a reference.

