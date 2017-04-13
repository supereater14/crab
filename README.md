# crab
## The crab shell

# Building
    To run the crab shell from within the crab directory type the following
    commands (each followed by 'enter') in the command line:

    make clean
    make

# Installing
    To install the custom commands man pages so they can be accessed through the 'man' command,
    type the following command (followed by 'enter') in the command line:

    sudo make install

# Running
    To run the shell once it has been built enter the command from within the
    crab directory:

    ./bin/crab

# Implemented Commands
    cd <directory name>                   -- changes current directory to <directory name>
    exit (or quit)                        -- exits the crab shell
    autocomplete (press tab)              -- press tab when typing a directory name to have the shell auto-complete it
    command history <# of cmds>           -- displays a list of recently used commands

# Color
    To change the color of the input/output text use the following command:
    colour <colour name>

    Below are the valid color options (<colour name>):
    reset (default color)
    red
    magenta
    yellow
    green
    blue
    cyan
    white
