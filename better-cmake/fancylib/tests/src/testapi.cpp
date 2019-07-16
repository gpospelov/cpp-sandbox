#include <gtest/gtest.h>
//#include "fancyutils.h"

class TestAPI : public ::testing::Test
{
public:
    ~TestAPI();
};

TestAPI::~TestAPI() = default;

TEST_F(TestAPI, publicMethods)
{
    EXPECT_EQ(1, 1);
}
