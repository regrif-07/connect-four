#include <io_utility.h>

#include <stdio.h>
#include <stdlib.h>

#include "../../connect_four_core/include/board.h"

void startMainMenu();
void startSavesMenu();

int main(void)
{
    startMainMenu();

    printf("\nThank you for playing Connect Four!");

    return EXIT_SUCCESS;
}

void startMainMenu()
{
    while (true)
    {
        printf("1) Play a new game\n"
               "2) Load already saved game\n"
               "3) Exit the game\n");

        switch (loopReadInteger("> "))
        {
        case 1:
            // some test code to see the work of board functionality
            Board* board = allocateEmptyBoard(nullptr);
            setCellAt(board, 5, 4, CROSS, nullptr);
            setCellAt(board, 4, 4, CROSS, nullptr);
            setCellAt(board, 3, 4, CROSS, nullptr);
            setCellAt(board, 5, 1, ZERO, nullptr);
            setCellAt(board, 4, 1, ZERO, nullptr);
            setCellAt(board, 5, 0, ZERO, nullptr);
            displayBoard(board);
            free(board);

            break;

        case 2:
            printf("\n");
            startSavesMenu();
            break;

        case 3:
            return;

        default:
            printf("Invalid menu selection. Try again.\n");
        }

        printf("\n");
    }
}

void startSavesMenu()
{
    while (true)
    {
        printf("1) List all saved games\n"
               "2) List all saved games for a particular player\n"
               "3) Show the board of one of the saved games\n"
               "4) Load a game\n"
               "5) Return to main menu\n");

        switch (loopReadInteger("> "))
        {
        case 1:
            printf("Listing all saved games...\n");
            break;

        case 2:
            printf("Listing all saved games for a particular player...\n");
            break;

        case 3:
            printf("Showing the board of one of the saved games...\n");
            break;

        case 4:
            printf("Loading the game...\n");
            break;

        case 5:
            return;

        default:
            printf("Invalid menu selection. Try again.\n");
        }

        printf("\n");
    }
}