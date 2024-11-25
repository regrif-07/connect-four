#include <game_context.h>
#include <game_context_serializer.h>
#include <id_generator.h>
#include <save_system.h>
#include <stdio.h>
#include <stdlib.h>

const char* SAVES_ID_COUNTER_FILEPATH = "saves_id_counter";
const char* SAVES_FILEPATH = "results.txt";

long long saveGame(const GameContext* gameContext, ErrorCode* errorCode)
{
    if (!gameContext)
    {
        if (errorCode) *errorCode = ERROR_NULLPTR_ARGUMENT;
        return ID_NOT_FOUND;
    }

    FILE* savesFile = fopen(SAVES_FILEPATH, "a");
    if (!savesFile)
    {
        if (errorCode) *errorCode = ERROR_FILE_IO;
        return ID_NOT_FOUND;
    }

    char* serializedGameContext = serializeGameContext(gameContext, errorCode);
    if (!serializedGameContext)
    {
        return ID_NOT_FOUND;
    }

    const long long saveId = generateNextId(SAVES_ID_COUNTER_FILEPATH, errorCode);
    if (errorCode && *errorCode != NO_ERROR)
    {
        fclose(savesFile);
        free(serializedGameContext);
        return ID_NOT_FOUND;
    }

    if (fprintf(savesFile, "%lld %s\n", saveId, serializedGameContext) < 0)
    {
        fclose(savesFile);
        free(serializedGameContext);
        if (errorCode) *errorCode = ERROR_FILE_IO;
        return ID_NOT_FOUND;
    }

    fclose(savesFile);
    free(serializedGameContext);
    if (errorCode) *errorCode = NO_ERROR;
    return saveId;
}

GameContext* loadGameById(const long long targetGameId, ErrorCode* errorCode)
{
    FILE* savesFile = fopen(SAVES_FILEPATH, "r");
    if (!savesFile)
    {
        if (errorCode) *errorCode = NO_ERROR;
        return nullptr;
    }

    char* serializedGameContext = nullptr;
    char* line = nullptr;

    size_t buffLen = 0;

    bool matchFound = false;
    while (getline(&line, &buffLen, savesFile) != -1)
    {
        long long gameId = ID_NOT_FOUND;
        if (sscanf(line, "%lld %m[^\n]", &gameId, &serializedGameContext) == 2)
        {
            if (gameId == targetGameId)
            {
                matchFound = true;
                break;
            }

            free(serializedGameContext);
        }
    }

    if (!matchFound)
    {
        free(line);
        if (errorCode) *errorCode = NO_ERROR;
        return nullptr;
    }

    GameContext* deserializedGameContext = deserializeGameContext(serializedGameContext, errorCode);
    if (!deserializedGameContext)
    {
        free(line);
        free(serializedGameContext);
        if (errorCode) *errorCode = ERROR_FILE_STATE;
        return nullptr;
    }

    free(serializedGameContext);
    free(line);
    if (errorCode) *errorCode = NO_ERROR;
    return deserializedGameContext;
}
