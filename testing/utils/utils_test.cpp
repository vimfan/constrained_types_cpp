/**
 * @file utils_test.cpp
 * @author Sebastian Madajczyk, sebastian@madajczyk.net
 * @date 04.05.2014
 */

#include <gtest/gtest.h>

#include "utils.hpp"

namespace ct
{

namespace utils
{

namespace ut
{

struct NonExplicitCopyConstructor
{
    NonExplicitCopyConstructor(int val)
        : value(val)
    {}

    int value;
};

TEST(HasNonExplicitCopyConstructorTest, shouldReturnTrueWhenConstructorIsNonExplicit)
{
    ASSERT_TRUE((HasNonExplicitCopyConstructor<NonExplicitCopyConstructor, int, 5>::value));
}

struct ExplicitCopyConstructor
{
    explicit ExplicitCopyConstructor(int val)
        : value(val)
    {
    }

    int value;
};

TEST(HasNonExplicitCopyConstructorTest, shouldReturnFalseWhenConstructorIsExplicit)
{
    ASSERT_FALSE((HasNonExplicitCopyConstructor<ExplicitCopyConstructor, int, 5>::value));
}

} // namespace ct
} // namespace utils
} // namespace ut
