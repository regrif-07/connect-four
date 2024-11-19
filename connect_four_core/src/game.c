#include <game.h>

#include <board.h>
#include <error_codes.h>
#include <game_state.h>
#include <io_utility.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/// Display initial information about game (game name, players, board state).
/// @param gameContext current GameContext.
void displayGameHeader(const GameContext* gameContext);

/// Loop and ask current player for a valid move he wants to play.
/// Perform this move and return last move data throughout out parameters.
/// @param gameContext current GameContext.
/// @param lastMoveRowIndex out parameter; should be filled with row index of the last move.
/// @param lastMoveColumnIndex out parameter; should be filled with column index of the last move.
void startCurrentPlayerTurn(const GameContext* gameContext, int* lastMoveRowIndex, int* lastMoveColumnIndex);

/// Search and return the row index of a first free cell in a specified column.
/// @param board board to search in.
/// @param columnIndex index of the column in which free cell should be searched.
/// @return row index of the first free cell in the specified column; -1 if no such row was found.
int findFirstFreeColumnCell(const Board* board, const int columnIndex);

/// Switch current player (cross player to zero player and zero player to cross player).
/// @param gameContext current GameContext.
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
        if (errorCode) *errorCode = ERROR_NULLPTR_ARGUMENT;
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

    if (errorCode) *errorCode = NO_ERROR;
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
    assert(lastMoveRowIndex && lastMoveColumnIndex); // check for nullptr output parameters

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