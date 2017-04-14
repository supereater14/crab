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
    
    To run the shell from within the crab directory and display a help message:
    
    ./bin/crab help

# Implemented Commands
    cd <directory name>                   -- changes current directory to <directory name>
    exit (or quit)                        -- exits the crab shell
    autocomplete (press tab)              -- press tab when typing a directory name to have the shell auto-complete it
    history <# of cmds>                   -- displays a list of recently used commands
    pwd                                   -- displays the path to the current directory
    colour <colour>                       -- switches the colour of the text in the shell
    ad <options>                          -- Create and navigate through aliases. for detailed usage instructions, see the # Alias section
    
    
# Alias
    Set an alias with ad (see commands below) and cd to that alias
    ad - 0 args - sets alias [prev] equal to current directory
    ad [name]- 1 args - sets alias [name] equal to current directory
    ad [name] [dir] - 2 args - sets alias [name] equal to [dir]
    ad print - print all alias
    ad findn [name] - print directory associated with [name]
    ad findd [dir] - print names associated with [dir]
    ad save - save all alias to file to be used in other sessions
    ad deletelog - delete alias.log and its contents
    ad reset - reset all alias for this current session
    cd [name] - change directory to the directory corresponding to [name]

# Colour
    To change the colour of the input/output text use the following command:
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


# History
    Whenever you input a command, it will be stored for later access. History will be stored in a file called cmdhist.txt so that it may persist through sessions.
    Please note that the .txt file will be stored in whichever directory you run the crab shell from. If you switch directories and run the shell from a different one than you normally use, you will not have access to your full command history, and the two directories will contain separate cmdhist.txt files.
    After you type a history command, a list of commands will be displayed. Index numbers will be displayed next to the commands. If your very next input is a valid index number (within the range of displayed indices), the corresponding command will be ran.
    To access history
    history - If no argument is given, 10 commands will be displayed by default
    history [# of commands] - If an integer argument is specified, that number of commands will be displayed.
   
# Pipes
    Pipes can be used to take the output of one command and use it as the input of another command.
    This shell supports any number of piped commands
    Example: ls | grep test
