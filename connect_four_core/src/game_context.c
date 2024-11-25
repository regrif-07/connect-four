#include <game_context.h>

#include <id_generator.h>
#include <io_utility.h>

#include <stdlib.h>

GameContext* createNewGameContext(ErrorCode* errorCode)
{
    GameContext* gameContext = malloc(sizeof(GameContext));
    if (!gameContext)
    {
        if (errorCode) *errorCode = ERROR_MEMORY;
        return nullptr;
    }

    char* crossPlayerName = readLine("Enter the name of the cross ('X') player: ", true, errorCode);
    if (!crossPlayerName)
    {
        free(gameContext);
        return nullptr;
    }

    char* zeroPlayerName = readLine("Enter the name of the zero ('O') player: ", true, errorCode);
    if (!zeroPlayerName)
    {
        free(gameContext);
        free(crossPlayerName);
        return nullptr;
    }

    gameContext->crossPlayer = (Player) { crossPlayerName, CROSS };
    gameContext->zeroPlayer = (Player) { zeroPlayerName, ZERO };
    gameContext->currentPlayer = &(gameContext->crossPlayer);

    gameContext->board = createEmptyBoard(errorCode);
    if (!gameContext->board)
    {
        free(gameContext->zeroPlayer.name);
        free(gameContext->crossPlayer.name);
        free(gameContext);
        return nullptr;
    }

    gameContext->gameState = IN_PROCESS;

    if (errorCode) *errorCode = NO_ERROR;
    return gameContext;
}

void freeGameContext(GameContext* gameContext)
{
    free(gameContext->board);
    free(gameContext->zeroPlayer.name);
    free(gameContext->crossPlayer.name);
    free(gameContext);
}