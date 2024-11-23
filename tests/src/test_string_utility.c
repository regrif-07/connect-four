#include <unity.h>

#include <string_utility.h>

void setUp() {}
void tearDown() {}

void testIsWhitespaceOnlyAllWhitespace(void)
{
    TEST_ASSERT_TRUE(isWhitespaceOnly("   \t\n"));
}

void testIsWhitespaceOnlyMixed(void)
{
    TEST_ASSERT_FALSE(isWhitespaceOnly("Hello World"));
}

void testIsWhitespaceOnlyEmpty(void)
{
    TEST_ASSERT_TRUE(isWhitespaceOnly(""));
}

void testIsWhitespaceOnlyNullptr(void)
{
    TEST_ASSERT_FALSE(isWhitespaceOnly(nullptr));
}

int main(void)
{
    UNITY_BEGIN();

    // tests for isWhitespaceOnly()
    RUN_TEST(testIsWhitespaceOnlyAllWhitespace);
    RUN_TEST(testIsWhitespaceOnlyMixed);
    RUN_TEST(testIsWhitespaceOnlyEmpty);
    RUN_TEST(testIsWhitespaceOnlyNullptr);

    return UNITY_END();
}

