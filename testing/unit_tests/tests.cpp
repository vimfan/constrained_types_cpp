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

TEST(ConstrainedType, shouldBeEqualComparable)
{
    BoundedInt v1(5);
    BoundedInt v2(5);
    ASSERT_TRUE(v1 == v2);
}

TEST(ConstrainedType, shouldBeEqualComparableNotEqual)
{
    BoundedInt v1(5);
    BoundedInt v2(7);
    ASSERT_FALSE(v1 == v2);
}

TEST(ConstrainedType, shouldBeEqualComparableWithUnderlyingTypeOnTheRightHand)
{
    BoundedInt v(7);
    ASSERT_TRUE(v == 7);
}

TEST(ConstrainedType, shouldBeEqualComparableWithUnderlyingTypeOnTheLeftHand)
{
    BoundedInt v(7);
    ASSERT_TRUE(7 == v);
}

TEST(ConstrainedType, shouldBeEqualComparableWithUnderlyingTypeOnTheRightHandNotEqual)
{
    BoundedInt v(7);
    ASSERT_FALSE(v == 8);
}

TEST(ConstrainedType, shouldBeInequalComparable)
{
    BoundedInt v1(5);
    BoundedInt v2(7);
    ASSERT_TRUE(v1 != v2);
}

TEST(ConstrainedType, shouldBeInequalComparableEqual)
{
    BoundedInt v1(5);
    BoundedInt v2(5);
    ASSERT_FALSE(v1 != v2);
}

TEST(ConstrainedType, shouldSupportInequalityOperatorWithValueOfUnderlyingTypeOnRight)
{
    BoundedInt v(5);
    ASSERT_TRUE(v != 6);
}

TEST(ConstrainedType, shouldSupportInequalityOperatorWithValueOfUnderlyingTypeOnLeft)
{
    BoundedInt v(5);
    ASSERT_TRUE(6 != v);
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

TEST(ConstrainedType, shouldSupportAddition)
{
    BoundedInt v1(7);
    BoundedInt v2(9);
    BoundedInt v3(v1 + v2);

    ASSERT_TRUE(v3 == v1.get() + v2.get());
}

TEST(ConstrainedType, shouldReturnValueOfUnderlyingTypeWhenAddingTwoValuesOfConstrainedTypes)
{
    BoundedInt v1(5);
    BoundedInt v2(7);
    ASSERT_TRUE(isOfType<int>(v1 + v2));
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
}

TEST(ConstrainedType, shouldReturnValueOfUnderlyingTypeWhenMultiplyValuesOfConstrainedTypes)
{
    ASSERT_TRUE(isOfType<int>(BoundedInt(5) * BoundedInt(7)));
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
}

TEST(ConstrainedType, shouldSupportPromotionToUnderlyingTypeWhenMultiplyByUnderlyingTypeOnTheLeft)
{
    BoundedInt v(8);
    ASSERT_TRUE(isOfType<int>(8 * v));
}

TEST(ConstrainedType, shouldSupportDivision)
{
    BoundedInt v1(6);
    BoundedInt v2(2);
    ASSERT_TRUE(v1 / v2 == 3);
}

TEST(ConstrainedType, shouldReturnValueOfUnderlyingTypeWhenDividingTwoConstrainedTypes)
{
    BoundedInt v1(6);
    BoundedInt v2(2);
    ASSERT_TRUE(isOfType<int>(v1 / v2));
}

TEST(ConstrainedType, shouldSupportDivisionByValueOfUnderlyingTypeOnTheRightHand)
{
    BoundedInt v1(6);
    ASSERT_TRUE(v1 / 2 == 3);
}

TEST(ConstrainedType, shouldSupportPromotionToUnderlyingTypeWhenDividingValueOfUnderlyingTypeOnTheRight)
{
    BoundedInt v1(6);
    ASSERT_TRUE(isOfType<int>(v1 / 2));
}

TEST(ConstrainedType, shouldSupportDivisionOfUnderlyingTypeByTheConstrainedType)
{
    BoundedInt v(3);
    ASSERT_TRUE(27 / v == 9);
}

TEST(ConstrainedType, shouldSupportPromotionToUnderlyingTypeWhenDividingValueOfUnderlyingTypeOnTheLeft)
{
    ASSERT_TRUE(isOfType<int>(2 / BoundedInt(2)));
}

TEST(ConstrainedType, shouldSupportPreincrementation)
{
    BoundedInt v(3);
    ++v;
    ASSERT_EQ(4, v);
}

TEST(ConstrainedType, shouldReturnTheSameObjectInCaseOfPreincrementation)
{
    BoundedInt v(3);
    BoundedInt* vPtr1 = &v;
    BoundedInt* vPtr2 = &(++v);
    ASSERT_EQ(vPtr1, vPtr2);
}

TEST(ConstrainedType, shouldSupportPostincrementation)
{
    BoundedInt v1(3);
    BoundedInt v2 = v1++;
    ASSERT_EQ(v2, 3);
    ASSERT_EQ(v1, 4);
}

TEST(ConstrainedType, shouldValueReturnedAfterPostIncrementationBeOfConstrainedType)
{
    BoundedInt v1(3);
    ASSERT_TRUE(isOfType<BoundedInt>(v1++));
}

TEST(ConstrainedType, shouldSupportPredecrementation)
{
    BoundedInt v(3);
    --v;
    ASSERT_EQ(2, v);
}

TEST(ConstrainedType, shouldReturnTheSameObjectInCaseOfPredecrementation)
{
    BoundedInt v(5);
    BoundedInt* vPtr1 = &v;
    BoundedInt* vPtr2 = &(--v);
    ASSERT_EQ(vPtr1, vPtr2);
}

TEST(ConstrainedType, shouldSupportPostdecrementation)
{
    BoundedInt v1(3);
    BoundedInt v2 = v1--;
    ASSERT_EQ(v2, 3);
    ASSERT_EQ(v1, 2);
}


} // namespace ut

} // namespace ct

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
