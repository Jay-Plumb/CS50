/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int boardValue = d*d - 1;
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            
            board[i][j] =  boardValue--;
        }
    }
    
    // Swap last two elements if we have odd number of cells (even board dimensions)
    if (d%2 == 0) {
        int temp = board[d-1][d-2];
        board[d-1][d-2] = board[d-1][d-3];
        board[d-1][d-3] = temp;
    }
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            if (board[i][j] == 0) {
                printf(" - ");
            }else {
                printf("%2d ", board[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int tilePositionX = -1;
    int tilePositionY = -1;
    int emptyPositionX = -1;
    int emptyPositionY = -1;
    // Search for tiles position
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            // Found tile
            if (tile == board[i][j]) {
                tilePositionX = i;
                tilePositionY = j;
                // Search neighbours for empty tile - compare all four neighbours but do not if they go past the bounds
                for (int a = -1; a < 2; a++) {
                    for (int b = -1; b < 2; b++) {
                        if ( (a == -1 && b == -1) || (a == -1 && b ==1) || (a == 1 && b == -1) || (a == 1 && b == 1) || (a == 0 && b == 0) ) {
                            // Do not check these cells
                        } else {
                 
                            // make sure we are in the bounds
                            if ( (a + tilePositionX >= 0) && (a + tilePositionX <= d - 1) && (b + tilePositionY >= 0) && (b + tilePositionY <= d-1) ) {
                                // Check for empty cell
                                if (board[a + tilePositionX][b + tilePositionY] == 0) {
                                    emptyPositionX = a + tilePositionX;
                                    emptyPositionY = b + tilePositionY;
                                    printf("empty (%i %i)", emptyPositionX, emptyPositionY);
                                    // Swap selected value with empty space
                                    int temp = board[i][j];
                                    board[i][j] = board[emptyPositionX][emptyPositionY];
                                    board[emptyPositionX][emptyPositionY] = temp;
                                    return true;
                                }
                            } 
                        }
                    }
                }
                
              
            }
        }
    }
 
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int counter = 1;
    int pass = 0;
    // Iterate over the board to check values are in 
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            if (counter == board[i][j]) {
              pass++;
              counter++;
            }else if (counter != board[i][j]) {
                // empty board piece is 0 so check this edge case. make sure it is in bottom right corner also
                if ((board[i][j]) == 0 && (i == d - 1) && (j == d - 1) && (pass == (d*d)-1) ) {
                    return true;
                }
            }
        }
    }
    return false;
}