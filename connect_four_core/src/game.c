#include <game.h>

#include <board.h>
#include <error_codes.h>
#include <io_utility.h>

#include <stdio.h>
#include <stdlib.h>

void displayGameHeader(const GameContext* gameContext);
void startCurrentPlayerTurn(const GameContext* gameContext);
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

    while (true)
    {
        printf("\n");
        displayBoard(gameContext->board);

        printf("%s, it is your turn.\n", gameContext->currentPlayer->name);
        startCurrentPlayerTurn(gameContext);

        // update game state
        // end the game if game state != IN_PROCESS
        switchCurrentPlayer(gameContext);
    }
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

void startCurrentPlayerTurn(const GameContext* gameContext)
{
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
    gameContext->currentPlayer = (gameContext->currentPlayer == &gameContext->firstPlayer)
                               ? &gameContext->secondPlayer
                               : &gameContext->firstPlayer;
}