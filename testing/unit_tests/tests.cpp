/**
 * @file tests.cpp
 * @author Sebastian Madajczyk, sebastian@madajczyk.net
 * @date 03.05.2014
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <ct/constrained_types.hpp>


TYPE(BoundedInt, int);

TEST(ConstrainedType, shouldBeDefaultConstructible)
{
    BoundedInt v;
    (void) v;
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
