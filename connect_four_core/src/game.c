#include <game.h>

#include <board.h>
#include <error_codes.h>

#include <stdio.h>
#include <stdlib.h>

void displayGameHeader(const GameContext* gameContext);

GameContext* allocateNewGameContext(ErrorCode* errorCode)
{
    GameContext* gameContext = malloc(sizeof(GameContext));
    if (!gameContext)
    {
        if (errorCode) *errorCode = ERROR_MEMORY;
        return nullptr;
    }

    gameContext->crossPlayerName = nullptr;
    gameContext->zeroPlayerName = nullptr;

    gameContext->board = allocateEmptyBoard(errorCode);
    if (errorCode && *errorCode != NO_ERROR)
    {
        return nullptr;
    }

    if (errorCode) *errorCode = NO_ERROR;
    return gameContext;
}

void startGame(GameContext* gameContext, ErrorCode* errorCode)
{
    if (!gameContext || !gameContext->crossPlayerName || !gameContext->zeroPlayerName || !gameContext->board)
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
           "*===*\n", gameContext->crossPlayerName, gameContext->zeroPlayerName);

    printf("Initial board state:\n");
    displayBoard(gameContext->board);
    printf("*===*\n");
}