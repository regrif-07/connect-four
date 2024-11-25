#include <assert.h>
#include <game_context.h>
#include <game_functionality.h>
#include <io_utility.h>
#include <save_system.h>

#include <stdio.h>
#include <stdlib.h>

// menus
void startMainMenu();
void startSavesMenu();

// menu option handlers
void playNewGameMenuOption();
void loadGameMenuOption();
void showBoardOfSavedGameOption();

// others
void startGameWrapper(GameContext* gameContext);
GameContext* loadGameByUserId(const long long saveId);

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
        printf("=== MAIN MENU ===\n"
               "1) Play a new game\n"
               "2) Load already saved game\n"
               "3) Exit the game\n");

        switch (loopReadInteger("> "))
        {
        case 1:
            printf("\n");
            playNewGameMenuOption();
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
        printf("=== SAVES MENU ===\n"
               "1) List all saved games\n"
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
            printf("\n");
            showBoardOfSavedGameOption();
            break;

        case 4:
            printf("\n");
            loadGameMenuOption();
            break;

        case 5:
            return;

        default:
            printf("Invalid menu selection. Try again.\n");
        }

        printf("\n");
    }
}

void playNewGameMenuOption()
{
    ErrorCode errorCode;
    GameContext* gameContext = createNewGameContext(&errorCode);
    if (gameContext)
    {
        startGameWrapper(gameContext);
        freeGameContext(gameContext);
    }
    else
    {
        printf("Unexpected error occurred while trying to create a new game.\n");
        exit(EXIT_FAILURE);
    }
}

void loadGameMenuOption()
{
    GameContext* loadedGame = loadGameByUserId(loopReadInteger("Enter the id of the save to load: "));
    if (!loadedGame)
    {
        return;
    }

    startGameWrapper(loadedGame);
    freeGameContext(loadedGame);
}

void showBoardOfSavedGameOption()
{
    GameContext* loadedGame = loadGameByUserId(loopReadInteger("Enter the id of the save to show: "));
    if (!loadedGame)
    {
        return;
    }

    displayGameHeader(loadedGame);
    freeGameContext(loadedGame);
}

void startGameWrapper(GameContext* gameContext)
{
    printf("\n");
    startGame(gameContext, nullptr);
    printf("\n");

    displayBoard(gameContext->board); // display the board for the last time
    switch (gameContext->gameState)
    {
    case CROSS_WIN:
        printf("%s ('X') victory!\n", gameContext->crossPlayer.name);
        break;

    case ZERO_WIN:
        printf("%s ('O') victory!\n", gameContext->zeroPlayer.name);
        break;

    case DRAW:
        printf("It's a draw!\n");
        break;

    default:
        assert(false && "unhandled game state");
    }
}

GameContext* loadGameByUserId(const long long saveId)
{
    ErrorCode errorCode;
    GameContext* loadedGame = loadGameBySaveId(saveId, &errorCode);
    if (!loadedGame)
    {
        if (errorCode && errorCode != NO_ERROR)
        {
            printf("Unexpected error occurred while trying to load the specified save.");
            exit(EXIT_FAILURE);
        }

        printf("Save with id %lld was not found.\n", saveId);
        return nullptr;
    }

    return loadedGame;
}