# crab
## The crab shell

# Building and installing
To build and install crab, run the following

    make clean
    sudo make install

This will install the crab shell and its associated manpages.

To build the crab shell without installing, use the following

    make clean
    make

The shell will be located in bin/crab

Once crab is installed, it can be uninstalled with

    sudo make uninstall

# Running
Once crab is installed, you can run it with

    crab

# Implemented Commands

| Feature                  | Description                                                               |
|:-------------------------|:--------------------------------------------------------------------------|
| cd <directory name>      | Changes current directory to <directory name>                             |
| exit (or quit)           | Exits the crab shell                                                      |
| autocomplete (press tab) | Press tab when typing a directory name to have the shell auto-complete it |
| history <# of cmds>      | Displays a list of recently used commands                                 |
| pwd                      | Displays the path to the current directory                                |
| colour <colour>          | Switches the colour of the text in the shell                              |
| ad <options>             | Create and navigate through aliases. for detailed usage instructions, see the # Alias section |

# Alias
Set an alias with ad (see commands below) and cd to that alias

| Command         | Effect                                                     |
|:----------------|:-----------------------------------------------------------|
| ad              | 0 args - sets alias [prev] equal to current directory      |
| ad [name]       | 1 args - sets alias [name] equal to current directory      |
| ad [name] [dir] | 2 args - sets alias [name] equal to [dir]                  |
| ad print        | print all aliases currently assigned                       |
| ad findn [name] | print directory associated with [name]                     |
| ad findd [dir]  | print names associated with [dir]                          |
| ad save         | save all alias to file to be used in other sessions        |
| ad deletelog    | delete alias.log and its contents                          |
| ad reset        | reset all alias for this current session                   |
| cd [name]       | change directory to the directory corresponding to [name]  |

# Colour
To change the colour of the input/output text use the following command:

    colour <colour name>

Below are the valid options for &lt;colour name&gt;:

    reset (default colour)
    red
    magenta
    yellow
    green
    blue
    cyan
    white


# History
Whenever you input a command, it will be stored for later access.

History will be stored in a file called cmdhist.txt so that it may persist through sessions.

Please note that the .txt file will be stored in whichever directory you run the crab shell from. If you switch directories and run the shell from a different one than you normally use, you will not have access to your full command history, and the two directories will contain separate cmdhist.txt files.

After you type a history command, a list of commands will be displayed.

Index numbers will be displayed next to the commands. If your very next input is a valid index number (within the range of displayed indices), the corresponding command will be run.

To access history,

| Command                 | Effect                                                             |
|:------------------------|:-------------------------------------------------------------------|
| history                 | If no argument is given, 10 commands will be displayed by default  |
| history [# of commands] | If an integer argument is specified, that number of commands will be displayed. |

# Pipes
Pipes can be used to take the output of one command and use it as the input of another command.
Crab shell supports any number of piped commands

Example:

    ls | grep test
