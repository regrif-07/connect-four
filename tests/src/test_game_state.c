#include <unity.h>

#include <board.h>
#include <board_serializer.h>
#include <error_codes.h>
#include <game_state.h>
#include <stdlib.h>

void setUp() {}
void tearDown() {}

void testCheckGameStateAndMarkWinningStreakInProcess()
{
    const char* serializedBoard =
        "......."
        "......."
        "O......"
        "X......"
        "XX....."
        "XOOO...";
    Board* board = deserializeBoard(serializedBoard, nullptr);
    TEST_ASSERT_NOT_NULL(board);

    ErrorCode errorCode;
    const GameState gameState = checkGameStateAndMarkWinningStreak(board, 4, 1, &errorCode);
    TEST_ASSERT_EQUAL(IN_PROCESS, gameState);

    free(board);
}

void testCheckGameStateAndMarkWinningStreakCrossWin()
{
    const char* serializedBoard =
        "......."
        "......."
        "X...X.."
        "XX.OO.."
        "XXO.XXO"
        "XOXOXOX";
    Board* board = deserializeBoard(serializedBoard, nullptr);
    TEST_ASSERT_NOT_NULL(board);

    ErrorCode errorCode;
    const GameState state = checkGameStateAndMarkWinningStreak(board, 2, 0, &errorCode);
    TEST_ASSERT_EQUAL_INT(NO_ERROR, errorCode);
    TEST_ASSERT_EQUAL_INT(CROSS_WIN, state);

    // verify that winning streak cells are marked
    TEST_ASSERT_EQUAL_INT(STREAK, getCellAt(board, 2, 0, nullptr));
    TEST_ASSERT_EQUAL_INT(STREAK, getCellAt(board, 3, 0, nullptr));
    TEST_ASSERT_EQUAL_INT(STREAK, getCellAt(board, 4, 0, nullptr));
    TEST_ASSERT_EQUAL_INT(STREAK, getCellAt(board, 5, 0, nullptr));

    free(board);
}

void testCheckGameStateAndMarkWinningStreakZeroWin()
{
    const char* serializedBoard =
        "......."
        "......."
        "XO....."
        "OXOXOXO"
        "XOXOXOX"
        "OXOXOXO";
    Board* board = deserializeBoard(serializedBoard, nullptr);
    TEST_ASSERT_NOT_NULL(board);

    ErrorCode errorCode;
    const GameState state = checkGameStateAndMarkWinningStreak(board, 2, 1, &errorCode);
    TEST_ASSERT_EQUAL_INT(ZERO_WIN, state);
    TEST_ASSERT_EQUAL_INT(NO_ERROR, errorCode);

    // verify that winning streak cells are marked
    TEST_ASSERT_EQUAL_INT(STREAK, getCellAt(board, 2, 1, nullptr));
    TEST_ASSERT_EQUAL_INT(STREAK, getCellAt(board, 3, 2, nullptr));
    TEST_ASSERT_EQUAL_INT(STREAK, getCellAt(board, 4, 3, nullptr));
    TEST_ASSERT_EQUAL_INT(STREAK, getCellAt(board, 5, 4, nullptr));

    free(board);
}

void testCheckGameStateAndMarkWinningStreakDraw()
{
    const char* serializedBoard =
        "OXOXOXO"
        "XOXOXOX"
        "OXOXOXO"
        "XOXOXOX"
        "OXOXOXO"
        "XOXOXOX";
    Board* board = deserializeBoard(serializedBoard, nullptr);
    TEST_ASSERT_NOT_NULL(board);

    ErrorCode errorCode;
    const GameState state = checkGameStateAndMarkWinningStreak(board, 5, 5, &errorCode);
    TEST_ASSERT_EQUAL_INT(NO_ERROR, errorCode);
    TEST_ASSERT_EQUAL_INT(DRAW, state);

    free(board);
}

int main()
{
    UNITY_BEGIN();

    // tests for checkGameStateAndMarkWinningStreak()
    RUN_TEST(testCheckGameStateAndMarkWinningStreakInProcess);
    RUN_TEST(testCheckGameStateAndMarkWinningStreakCrossWin);
    RUN_TEST(testCheckGameStateAndMarkWinningStreakZeroWin);
    RUN_TEST(testCheckGameStateAndMarkWinningStreakDraw);

    return UNITY_END();
}
