/**
 * @file constrained_types.hpp
 * @author Sebastian Madajczyk, sebastian@madajczyk.net
 * @date 04.05.2014
 */

#define CT_COMPUND_ASSIGNMENT_OPERATOR(TypeName, ValueType, op) \
    TypeName& operator op##=(TypeName rhs)                    \
    {                                                         \
      value = TypeName (value op rhs.value).value;            \
      return *this;                                           \
    }                                                         \
                                                              \
    TypeName& operator op##=(ValueType rhs)                   \
    { value = TypeName (value op rhs).value;                  \
      return *this;                                           \
    }                                                         \


#define CT_BINARY_OPERATOR(TypeName, ValueType, op)              \
    ValueType operator op (TypeName rhs) const                \
    { return value op rhs.get(); }                            \
                                                              \
    ValueType operator op(ValueType rhs) const                \
    { return value op rhs; }                                  \


#define CT_BINARY_OPERATOR_EXT(TypeName, ValueType, op)          \
    inline ValueType operator op(ValueType p1, TypeName p2)   \
    {                                                         \
        return p1 op p2.get();                                \
    }                                                         \


#define CT_RELATIONAL_OPERATOR(TypeName, ValueType, op)          \
    bool operator op (TypeName rhs) const                     \
    { return rhs.value op value; }                            \
                                                              \
    bool operator op (ValueType rhs) const                    \
    { return rhs op value; }                                  \

#define CT_RELATIONAL_OPERATOR_EXT(TypeName, ValueType, op)      \
    inline bool operator op (ValueType p1, TypeName p2)       \
    { return p1 op p2.get(); }                                \


#define CONSTRAINED_TYPE(TypeName, ValueType)                \
    class TypeName                                           \
    {                                                        \
    public:                                                  \
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
        CT_RELATIONAL_OPERATOR(TypeName, ValueType, ==)         \
        CT_RELATIONAL_OPERATOR(TypeName, ValueType, !=)         \
                                                             \
        CT_BINARY_OPERATOR(TypeName, ValueType, +)              \
        CT_BINARY_OPERATOR(TypeName, ValueType, *)              \
        CT_BINARY_OPERATOR(TypeName, ValueType, /)              \
        CT_BINARY_OPERATOR(TypeName, ValueType, %)              \
                                                             \
        TypeName& operator++()                               \
        { ++value; return *this; }                           \
                                                             \
        TypeName operator++(int)                             \
        { return TypeName(value++); }                        \
                                                             \
        TypeName& operator--()                               \
        { --value; return *this; }                           \
                                                             \
        TypeName operator--(int)                             \
        { return TypeName(value--); }                        \
                                                             \
        CT_COMPUND_ASSIGNMENT_OPERATOR(TypeName, ValueType, +) \
        CT_COMPUND_ASSIGNMENT_OPERATOR(TypeName, ValueType, -) \
                                                             \
    private:                                                 \
        ValueType value;                                     \
    };                                                       \
                                                             \
    CT_RELATIONAL_OPERATOR_EXT(TypeName, ValueType, ==)         \
    CT_RELATIONAL_OPERATOR_EXT(TypeName, ValueType, !=)         \
                                                             \
    CT_BINARY_OPERATOR_EXT(TypeName, ValueType, /)              \
    CT_BINARY_OPERATOR_EXT(TypeName, ValueType, +)              \
    CT_BINARY_OPERATOR_EXT(TypeName, ValueType, *)              \
    CT_BINARY_OPERATOR_EXT(TypeName, ValueType, %)              \
                                                             \
    struct DUMMY_##TypeName {}

namespace ct
{
} // namespace ct
