#include <game.h>

#include <board.h>
#include <error_codes.h>

#include <stdio.h>
#include <stdlib.h>

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

    printf("%s %s", gameContext->crossPlayerName, gameContext->zeroPlayerName);
    displayBoard(gameContext->board);
}