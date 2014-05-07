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
    (void) v;
}

TEST(ConstrainedType, shouldBeConstructibleByValueOfUnderlyingType)
{
    int i = 5;
    BoundedInt v(i);
}

TEST(ConstrainedType, shouldBeConstructibleExplicitly)
{
    ASSERT_FALSE((utils::HasNonExplicitCopyConstructor<BoundedInt, int, 5>::value));
}

TEST(ConstrainedType, shouldBeCopyable)
{
    BoundedInt v1(1);
    BoundedInt v2 = v1;
    BoundedInt v3 = (v1 = v2);
}

TEST(ConstrainedType, shouldSupportAssignmentOfUnderlyingType)
{
    BoundedInt v1;
    v1 = int(5);
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
