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

    gameContext->crossPlayer = (Player) {
        readLine("Enter the name of the cross ('X') player: ", true),
        CROSS
    };
    gameContext->zeroPlayer = (Player) {
        readLine("Enter the name of the zero ('O') player: ", true),
        ZERO
    };
    gameContext->currentPlayer = &(gameContext->crossPlayer);

    gameContext->board = createEmptyBoard(errorCode);
    if (errorCode && *errorCode != NO_ERROR)
    {
        return nullptr;
    }

    gameContext->gameState = IN_PROCESS;

    if (errorCode) *errorCode = NO_ERROR;
    return gameContext;
}

void freeGameContext(GameContext* gameContext)
{
    free(gameContext->crossPlayer.name);
    free(gameContext->zeroPlayer.name);
    free(gameContext->board);
    free(gameContext);
}