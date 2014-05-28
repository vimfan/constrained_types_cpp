/**
 * @file constrained_types.hpp
 * @author Sebastian Madajczyk, sebastian@madajczyk.net
 * @date 04.05.2014
 */

#define CT_COMPUND_ASSIGNMENT_OPERATOR(T, op)                 \
    T& operator op##=(T rhs)                                  \
    {                                                         \
      value = T (value op rhs.value).value;                   \
      return *this;                                           \
    }                                                         \
                                                              \
    T& operator op##=(T::value_type rhs)                      \
    { value = T (value op rhs).value;                         \
      return *this;                                           \
    }                                                         \

#define CT_INNER_COMPUND_ASSIGNMENT_OPERATOR(op)              \
    CT_COMPUND_ASSIGNMENT_OPERATOR(type, op)

#define CT_BINARY_OPERATOR(T, op)                             \
    T::value_type operator op (T rhs) const                   \
    { return value op rhs.get(); }                            \
                                                              \
    T::value_type operator op(T::value_type rhs) const        \
    { return value op rhs; }                                  \


#define CT_BINARY_OPERATOR_EXT(T, op)                         \
    inline T::value_type operator op(T::value_type p1, T p2)  \
    {                                                         \
        return p1 op p2.get();                                \
    }                                                         \


#define CT_RELATIONAL_OPERATOR(T, op)                         \
    bool operator op (T rhs) const                            \
    { return value op rhs.value; }                            \
                                                              \
    bool operator op (T::value_type rhs) const                \
    { return value op rhs; }                                  \


#define CT_RELATIONAL_OPERATOR_EXT(T, op)                     \
    inline bool operator op (T::value_type p1, T p2)          \
    { return p1 op p2.get(); }                                \

#define CT_LOGICAL_OPERATOR_EXT(T, op)                        \
    CT_RELATIONAL_OPERATOR_EXT(T, op)

#define CT_INNER_BINARY_OPERATOR(op)                          \
    CT_BINARY_OPERATOR(type, op)
    
#define CT_INNER_RELATIONAL_OPERATOR(op)                      \
    CT_RELATIONAL_OPERATOR(type, op)

#define CT_INNER_LOGICAL_OPERATOR(op)                         \
    CT_INNER_RELATIONAL_OPERATOR(op)

#define CT_PRE_CREMENT(T, op)                                 \
    T& operator op ()                                         \
    { op value; return *this; }                               \

#define CT_INNER_PRE_CREMENT(op)                              \
    CT_PRE_CREMENT(type, op)

#define CT_POST_CREMENT(T, op)                                \
    T operator op (int)                                       \
    { return T(value op); }                                   \

#define CT_INNER_POST_CREMENT(op)                             \
    CT_POST_CREMENT(type, op)

#define CT_UNARY_OPERATOR(T, op)                             \
    T::value_type operator op(void) const                    \
    { return op value; }                                     \


#define CT_INNER_UNARY_OPERATOR(op)                          \
    CT_UNARY_OPERATOR(type, op)


#define CONSTRAINED_TYPE(TypeName, ValueType)                \
    class TypeName                                           \
    {                                                        \
        typedef TypeName type;                               \
                                                             \
    public:                                                  \
                                                             \
        typedef ValueType value_type;                        \
                                                             \
        TypeName() : value(0) {}                             \
                                                             \
        explicit TypeName(ValueType val)                     \
            : value(val)                                     \
        {}                                                   \
                                                             \
        TypeName& operator=(const TypeName& rhs)             \
        {                                                    \
            value = rhs.value;                               \
            return *this;                                    \
        }                                                    \
                                                             \
        TypeName& operator=(ValueType val)                   \
        {                                                    \
            value = val;                                     \
            return *this;                                    \
        }                                                    \
                                                             \
        ValueType get() const { return value; }              \
                                                             \
        /* RELATIONAL OPERATORS */                           \
        CT_INNER_RELATIONAL_OPERATOR(==)                     \
        CT_INNER_RELATIONAL_OPERATOR(!=)                     \
        CT_INNER_RELATIONAL_OPERATOR(>)                      \
        CT_INNER_RELATIONAL_OPERATOR(<)                      \
        CT_INNER_RELATIONAL_OPERATOR(<=)                     \
        CT_INNER_RELATIONAL_OPERATOR(>=)                     \
                                                             \
        /* LOGICAL OPERATORS */                              \
        CT_INNER_LOGICAL_OPERATOR(||)                        \
        CT_INNER_LOGICAL_OPERATOR(&&)                        \
                                                             \
        /* ARITHMETIC OPERATORS */                           \
        CT_INNER_BINARY_OPERATOR(+)                          \
        CT_INNER_BINARY_OPERATOR(-)                          \
        CT_INNER_BINARY_OPERATOR(*)                          \
        CT_INNER_BINARY_OPERATOR(/)                          \
        CT_INNER_BINARY_OPERATOR(%)                          \
                                                             \
        CT_INNER_UNARY_OPERATOR(-)                           \
                                                             \
        /* BITWISE OPERATORS */                              \
        CT_INNER_BINARY_OPERATOR(^)                          \
        CT_INNER_BINARY_OPERATOR(|)                          \
        CT_INNER_BINARY_OPERATOR(&)                          \
        CT_INNER_BINARY_OPERATOR(<<)                         \
        CT_INNER_BINARY_OPERATOR(>>)                         \
                                                             \
        CT_INNER_UNARY_OPERATOR(~)                           \
                                                             \
        /* (INC/DEC)REMENTATION OPERATORS */                 \
        CT_INNER_PRE_CREMENT(++)                             \
        CT_INNER_POST_CREMENT(++)                            \
        CT_INNER_PRE_CREMENT(--)                             \
        CT_INNER_POST_CREMENT(--)                            \
                                                             \
        /* COMPOUND ASSIGNMENT OPERATORS */                  \
        CT_INNER_COMPUND_ASSIGNMENT_OPERATOR(+)              \
        CT_INNER_COMPUND_ASSIGNMENT_OPERATOR(-)              \
        CT_INNER_COMPUND_ASSIGNMENT_OPERATOR(*)              \
        CT_INNER_COMPUND_ASSIGNMENT_OPERATOR(%)              \
        CT_INNER_COMPUND_ASSIGNMENT_OPERATOR(/)              \
        CT_INNER_COMPUND_ASSIGNMENT_OPERATOR(&)              \
        CT_INNER_COMPUND_ASSIGNMENT_OPERATOR(|)              \
        CT_INNER_COMPUND_ASSIGNMENT_OPERATOR(^)              \
        CT_INNER_COMPUND_ASSIGNMENT_OPERATOR(<<)             \
        CT_INNER_COMPUND_ASSIGNMENT_OPERATOR(>>)             \
                                                             \
    private:                                                 \
        ValueType value;                                     \
    };                                                       \
                                                             \
    CT_RELATIONAL_OPERATOR_EXT(TypeName, ==)                 \
    CT_RELATIONAL_OPERATOR_EXT(TypeName, !=)                 \
                                                             \
    CT_LOGICAL_OPERATOR_EXT(TypeName, ||)                    \
    CT_LOGICAL_OPERATOR_EXT(TypeName, &&)                    \
                                                             \
    CT_BINARY_OPERATOR_EXT(TypeName, +)                      \
    CT_BINARY_OPERATOR_EXT(TypeName, -)                      \
    CT_BINARY_OPERATOR_EXT(TypeName, *)                      \
    CT_BINARY_OPERATOR_EXT(TypeName, /)                      \
    CT_BINARY_OPERATOR_EXT(TypeName, %)                      \
                                                             \
    CT_BINARY_OPERATOR_EXT(TypeName, &)                      \
    CT_BINARY_OPERATOR_EXT(TypeName, ^)                      \
    CT_BINARY_OPERATOR_EXT(TypeName, |)                      \
    CT_BINARY_OPERATOR_EXT(TypeName, <<)                     \
    CT_BINARY_OPERATOR_EXT(TypeName, >>)                     \
                                                             \
    struct DUMMY_##TypeName {}

namespace ct
{
} // namespace ct
