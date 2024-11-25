#include <game_context.h>
#include <game_functionality.h>
#include <io_utility.h>
#include <save_system.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// menus
void startMainMenu();
void startSavesMenu();

// menu option handlers
void playNewGameMenuOption();
void loadGameMenuOption();
void showBoardOfSavedGameOption();
void listAllSavedGamesOption();
void listAllSavedGamesParticularPlayerOption();

// others
/// Start the game wrapper that will start the game and manage the player notification about game results.
/// @param gameContext context of the game to start
void startGameWrapper(GameContext* gameContext);

/// Try to load the game using its save's id. Notify the player about the status of operation.
/// @param saveId id of the save to load.
/// @return heap allocated context of the loaded game or nullptr if loading failed.
GameContext* loadGameByIdWrapper(const long long saveId);

int main(void)
{
    startMainMenu();

    printf("\nThank you for playing Connect Four!\n");

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
            printf("\n");
            listAllSavedGamesOption();
            break;

        case 2:
            printf("\n");
            listAllSavedGamesParticularPlayerOption();
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
    GameContext* loadedGame = loadGameByIdWrapper(loopReadInteger("Enter the id of the save to load: "));
    if (!loadedGame)
    {
        return;
    }

    startGameWrapper(loadedGame);
    freeGameContext(loadedGame);
}

void showBoardOfSavedGameOption()
{
    GameContext* loadedGame = loadGameByIdWrapper(loopReadInteger("Enter the id of the save to show: "));
    if (!loadedGame)
    {
        return;
    }

    displayGameHeader(loadedGame);
    freeGameContext(loadedGame);
}

void listAllSavedGamesOption()
{
    listAllSavedGames(DEFAULT_SAVES_FILEPATH);
}

void listAllSavedGamesParticularPlayerOption()
{
    ErrorCode errorCode;

    char* playerNameFilter = readLine("Enter the name of one of the players to search: ", true, &errorCode);
    if (!playerNameFilter)
    {
        printf("Unexpected error occurred while trying to process user input.\n");
        exit(EXIT_FAILURE);
    }

    listAllSavedGamesByPlayerName(DEFAULT_SAVES_FILEPATH, playerNameFilter);

    free(playerNameFilter);
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

GameContext* loadGameByIdWrapper(const long long saveId)
{
    ErrorCode errorCode;
    GameContext* loadedGame = loadGameBySaveId(DEFAULT_SAVES_FILEPATH, saveId, &errorCode);
    if (!loadedGame)
    {
        if (errorCode != NO_ERROR)
        {
            printf("Unexpected error occurred while trying to load the specified save.\n");
            exit(EXIT_FAILURE);
        }

        printf("Save with id %lld was not found.\n", saveId);
        return nullptr;
    }

    return loadedGame;
}