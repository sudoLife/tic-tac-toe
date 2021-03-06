#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Constants
#define DIM_MIN 3
#define DIM_MAX 15
#define COLOR "\033[32m"

// Board
char board[DIM_MAX][DIM_MAX];

// Current player
char state = 'X';

// Dimensions
int d;


// Prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
int place(int tile_x, int tile_y);
int won(void);

int main()
{
	printf("Enter the number of dimension: ");
	scanf("%d", &d);
    // Ensure valid dimensions
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
			   DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // Greet user with instructions
    greet();

    // Initialize the board
    init();

    // Accept moves until game is won
    while (1)
    {
        // Clear the screen
        clear();

        // Draw the current state of the board
        draw();

        // Check for win

        // Prompt for coordinates
		int tile_x,  tile_y;
        printf("X coordinate: ");
		scanf("%d", &tile_x);

		printf("Y coordinate: ");
		scanf("%d", &tile_y);
 
 
        // Quit if user inputs 0 (for testing)
        if (tile_x == 0)
        {
            break;
        }

        // Place if possible, else report illegality
        if (place(tile_x, tile_y))
        {
            printf("\nIllegal move.\n");
            usleep(2000);
        }

		if (won())
        {
            printf("VIIIIIIICTOOOORYY!\n");
            break;
        }

        // Sleep thread for animation's sake
        usleep(2000);
    }

    // Success
    return 0;
}

// Clears screen using ANSI escape sequences
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

// Greets player
void greet(void)
{
    clear();
    printf("WELCOME TO TIC-TAC-TOE!\n");
    usleep(2000);
}

void init(void)
{
	int i, j;

	for (i = 0; i < d; ++i)
	{
		for (j = 0; j < d; j++)
		{
			board[i][j] = ' ';
		}
	}
}

// Prints the board in its current state
void draw(void)
{
    int i, j;

	for (j = 0; j < d; ++j)
	{
		printf("-----");
	}
	
	for (i = 0; i < d; ++i)
	{		
		printf("\n|");
		for (j = 0; j < d; ++j)
		{
			printf(" %c |", board[i][j]);
		}

		printf("\n");
		
		for (j = 0; j < d; ++j)
		{
			printf("-----");
		}

		printf("\n");
	}
}

int place(int tile_x, int tile_y)
{
	if (tile_x > d || tile_y > d || board[tile_y - 1][tile_x - 1] == state)
	{
		return 1;
	}

	board[tile_y - 1][tile_x - 1] = state;
	

	return 0;
	
}

int won(void)
{
    int i, j;

	int won;
	// Check horizontally
	for (i = 0; i < d; ++i)
	{
		won = 1;
		for (j = 0; j < d; ++j)
		{
			if (board[i][j] != state)
			{
				won = 0;
			}
		}
		if (won)
		{
			return 1;
		}

	}

	// Checking vertically
	for (i = 0; i < d; ++i)
	{
		won = 1;
		for (j = 0; j < d; ++j)
		{
			if (board[j][i] != state)
			{
				won = 0;
			}
		}

		if (won)
		{
			return 1;
		}
	}
	
	
	won = 1;
	for (i = 0; i < d; ++i)
	{
		if (board[i][i] != state)
		{
			won = 0;
			break;
		}
	}
	
	if (won)
	{
		return 1;
	}
	
	won = 1;
	for (i = 0, j = d - 1; i < d && j > 0; ++i, --j)
	{
		if (board[i][j] != state)
		{
			won = 0;
			break;
		}
	}
	
	if (won)
	{
		return 1;
	}

	state = state == 'X' ? 'O' : 'X';
	
    return 0;
}
