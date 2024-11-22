#pragma once

#include <error_codes.h>
#include <game_context.h>

char* serializeGameContext(const GameContext* gameContext, ErrorCode* errorCode);
GameContext* deserializeGameContext(const char* serializedGameContext, ErrorCode* errorCode);
