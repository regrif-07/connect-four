#include <save_system.h>

#include <game_context.h>
#include <game_context_serializer.h>

#include <id_generator.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

constexpr int SAVE_ENTRY_LINE_BUFFER_SIZE = 1024;

const char* SAVES_ID_COUNTER_FILEPATH = "saves_id_counter";
const char* DEFAULT_SAVES_FILEPATH = "results.txt";

/// Display short info about the provided game context (with save id).
/// @param saveId id of the save.
/// @param gameContext game context to be displayed.
void displayShortGameInfo(const long long saveId, const GameContext* gameContext);

/// Count the amount of empty cells on the provided board.
/// @param board board where counting will be processed.
/// @return number of empty cells on the provided board.
int countEmptyCells(const Board* board);

long long saveGame(const char* savesFilepath, const GameContext* gameContext, ErrorCode* errorCode)
{
    if (!gameContext)
    {
        if (errorCode) *errorCode = ERROR_NULLPTR_ARGUMENT;
        return ID_NOT_FOUND;
    }

    FILE* savesFile = fopen(savesFilepath, "a");
    if (!savesFile)
    {
        if (errorCode) *errorCode = ERROR_FILE_IO;
        return ID_NOT_FOUND;
    }

    char* serializedGameContext = serializeGameContext(gameContext, errorCode);
    if (!serializedGameContext)
    {
        fclose(savesFile);
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

GameContext* loadGameBySaveId(const char* savesFilepath, const long long targetSaveId, ErrorCode* errorCode)
{
    static char lineBuffer[SAVE_ENTRY_LINE_BUFFER_SIZE];

    FILE* savesFile = fopen(savesFilepath, "r");
    if (!savesFile)
    {
        if (errorCode) *errorCode = NO_ERROR;
        return nullptr;
    }

    char* serializedGameContext = nullptr;

    bool matchFound = false;
    while (fgets(lineBuffer, sizeof(lineBuffer), savesFile) != nullptr)
    {
        long long saveId = ID_NOT_FOUND;

        char* contextStart = strchr(lineBuffer, ' '); // find the first space
        if (contextStart)
        {
            *contextStart = '\0';  // split the line into two parts
            saveId = atoll(lineBuffer);  // convert the first part to a save ID
            serializedGameContext = strdup(contextStart + 1);  // copy the rest as the context
        }

        if (saveId == targetSaveId)
        {
            matchFound = true;
            break;
        }

        if (serializedGameContext)
        {
            free(serializedGameContext);
            serializedGameContext = nullptr;
        }
    }

    if (!matchFound)
    {
        if (errorCode) *errorCode = NO_ERROR;
        return nullptr;
    }

    GameContext* deserializedGameContext = deserializeGameContext(serializedGameContext, errorCode);
    if (!deserializedGameContext)
    {
        free(serializedGameContext);
        if (errorCode) *errorCode = ERROR_FILE_STATE;
        return nullptr;
    }

    free(serializedGameContext);
    if (errorCode) *errorCode = NO_ERROR;
    return deserializedGameContext;
}

void listAllSavedGames(const char* savesFilepath)
{
    ErrorCode errorCode;

    const long long lastSaveId = loadPreviousId(SAVES_ID_COUNTER_FILEPATH, &errorCode);
    if (errorCode != NO_ERROR)
    {
        return;
    }

    if (lastSaveId == ID_START)
    {
        printf("No saved games were found.\n");
        return;
    }

    printf("List of saved games:\n");
    for (long long saveId = ID_START; saveId <= lastSaveId; ++saveId)
    {
        GameContext* gameContext = loadGameBySaveId(savesFilepath, saveId, &errorCode);
        if (!gameContext)
        {
            if (errorCode != NO_ERROR)
            {
                printf("Unexpected error occurred while trying to list all saved games.");
                exit(EXIT_FAILURE);
            }

            continue;
        }

        displayShortGameInfo(saveId, gameContext);

        freeGameContext(gameContext);
    }
}

void listAllSavedGamesByPlayerName(const char* savesFilepath, const char* playerNameFilter)
{
    ErrorCode errorCode;

    const long long lastSaveId = loadPreviousId(SAVES_ID_COUNTER_FILEPATH, &errorCode);
    if (errorCode != NO_ERROR)
    {
        return;
    }

    if (lastSaveId == ID_START)
    {
        printf("No saved games were found.\n");
        return;
    }

    bool oneMatched = false;
    printf("List of all saved games where at least one player is \"%s\":\n", playerNameFilter);
    for (long long saveId = ID_START; saveId <= lastSaveId; ++saveId)
    {
        GameContext* gameContext = loadGameBySaveId(savesFilepath, saveId, &errorCode);
        if (!gameContext)
        {
            if (errorCode != NO_ERROR)
            {
                printf("Unexpected error occurred while trying to list all saved games.");
                exit(EXIT_FAILURE);
            }

            continue;
        }

        if (strcmp(gameContext->crossPlayer.name, playerNameFilter) == 0 ||
            strcmp(gameContext->zeroPlayer.name, playerNameFilter) == 0)
        {
            displayShortGameInfo(saveId, gameContext);
            oneMatched = true;
        }

        freeGameContext(gameContext);
    }

    if (!oneMatched)
    {
        printf("No suitable saved games were found.\n");
    }
}

void displayShortGameInfo(const long long saveId, const GameContext* gameContext)
{
    printf("ID: %lld; %s ('X') vs %s ('O'); %d empty cells\n",
            saveId,
            gameContext->crossPlayer.name, gameContext->zeroPlayer.name,
            countEmptyCells(gameContext->board));
}

int countEmptyCells(const Board* board)
{
    int emptyCellCounter = 0;
    for (int cellIndex = 0; cellIndex < TOTAL_CELLS; ++cellIndex)
    {
        if (board->cellArray[cellIndex] == EMPTY)
        {
            ++emptyCellCounter;
        }
    }

    return emptyCellCounter;
}