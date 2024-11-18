#include <board.h>

#include <unity.h>

#include <stdlib.h>

static Board* g_testBoard = nullptr;
static ErrorCode g_errorCode = NO_ERROR;

void setUp()
{
    g_testBoard = allocateEmptyBoard(&g_errorCode);
    TEST_ASSERT_NOT_NULL(g_testBoard);
    TEST_ASSERT_EQUAL(NO_ERROR, g_errorCode);
}

void tearDown()
{
    free(g_testBoard);
    g_testBoard = nullptr;
}

void testAllocateEmptyBoard()
{
    TEST_ASSERT_NOT_NULL(g_testBoard);
    TEST_ASSERT_EQUAL(NO_ERROR, g_errorCode);

    for (int i = 0; i < TOTAL_CELLS; ++i)
    {
        TEST_ASSERT_EQUAL(EMPTY, g_testBoard->cellArray[i]);
    }
}

void testGetCellAtValidIndices()
{
    for (int i = 0; i < TOTAL_CELLS; ++i)
    {
        g_testBoard->cellArray[i] = CROSS;
    }

    const Cell firstCell = getCellAt(g_testBoard, 0, 0, &g_errorCode);
    TEST_ASSERT_EQUAL(NO_ERROR, g_errorCode);
    TEST_ASSERT_EQUAL(CROSS, firstCell);

    const Cell middleCell = getCellAt(g_testBoard, BOARD_HEIGHT / 2, BOARD_WIDTH / 2, &g_errorCode);
    TEST_ASSERT_EQUAL(NO_ERROR, g_errorCode);
    TEST_ASSERT_EQUAL(CROSS, middleCell);

    const Cell lastCell = getCellAt(g_testBoard, BOARD_HEIGHT - 1, BOARD_WIDTH - 1, &g_errorCode);
    TEST_ASSERT_EQUAL(NO_ERROR, g_errorCode);
    TEST_ASSERT_EQUAL(CROSS, lastCell);
}

void testGetCellAtInvalidIndices()
{
    getCellAt(g_testBoard, -1, 0, &g_errorCode);
    TEST_ASSERT_EQUAL(ERROR_ARGUMENT_OUT_OF_RANGE, g_errorCode);

    getCellAt(g_testBoard, BOARD_HEIGHT, 0, &g_errorCode);
    TEST_ASSERT_EQUAL(ERROR_ARGUMENT_OUT_OF_RANGE, g_errorCode);
}

void testSetCellAtValidIndices()
{
    setCellAt(g_testBoard, 0, 0, CROSS, &g_errorCode);
    TEST_ASSERT_EQUAL(NO_ERROR, g_errorCode);
    TEST_ASSERT_EQUAL(CROSS, g_testBoard->cellArray[0]);

    setCellAt(g_testBoard, BOARD_HEIGHT / 2, BOARD_WIDTH / 2, ZERO, &g_errorCode);
    TEST_ASSERT_EQUAL(NO_ERROR, g_errorCode);
    TEST_ASSERT_EQUAL(ZERO, g_testBoard->cellArray[(BOARD_HEIGHT / 2 * BOARD_WIDTH) + (BOARD_WIDTH / 2)]);

    setCellAt(g_testBoard, BOARD_HEIGHT - 1, BOARD_WIDTH - 1, CROSS, &g_errorCode);
    TEST_ASSERT_EQUAL(NO_ERROR, g_errorCode);
    TEST_ASSERT_EQUAL(CROSS, g_testBoard->cellArray[TOTAL_CELLS - 1]);
}

void testSetCellAtInvalidIndices()
{
    setCellAt(g_testBoard, -1, 0, CROSS, &g_errorCode);
    TEST_ASSERT_EQUAL(ERROR_ARGUMENT_OUT_OF_RANGE, g_errorCode);

    setCellAt(g_testBoard, 0, BOARD_WIDTH, ZERO, &g_errorCode);
    TEST_ASSERT_EQUAL(ERROR_ARGUMENT_OUT_OF_RANGE, g_errorCode);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(testAllocateEmptyBoard);
    RUN_TEST(testGetCellAtValidIndices);
    RUN_TEST(testGetCellAtInvalidIndices);
    RUN_TEST(testSetCellAtValidIndices);
    RUN_TEST(testSetCellAtInvalidIndices);

    return UNITY_END();
}
