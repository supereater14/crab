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
    command history (up or down arrowkey) -- navigate through most recently used commands
    ad                                    -- Set alias for directories and cd to that alias (see ad help)

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
    
# Alias
    Set an alias with ad (see commands below) and cd to that alias
    
    ad help - print detailed description of each command.
	ad - (0 args) - sets alias [prev] equal to current directory.
	ad [name]- (1 args) - sets alias [name] equal to current directory.
	ad [name] [dir] - (2 args) - sets alias [name] equal to [dir].
	ad print - print all alias.
    ad findn [name] - print directory associated with [name].
	ad findd [dir] - print names associated with [dir].
	ad reset - reset all alias for this current session.
    
	cd [name] - change directory to the directory corresponding to [name].
