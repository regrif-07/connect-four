#include <game.h>

#include <board.h>
#include <error_codes.h>
#include <io_utility.h>

#include <stdio.h>
#include <stdlib.h>

void displayGameHeader(const GameContext* gameContext);

GameContext* createNewGameContext(ErrorCode* errorCode)
{
    GameContext* gameContext = malloc(sizeof(GameContext));
    if (!gameContext)
    {
        if (errorCode) *errorCode = ERROR_MEMORY;
        return nullptr;
    }

    gameContext->firstPlayer = (Player) {
        readLine("Enter the name of the cross ('X') player: ", true),
        CROSS
    };
    gameContext->secondPlayer = (Player) {
        readLine("Enter the name of the zero ('O') player: ", true),
        ZERO
    };
    gameContext->currentPlayer = &(gameContext->firstPlayer);

    gameContext->board = createEmptyBoard(errorCode);
    if (errorCode && *errorCode != NO_ERROR)
    {
        return nullptr;
    }

    if (errorCode) *errorCode = NO_ERROR;
    return gameContext;
}

void freeGameContext(GameContext* gameContext)
{
    free(gameContext->firstPlayer.name);
    free(gameContext->secondPlayer.name);
    free(gameContext->board);
    free(gameContext);
}

void startGame(GameContext* gameContext, ErrorCode* errorCode)
{
    if (!gameContext || !gameContext->board)
    {
        if (errorCode) *errorCode = ERROR_INVALID_ARGUMENT;
        return;
    }

    displayGameHeader(gameContext);
}

void displayGameHeader(const GameContext* gameContext)
{
    printf("*===*\n"
           "CONNECT FOUR\n"
           "*===*\n"
           "%s ('X') VS %s ('O')\n"
           "*===*\n", gameContext->firstPlayer.name, gameContext->secondPlayer.name);

    printf("Initial board state:\n");
    displayBoard(gameContext->board);
    printf("*===*\n");
}