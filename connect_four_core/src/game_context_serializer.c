#include <game_context_serializer.h>

#include <board.h>
#include <board_serializer.h>
#include <error_codes.h>
#include <game_context.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

constexpr int PLAYER_NAME_BUFFER_SIZE = 256;

// serialization format: [id] "[cross player name]" "[zero player name]" [current player (X or O)] [serialized board] [game state (number)]
const char* GAME_CONTEXT_SERIALIZE_FORMAT_STRING = "%d \"%s\" \"%s\" %c \"%s\" %d";
const char* GAME_CONTEXT_DESERIALIZE_FORMAT_STRING = "%d \"%[^\"]\" \"%[^\"]\" %c \"%[^\"]\" %d";

char* serializeGameContext(const GameContext* gameContext, ErrorCode* errorCode)
{
    if (!gameContext)
    {
        if (errorCode) *errorCode = ERROR_NULLPTR_ARGUMENT;
        return nullptr;
    }

    char* serializedBoard = serializeBoard(gameContext->board, errorCode);
    if (errorCode && *errorCode != NO_ERROR)
    {
        return nullptr;
    }

    const int gameContextSerializedLength = snprintf(nullptr, 0, GAME_CONTEXT_SERIALIZE_FORMAT_STRING,
        gameContext->id,
        gameContext->crossPlayer.name,
        gameContext->zeroPlayer.name,
        cellToChar(gameContext->currentPlayer->cell),
        serializedBoard,
        (int)(gameContext->gameState));
    char* gameContextSerialized = malloc(sizeof(char) * gameContextSerializedLength + 1);
    snprintf(gameContextSerialized, gameContextSerializedLength + 1, GAME_CONTEXT_SERIALIZE_FORMAT_STRING,
        gameContext->id,
        gameContext->crossPlayer.name,
        gameContext->zeroPlayer.name,
        cellToChar(gameContext->currentPlayer->cell),
        serializedBoard,
        (int)(gameContext->gameState));

    if (errorCode) *errorCode = NO_ERROR;
    return gameContextSerialized;
}

GameContext* deserializeGameContext(const char* serializedGameContext, ErrorCode* errorCode)
{
    if (!serializedGameContext)
    {
        if (errorCode) *errorCode = ERROR_NULLPTR_ARGUMENT;
        return nullptr;
    }

    int id;
    char crossPlayerNameBuffer[PLAYER_NAME_BUFFER_SIZE];
    char zeroPlayerNameBuffer[PLAYER_NAME_BUFFER_SIZE];
    char currentPlayerCellChar;
    char serializedBoard[TOTAL_CELLS];
    int gameStateInteger;

    const int elementsRead = sscanf(serializedGameContext, GAME_CONTEXT_DESERIALIZE_FORMAT_STRING,
        &id,
        &crossPlayerNameBuffer,
        &zeroPlayerNameBuffer,
        &currentPlayerCellChar,
        &serializedBoard,
        &gameStateInteger);
    if (elementsRead != 6)
    {
        if (errorCode) *errorCode = ERROR_INVALID_ARGUMENT;
        return nullptr;
    }

    char* crossPlayerName = malloc(sizeof(char) * strlen(crossPlayerNameBuffer));
    char* zeroPlayerName = malloc(sizeof(char) * strlen(zeroPlayerNameBuffer));
    if (!crossPlayerName || !zeroPlayerName)
    {
        if (errorCode) *errorCode = ERROR_MEMORY;
        return nullptr;
    }
    strcpy(crossPlayerName, crossPlayerNameBuffer);
    strcpy(zeroPlayerName, zeroPlayerNameBuffer);

    Cell currentPlayerCell = charToCell(currentPlayerCellChar, errorCode);
    if (errorCode && *errorCode != NO_ERROR)
    {
        return nullptr;
    }

    Board* deserializedBoard = deserializeBoard(serializedBoard, errorCode);
    if (errorCode && *errorCode != NO_ERROR)
    {
        free(crossPlayerName);
        free(zeroPlayerName);
        return nullptr;
    }

    GameContext* deserializedGameContext = malloc(sizeof(GameContext));
    deserializedGameContext->id = id;
    deserializedGameContext->crossPlayer = (Player) { crossPlayerName, CROSS };
    deserializedGameContext->zeroPlayer = (Player) { zeroPlayerName, ZERO };
    deserializedGameContext->currentPlayer = (currentPlayerCell == CROSS) ?
                                             &deserializedGameContext->crossPlayer :
                                             &deserializedGameContext->zeroPlayer;
    deserializedGameContext->board = deserializedBoard;
    deserializedGameContext->gameState = (GameState)(gameStateInteger);

    if (errorCode) *errorCode = NO_ERROR;
    return deserializedGameContext;
}
