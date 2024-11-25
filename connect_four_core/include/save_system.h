#pragma once

#include <error_codes.h>

long long saveGame(const GameContext* gameContext, ErrorCode* errorCode);
GameContext* loadGameBySaveId(const long long targetSaveId, ErrorCode* errorCode);
void listAllSavedGames();