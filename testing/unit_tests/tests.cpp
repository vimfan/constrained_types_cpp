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

template <typename T, typename U>
bool isOfType(U)
{
    return typeid(T) == typeid(U);
}

template <typename T>
bool isBoundedInt(T expr)
{
    return isOfType<BoundedInt>(expr);
}

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

TEST(ConstrainedType, shouldSupportComparison)
{
    BoundedInt v(5);
    ASSERT_TRUE(v == v);
}

TEST(ConstrainedType, shouldSupportComparisonToUnderlyingTypeWhenSimpleTypeIsOnLeft)
{
    BoundedInt v(7);
    ASSERT_TRUE(7 == v);
}

TEST(ConstrainedType, shouldSupportComparisonToUnderlyingTypeWhenSimpleTypeIsOnRight)
{
    BoundedInt v(7);
    ASSERT_TRUE(v == 7);
}

TEST(ConstrainedType, shouldSupportAddition)
{
    BoundedInt v1(7);
    BoundedInt v2(9);
    BoundedInt v3 = v1 + v2;

    ASSERT_TRUE(v3 == v1.get() + v2.get());
}

TEST(ConstrainedType, shouldSupportAdditionOnTheRightHandValueOfUnderlyingType)
{
    BoundedInt v(7);
    BoundedInt v2(v + 5);
    ASSERT_TRUE(v2 == 7 + 5);
}

TEST(ConstrainedType, shouldSupportPromotionToUnderlyingTypeWhenAddingValueOfUnderlyingTypeOnTheRight)
{
    BoundedInt v(7);
    ASSERT_TRUE(isOfType<int>(v + 5));
}

TEST(ConstrainedType, shouldSupportAdditionOnTheLeftHandValueOfUnderlyingType)
{
    BoundedInt v(7);
    BoundedInt v2(5 + v);
    ASSERT_TRUE(v2 == 7 + 5);
}

TEST(ConstrainedType, shouldSupportPromotionToUnderlyingTypeWhenAddingValueOfUnderlyingTypeOnTheLeft)
{
    BoundedInt v(7);
    ASSERT_TRUE(isOfType<int>(5 + v));
}

TEST(ConstrainedType, shouldSupportMultiplication)
{
    BoundedInt v1(5);
    BoundedInt v2(6);
    
    ASSERT_TRUE(v1 * v2 == 5 * 6);
    ASSERT_TRUE(isBoundedInt(v1 * v2));
}

TEST(ConstrainedType, shouldSupportMultiplicationByValueOfUnderlyingTypeOnTheRightHand)
{
    BoundedInt v1(5);
    ASSERT_TRUE(v1 * 8 == 5 * 8);
}

TEST(ConstrainedType, shouldSupportPromotionToUnderlyingTypeWhenMultiplyByUnderlyingTypeOnTheRight)
{
    BoundedInt v(8);
    ASSERT_TRUE(isOfType<int>(v * 8));
}

TEST(ConstrainedType, shouldSupportMultiplicationByValueOfUnderlyingTypeOnTheLeftHand)
{
    BoundedInt v1(5);
    ASSERT_TRUE(8 * v1 == 5 * 8);
    ASSERT_TRUE(isBoundedInt(8 * v1));
}

TEST(ConstrainedType, shouldSupportDivision)
{
    BoundedInt v1(6);
    BoundedInt v2(2);
    ASSERT_TRUE(v1 / v2 == 3);
    ASSERT_TRUE(isBoundedInt(v1 / v2));
}

TEST(ConstrainedType, shouldSupportDivisionByValueOfUnderlyingTypeOnTheRightHand)
{
    BoundedInt v1(6);
    ASSERT_TRUE(v1 / 2 == 3);
    ASSERT_TRUE(isBoundedInt(v1 / 2));
}

TEST(ConstrainedType, shouldSupportDivisionOfUnderlyingTypeByTheConstrainedType)
{
    BoundedInt v(3);
    ASSERT_TRUE(27 / v == 9);
    ASSERT_TRUE(isBoundedInt(9 / v));
}

} // namespace ut

} // namespace ct

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
