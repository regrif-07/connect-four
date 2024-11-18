#include <game.h>
#include <io_utility.h>

#include <stdio.h>
#include <stdlib.h>

void startMainMenu();
void startSavesMenu();
GameContext* createNewGameContext(ErrorCode* errorCode);

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
            ErrorCode errorCode;
            GameContext* gameContext = createNewGameContext(&errorCode);
            if (errorCode == NO_ERROR)
            {
                startGame(gameContext, &errorCode);

                free(gameContext->crossPlayerName);
                free(gameContext->zeroPlayerName);
                free(gameContext->board);
                free(gameContext);
            }
            else
            {
                printf("Unexpected error occurred while trying to create a new game.\n");
            }

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

GameContext* createNewGameContext(ErrorCode* errorCode)
{
    GameContext* gameContext = allocateNewGameContext(errorCode);
    if (errorCode && *errorCode != NO_ERROR)
    {
        return nullptr;
    }

    printf("\n");
    gameContext->crossPlayerName = readLine("Enter the name of the cross ('X') player: ", true);
    gameContext->zeroPlayerName = readLine("Enter the name of the zero ('O') player: ", true);

    if (errorCode) *errorCode = NO_ERROR;
    return gameContext;
}
