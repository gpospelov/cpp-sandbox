#include <gtest/gtest.h>
#include "fancyutils.h"
#include "coreutils.h"

class TestAPI : public ::testing::Test
{
public:
    ~TestAPI();
};

TestAPI::~TestAPI() = default;

TEST_F(TestAPI, publicMethods)
{
    EXPECT_EQ(fancy::get_number(), 42);
}

TEST_F(TestAPI, privateMethods)
{
    EXPECT_EQ(*fancy::fizzbuzz(42), "fizzbuzz");
}
