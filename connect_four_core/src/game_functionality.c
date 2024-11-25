#include <game_functionality.h>

#include <game_context.h>
#include <game_state.h>

#include <board.h>
#include <error_codes.h>
#include <io_utility.h>

#include <assert.h>
#include <save_system.h>
#include <stdio.h>
#include <stdlib.h>

const char* GAME_CONTEXT_ID_COUNTER_FILEPATH = "game_context_id_counter";

/// Loop and ask current player for a valid move he wants to play.
/// Perform this move and return last move data throughout out parameters.
/// @param gameContext current GameContext.
/// @param lastMoveRowIndex out parameter; should be filled with row index of the last move.
/// @param lastMoveColumnIndex out parameter; should be filled with column index of the last move.
void startCurrentPlayerTurn(const GameContext* gameContext, int* lastMoveRowIndex, int* lastMoveColumnIndex);

/// Search and return the row index of the first free cell in the specified column.
/// @param board board to search in.
/// @param columnIndex index of the column in which free cell should be searched.
/// @return row index of the first free cell in the specified column; -1 if no such row was found.
int findFirstFreeColumnCell(const Board* board, const int columnIndex);

/// Switch current player (cross player to zero player and zero player to cross player).
/// @param gameContext current GameContext.
void switchCurrentPlayer(GameContext* gameContext);

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

    printf("Board state:\n");
    displayBoard(gameContext->board);
    printf("*===*\n");
}

void startCurrentPlayerTurn(const GameContext* gameContext, int* lastMoveRowIndex, int* lastMoveColumnIndex)
{
    assert(lastMoveRowIndex && lastMoveColumnIndex); // check for nullptr output parameters

    while (true)
    {
        const int playerInputInteger = loopReadIntegerInRange("Enter the column (or enter '0' to save the game): ", 0, BOARD_WIDTH);
        if (playerInputInteger == 0)
        {
            ErrorCode errorCode;
            const long long saveId = saveGame(DEFAULT_SAVES_FILEPATH, gameContext, &errorCode);
            if (errorCode != NO_ERROR)
            {
                printf("Unexpected error occurred while trying to save your game.\n");
                exit(EXIT_FAILURE);
            }

            printf("Your game was successfully saved. Save id: %lld.\n", saveId);
            continue;
        }

        const int targetColumnIndex = playerInputInteger - 1;
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