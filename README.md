# crab
## The crab shell

# Building
    To run the crab shell from within the crab directory type the following
    commands (each followed by 'enter') in the command line:
    
    make clean
    make

# Running
    To run the shell once it has been built enter the command from within the
    crab directory:

    ./bin/crab
    
# Implemented Commands
    cd <directory name>                   -- changes current directory to <directory name>
    exit (or quit)                        -- exits the crab shell
    autocomplete (press tab)              -- press tab when typing a directory name to have the shell auto-complete it
    command history (up or down arrowkey) -- navigate through most recently used commands
    
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
 
