#pragma once

#include <error_codes.h>

/// Save the provided game and return save's id.
/// @param gameContext context of the game to save.
/// @param errorCode out error parameter; ERROR_NULLPTR_ARGUMENT in case gameContext was nullptr,
/// ERROR_FILE_IO in case of saves or id counter files IO failure, NO_ERROR otherwise;
/// @return id of the save, or ID_NOT_FOUND in case of error.
long long saveGame(const GameContext* gameContext, ErrorCode* errorCode);

/// Load the game from the saves file using the provided save's id.
/// @param targetSaveId id of the save to load.
/// @param errorCode out error parameter; ERROR_FILE_STATE in case saves file has invalid format, NO_ERROR otherwise.
/// @return heap allocated loaded game context.
GameContext* loadGameBySaveId(const long long targetSaveId, ErrorCode* errorCode);

/// List all saved games.
void listAllSavedGames();

/// List all saved games where the name of one of the players matches playerNameFilter.
/// @param playerNameFilter name of the player to search.
void listAllSavedGamesByPlayerName(const char* playerNameFilter);