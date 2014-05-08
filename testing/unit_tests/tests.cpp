/**
 * @file tests.cpp
 * @author Sebastian Madajczyk, sebastian@madajczyk.net
 * @date 03.05.2014
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <testing/utils/utils.hpp>
#include <ct/constrained_types.hpp>

namespace ct
{

namespace ut
{

CONSTRAINED_TYPE(BoundedInt, int);

TEST(ConstrainedType, shouldBeDefaultConstructible)
{
    BoundedInt v;
    ASSERT_EQ(0, v.get());
}

TEST(ConstrainedType, shouldBeConstructibleByValueOfUnderlyingType)
{
    int i = 5;
    BoundedInt v(i);
    ASSERT_EQ(5, v.get()); 
}

TEST(ConstrainedType, shouldBeConstructibleExplicitly)
{
    ASSERT_FALSE((utils::HasNonExplicitCopyConstructor<BoundedInt, int, 5>::value));
}

TEST(ConstrainedType, shouldBeCopyable)
{
    BoundedInt v1(9);
    BoundedInt v2 = v1;
    BoundedInt v3 = (v1 = v2);

    ASSERT_EQ(v1.get(), v2.get());
    ASSERT_EQ(v1.get(), v3.get());
}

TEST(ConstrainedType, shouldSupportAssignmentOfUnderlyingType)
{
    BoundedInt v1;
    v1 = int(7);
    ASSERT_EQ(7, v1.get());
}

TEST(ConstrainedType, shouldBePossibleToGetValueOfUnderlyingType)
{
    BoundedInt v(5);
    ASSERT_EQ(v.get(), 5);
}

} // namespace ut

} // namespace ct

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
