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

namespace
{

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


} // anonymous namespace

// *** CONSTRUCTION

TEST(ConstrainedTypeConstruction, shouldBeDefaultConstructible)
{
    BoundedInt v;
    ASSERT_EQ(0, v.get());
}

TEST(ConstrainedTypeConstruction, shouldBeConstructibleByValueOfUnderlyingType)
{
    int i = 5;
    BoundedInt v(i);
    ASSERT_EQ(5, v.get()); 
}

TEST(ConstrainedTypeConstruction, shouldBeConstructibleExplicitly)
{
    ASSERT_FALSE((utils::HasNonExplicitCopyConstructor<BoundedInt, int, 5>::value));
}

TEST(ConstrainedTypeConstruction, shouldBeCopyable)
{
    BoundedInt v1(9);
    BoundedInt v2 = v1;
    BoundedInt v3 = (v1 = v2);

    ASSERT_EQ(v1.get(), v2.get());
    ASSERT_EQ(v1.get(), v3.get());
}


// *** RELATIONAL OPERATORS

TEST(ConstrainedTypeRelational, shouldBeEqualComparable)
{
    BoundedInt v1(5);
    BoundedInt v2(5);
    ASSERT_TRUE(v1 == v2);
}

TEST(ConstrainedTypeRelational, shouldBeEqualComparableNotEqual)
{
    BoundedInt v1(5);
    BoundedInt v2(7);
    ASSERT_FALSE(v1 == v2);
}

TEST(ConstrainedTypeRelational, shouldBeEqualComparableWithUnderlyingTypeOnTheRightHand)
{
    BoundedInt v(7);
    ASSERT_TRUE(v == 7);
}

TEST(ConstrainedTypeRelational, shouldBeEqualComparableWithUnderlyingTypeOnTheLeftHand)
{
    BoundedInt v(7);
    ASSERT_TRUE(7 == v);
}

TEST(ConstrainedTypeRelational, shouldBeEqualComparableWithUnderlyingTypeOnTheRightHandNotEqual)
{
    BoundedInt v(7);
    ASSERT_FALSE(v == 8);
}

TEST(ConstrainedTypeRelational, shouldBeInequalComparable)
{
    BoundedInt v1(5);
    BoundedInt v2(7);
    ASSERT_TRUE(v1 != v2);
}

TEST(ConstrainedTypeRelational, shouldBeInequalComparableEqual)
{
    BoundedInt v1(5);
    BoundedInt v2(5);
    ASSERT_FALSE(v1 != v2);
}

TEST(ConstrainedTypeRelational, shouldSupportInequalityOperatorWithValueOfUnderlyingTypeOnRight)
{
    BoundedInt v(5);
    ASSERT_TRUE(v != 6);
}

TEST(ConstrainedTypeRelational, shouldSupportInequalityOperatorWithValueOfUnderlyingTypeOnLeft)
{
    BoundedInt v(5);
    ASSERT_TRUE(6 != v);
}

// *** ASSIGNMENTS OPERATORS

TEST(ConstrainedTypeAssignments, shouldSupportAssignmentOfUnderlyingType)
{
    BoundedInt v1;
    v1 = int(7);
    ASSERT_EQ(7, v1.get());
}

TEST(ConstrainedTypeAssignments, shouldReturnObjectOfConstrainedTypeWhenAssigningValueOfUnderlyingType)
{
    BoundedInt v1(5);
    ASSERT_TRUE(isBoundedInt(v1 = 7));
}

TEST(ConstrainedTypeAssignments, shouldReturnObjectOfConstrainedTypeWhenAssigningValueOfUnderlyingTypeAndItNeedsToBeEqualToAssignedValue)
{
    BoundedInt v1(5);
    ASSERT_TRUE((v1 = 8) == 8);
}

TEST(ConstrainedTypeAssignments, shouldSupportAssignment)
{
    BoundedInt v1(5);
    BoundedInt v2(7);
    v1 = v2;
    ASSERT_TRUE(v1 == 7);
}

TEST(ConstrainedTypeAssignments, shouldReturnValueOfConstrainedTypeWhenAssign)
{
    BoundedInt v1(5);
    BoundedInt v2(7);
    ASSERT_TRUE(isBoundedInt(v1 = v2));
}

TEST(ConstrainedTypeAssignments, shouldReturnTheSameValueAsAssigned)
{
    BoundedInt v1(5);
    BoundedInt v2(7);
    ASSERT_TRUE((v1 = v2) == v2);
}

TEST(ConstrainedTypeAssignments, shouldSupportAdditionAssignment)
{
    BoundedInt v(5);
    v += BoundedInt(5);
    ASSERT_EQ(v, 10);
}

TEST(ConstrainedTypeAssignments, shouldSupportAdditionAssignmentAndReturnTheModifiedValue)
{
    BoundedInt v(7);
    ASSERT_EQ(&v, &(v += BoundedInt(9)));
}

TEST(ConstrainedTypeAssignments, shouldSupportAdditionAssignmentWithValueOfUnderlyingType)
{
    BoundedInt v(8);
    v += 5;
    ASSERT_EQ(v, 5 + 8);
}

TEST(ConstrainedTypeAssignments, shouldSupportAdditionAssignmentWithValueOfUnderlyingTypeAndReturnTheModifiedValue)
{
    BoundedInt v(8);
    ASSERT_EQ(&v, &(v += 5));
}

TEST(ConstrainedTypeAssignments, shouldSupportSubstractionAssignment)
{
    BoundedInt v(5);
    v -= BoundedInt(3);
    ASSERT_EQ(v, 2);
}

TEST(ConstrainedTypeAssignments, shouldSupportSubstractionAssignmentWithValueOfUnderlyingType)
{
    BoundedInt v(5);
    v -= 5;
    ASSERT_EQ(v, 0);
}

// *** ARITHMETIC OPERATORS

TEST(ConstrainedTypeArithmetic, shouldSupportAddition)
{
    BoundedInt v1(7);
    BoundedInt v2(9);
    BoundedInt v3(v1 + v2);

    ASSERT_TRUE(v3 == v1.get() + v2.get());
}

TEST(ConstrainedTypeArithmetic, shouldReturnValueOfUnderlyingTypeWhenAddingTwoValuesOfConstrainedTypes)
{
    BoundedInt v1(5);
    BoundedInt v2(7);
    ASSERT_TRUE(isOfType<int>(v1 + v2));
}

TEST(ConstrainedTypeArithmetic, shouldSupportAdditionOnTheRightHandValueOfUnderlyingType)
{
    BoundedInt v(7);
    BoundedInt v2(v + 5);
    ASSERT_TRUE(v2 == 7 + 5);
}

TEST(ConstrainedTypeArithmetic, shouldPromoteToUnderlyingTypeWhenAddingValueOfUnderlyingTypeOnTheRight)
{
    BoundedInt v(7);
    ASSERT_TRUE(isOfType<int>(v + 5));
}

TEST(ConstrainedTypeArithmetic, shouldSupportAdditionOnTheLeftHandValueOfUnderlyingType)
{
    BoundedInt v(7);
    BoundedInt v2(5 + v);
    ASSERT_TRUE(v2 == 7 + 5);
}

TEST(ConstrainedTypeArithmetic, shouldPromoteToUnderlyingTypeWhenAddingValueOfUnderlyingTypeOnTheLeft)
{
    BoundedInt v(7);
    ASSERT_TRUE(isOfType<int>(5 + v));
}

TEST(ConstrainedTypeArithmetic, shouldSupportMultiplication)
{
    BoundedInt v1(5);
    BoundedInt v2(6);
    ASSERT_TRUE(v1 * v2 == 5 * 6);
}

TEST(ConstrainedTypeArithmetic, shouldReturnValueOfUnderlyingTypeWhenMultiplyValuesOfConstrainedTypes)
{
    ASSERT_TRUE(isOfType<int>(BoundedInt(5) * BoundedInt(7)));
}

TEST(ConstrainedTypeArithmetic, shouldSupportMultiplicationByValueOfUnderlyingTypeOnTheRightHand)
{
    BoundedInt v1(5);
    ASSERT_TRUE(v1 * 8 == 5 * 8);
}

TEST(ConstrainedTypeArithmetic, shouldPromoteToUnderlyingTypeWhenMultiplyByUnderlyingTypeOnTheRight)
{
    BoundedInt v(8);
    ASSERT_TRUE(isOfType<int>(v * 8));
}

TEST(ConstrainedTypeArithmetic, shouldSupportMultiplicationByValueOfUnderlyingTypeOnTheLeftHand)
{
    BoundedInt v1(5);
    ASSERT_TRUE(8 * v1 == 5 * 8);
}

TEST(ConstrainedTypeArithmetic, shouldPromoteToUnderlyingTypeWhenMultiplyByUnderlyingTypeOnTheLeft)
{
    BoundedInt v(8);
    ASSERT_TRUE(isOfType<int>(8 * v));
}

TEST(ConstrainedTypeArithmetic, shouldSupportDivision)
{
    BoundedInt v1(6);
    BoundedInt v2(2);
    ASSERT_TRUE(v1 / v2 == 3);
}

TEST(ConstrainedTypeArithmetic, shouldReturnValueOfUnderlyingTypeWhenDividingTwoConstrainedTypes)
{
    BoundedInt v1(6);
    BoundedInt v2(2);
    ASSERT_TRUE(isOfType<int>(v1 / v2));
}

TEST(ConstrainedTypeArithmetic, shouldSupportDivisionByValueOfUnderlyingTypeOnTheRightHand)
{
    BoundedInt v1(6);
    ASSERT_TRUE(v1 / 2 == 3);
}

TEST(ConstrainedTypeArithmetic, shouldPromoteToUnderlyingTypeWhenDividingValueOfUnderlyingTypeOnTheRight)
{
    BoundedInt v1(6);
    ASSERT_TRUE(isOfType<int>(v1 / 2));
}

TEST(ConstrainedTypeArithmetic, shouldSupportDivisionOfUnderlyingTypeByTheConstrainedType)
{
    BoundedInt v(3);
    ASSERT_TRUE(27 / v == 9);
}

TEST(ConstrainedTypeArithmetic, shouldPromoteToUnderlyingTypeWhenDividingValueOfUnderlyingTypeOnTheLeft)
{
    ASSERT_TRUE(isOfType<int>(2 / BoundedInt(2)));
}

TEST(ConstrainedTypeArithmetic, shouldSupportModulusOperation)
{
    BoundedInt v1(6);
    BoundedInt v2(4);
    ASSERT_TRUE(v1 % v2 == 6 % 4);
}

TEST(ConstrainedTypeArithmetic, shouldSupportModulusOperationWhenUnderlyingTypeIsOnRight)
{
    BoundedInt v1(6);
    int v2(4);
    ASSERT_TRUE(v1 % v2 == 6  % 4);
}

TEST(ConstrainedTypeArithmetic, shouldSupportModulusOperationWhenUnderlyingTypeIsOnLeft)
{
    BoundedInt v1(8);
    int v2(10);
    ASSERT_TRUE(v2 % v1 == 10 % 8);
}

TEST(ConstrainedTypeArithmetic, shouldPromoteToUnderlyingTypeWhenApplyingOperatorModulus)
{
    BoundedInt v1(8);
    int v2(10);
    ASSERT_TRUE(isOfType<int>(v2 % v1));
    ASSERT_TRUE(isOfType<int>(v1 % v2));
    ASSERT_TRUE(isOfType<int>(v1 % v1));
}

// *** INCREMENTATION OPERATORS

TEST(ConstrainedTypeIncrementations, shouldSupportPreincrementation)
{
    BoundedInt v(3);
    ++v;
    ASSERT_EQ(4, v);
}

TEST(ConstrainedTypeIncrementations, shouldReturnTheSameObjectInCaseOfPreincrementation)
{
    BoundedInt v(3);
    BoundedInt* vPtr1 = &v;
    BoundedInt* vPtr2 = &(++v);
    ASSERT_EQ(vPtr1, vPtr2);
}

TEST(ConstrainedTypeIncrementations, shouldSupportPostincrementation)
{
    BoundedInt v1(3);
    BoundedInt v2 = v1++;
    ASSERT_EQ(v2, 3);
    ASSERT_EQ(v1, 4);
}

TEST(ConstrainedTypeIncrementations, shouldValueReturnedAfterPostIncrementationBeOfConstrainedType)
{
    BoundedInt v1(3);
    ASSERT_TRUE(isOfType<BoundedInt>(v1++));
}

TEST(ConstrainedTypeIncrementations, shouldSupportPredecrementation)
{
    BoundedInt v(3);
    --v;
    ASSERT_EQ(2, v);
}

TEST(ConstrainedTypeIncrementations, shouldReturnTheSameObjectInCaseOfPredecrementation)
{
    BoundedInt v(5);
    BoundedInt* vPtr1 = &v;
    BoundedInt* vPtr2 = &(--v);
    ASSERT_EQ(vPtr1, vPtr2);
}

TEST(ConstrainedTypeIncrementations, shouldSupportPostdecrementation)
{
    BoundedInt v1(3);
    BoundedInt v2 = v1--;
    ASSERT_EQ(v2, 3);
    ASSERT_EQ(v1, 2);
}


// ** OTHER

TEST(ConstrainedTypeOther, shouldBePossibleToGetValueOfUnderlyingType)
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
