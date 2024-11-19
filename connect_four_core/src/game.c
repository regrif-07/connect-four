#include <game.h>

#include <board.h>
#include <error_codes.h>
#include <game_state.h>
#include <io_utility.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void displayGameHeader(const GameContext* gameContext);
void startCurrentPlayerTurn(const GameContext* gameContext, int* lastMoveRowIndex, int* lastMoveColumnIndex);
int findFirstFreeColumnCell(const Board* board, const int columnIndex);
void switchCurrentPlayer(GameContext* gameContext);

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

void startGame(GameContext* gameContext, ErrorCode* errorCode)
{
    if (!gameContext || !gameContext->board)
    {
        if (errorCode) *errorCode = ERROR_INVALID_ARGUMENT;
        return;
    }

    displayGameHeader(gameContext);

    while (gameContext->gameState == IN_PROCESS) // in case loaded game was already ended
    {
        printf("\n");
        displayBoard(gameContext->board);

        printf("%s, it is your turn.\n", gameContext->currentPlayer->name);
        int lastMoveRowIndex;
        int lastMoveColumnIndex;
        startCurrentPlayerTurn(gameContext, &lastMoveRowIndex, &lastMoveColumnIndex);

        gameContext->gameState = checkGameStateAndMarkWinningStreak(gameContext->board, lastMoveRowIndex, lastMoveColumnIndex, nullptr);
        if (gameContext->gameState != IN_PROCESS)
        {
            return;
        }

        switchCurrentPlayer(gameContext);
    }
}

void displayGameHeader(const GameContext* gameContext)
{
    printf("*===*\n"
           "CONNECT FOUR\n"
           "*===*\n"
           "%s ('X') VS %s ('O')\n"
           "*===*\n", gameContext->crossPlayer.name, gameContext->zeroPlayer.name);

    printf("Initial board state:\n");
    displayBoard(gameContext->board);
    printf("*===*\n");
}

void startCurrentPlayerTurn(const GameContext* gameContext, int* lastMoveRowIndex, int* lastMoveColumnIndex)
{
    assert(lastMoveRowIndex && lastMoveColumnIndex);

    while (true)
    {
        const int targetColumnIndex = loopReadIntegerInRange("Enter the column: ", 1, BOARD_WIDTH) - 1;
        const int targetRowIndex = findFirstFreeColumnCell(gameContext->board, targetColumnIndex);
        if (targetRowIndex == -1)
        {
            printf("This column is already filled. Choose another one.\n");
            continue;
        }

        setCellAt(gameContext->board, targetRowIndex, targetColumnIndex, gameContext->currentPlayer->cell, nullptr);
        *lastMoveRowIndex = targetRowIndex;
        *lastMoveColumnIndex = targetColumnIndex;

        break;
    }
}

int findFirstFreeColumnCell(const Board* board, const int columnIndex)
{
    for (int rowIndex = BOARD_HEIGHT - 1; rowIndex >= 0; --rowIndex) // we are searching bottom-up
    {
        if (getCellAt(board, rowIndex, columnIndex, nullptr) == EMPTY)
        {
            return rowIndex;
        }
    }

    return -1;
}

void switchCurrentPlayer(GameContext* gameContext)
{
    gameContext->currentPlayer = (gameContext->currentPlayer == &gameContext->crossPlayer)
                               ? &gameContext->zeroPlayer
                               : &gameContext->crossPlayer;
}