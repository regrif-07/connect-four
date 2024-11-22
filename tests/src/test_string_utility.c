#include <unity.h>

#include <error_codes.h>
#include <string_utility.h>

#include <stdlib.h>
#include <string.h>

DEFINE_TO_STRING_CONVERSION_FUNCTION(int, int, "%d")
DEFINE_TO_STRING_CONVERSION_FUNCTION(long long, longLong, "%lld")

void setUp(void) {}
void tearDown(void) {}

void testIntToStringValid(void)
{
    ErrorCode errorCode;
    int outStringLength;
    char* result = intToString(42, &outStringLength, &errorCode);

    TEST_ASSERT_EQUAL(NO_ERROR, errorCode);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("42", result);
    TEST_ASSERT_EQUAL(2, outStringLength);

    free(result);
}

void testLongLongToStringValid(void)
{
    ErrorCode errorCode;
    int outStringLength;
    char* result = longLongToString(123456789012345LL, &outStringLength, &errorCode);

    TEST_ASSERT_EQUAL(NO_ERROR, errorCode);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("123456789012345", result);
    TEST_ASSERT_EQUAL(15, outStringLength);

    free(result);
}

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

    // tests for intToString
    RUN_TEST(testIntToStringValid);

    // tests for longLongToString
    RUN_TEST(testLongLongToStringValid);

    // tests for isWhitespaceOnly
    RUN_TEST(testIsWhitespaceOnlyAllWhitespace);
    RUN_TEST(testIsWhitespaceOnlyMixed);
    RUN_TEST(testIsWhitespaceOnlyEmpty);
    RUN_TEST(testIsWhitespaceOnlyNullptr);

    return UNITY_END();
}

