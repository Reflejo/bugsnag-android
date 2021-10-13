#include <greatest/greatest.h>
#include "utils/number_to_string.h"
#include "test_helpers.h"

TEST test_uint_to_string(void) {
    char buff[100];

    ASSERT_EQ(1, bsg_uint64_to_string(0, buff));
    ASSERT_STR_EQ("0", buff);

    ASSERT_EQ(20, bsg_uint64_to_string(0xffffffffffffffff, buff));
    ASSERT_STR_EQ("18446744073709551615", buff);

    PASS();
}

TEST test_int_to_string(void) {
    char buff[100];

    ASSERT_EQ(1, bsg_int64_to_string(0, buff));
    ASSERT_STR_EQ("0", buff);

    ASSERT_EQ(1, bsg_int64_to_string(1, buff));
    ASSERT_STR_EQ("1", buff);

    ASSERT_EQ(2, bsg_int64_to_string(-1, buff));
    ASSERT_STR_EQ("-1", buff);

    ASSERT_EQ(19, bsg_int64_to_string(0x7fffffffffffffff, buff));
    ASSERT_STR_EQ("9223372036854775807", buff);

    ASSERT_EQ(20, bsg_int64_to_string(-0x8000000000000000, buff));
    ASSERT_STR_EQ("-9223372036854775808", buff);

    PASS();
}

TEST test_hex_to_string(void) {
    char buff[100];

    for (unsigned i = 0; i < 0x10; i++) {
        char expected[10];
        sprintf(expected, "%x", i);
        ASSERT_EQ(1, bsg_hex64_to_string(i, buff));
        ASSERT_STR_EQ(expected, buff);
    }

    for (unsigned i = 0x10; i < 0x100; i++) {
        char expected[10];
        sprintf(expected, "%x", i);
        ASSERT_EQ(2, bsg_hex64_to_string(i, buff));
        ASSERT_STR_EQ(expected, buff);
    }

    ASSERT_EQ(8, bsg_hex64_to_string(0x8fedcba9, buff));
    ASSERT_STR_EQ("8fedcba9", buff);

    ASSERT_EQ(8, bsg_hex64_to_string(0xffffffff, buff));
    ASSERT_STR_EQ("ffffffff", buff);

    ASSERT_EQ(16, bsg_hex64_to_string(0xfedcba9876543210, buff));
    ASSERT_STR_EQ("fedcba9876543210", buff);

    ASSERT_EQ(16, bsg_hex64_to_string(0xffffffffffffffff, buff));
    ASSERT_STR_EQ("ffffffffffffffff", buff);

    PASS();
}

TEST test_double_to_string(void) {
    char buff[100];

    ASSERT_EQ(1, bsg_double_to_string(0, buff, BSG_DEFAULT_SIGNIFICANT_DIGITS));
    ASSERT_STR_EQ("0", buff);

    ASSERT_EQ(1, bsg_double_to_string(1, buff, BSG_DEFAULT_SIGNIFICANT_DIGITS));
    ASSERT_STR_EQ("1", buff);

    ASSERT_EQ(2, bsg_double_to_string(-1, buff, BSG_DEFAULT_SIGNIFICANT_DIGITS));
    ASSERT_STR_EQ("-1", buff);

    ASSERT_EQ(3, bsg_double_to_string(1.5, buff, BSG_DEFAULT_SIGNIFICANT_DIGITS));
    ASSERT_STR_EQ("1.5", buff);

    ASSERT_EQ(6, bsg_double_to_string(-2.855, buff, BSG_DEFAULT_SIGNIFICANT_DIGITS));
    ASSERT_STR_EQ("-2.855", buff);

    ASSERT_EQ(11, bsg_double_to_string(6.95234e-20, buff, BSG_DEFAULT_SIGNIFICANT_DIGITS));
    ASSERT_STR_EQ("6.95234e-20", buff);

    ASSERT_EQ(13, bsg_double_to_string(-2.222594e+15, buff, BSG_DEFAULT_SIGNIFICANT_DIGITS));
    ASSERT_STR_EQ("-2.222594e+15", buff);

    PASS();
}

SUITE(suite_number_to_string) {
    RUN_TEST(test_uint_to_string);
    RUN_TEST(test_int_to_string);
    RUN_TEST(test_hex_to_string);
    RUN_TEST(test_double_to_string);
}
