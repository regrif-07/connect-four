#pragma once

#include <error_codes.h>

constexpr long long ID_NOT_FOUND = -1;

long long saveGame(const GameContext* gameContext, ErrorCode* errorCode);
GameContext* loadGameById(const long long targetGameId, ErrorCode* errorCode);