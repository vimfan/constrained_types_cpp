/**
 * @file constrained_types.hpp
 * @author Sebastian Madajczyk, sebastian@madajczyk.net
 * @date 04.05.2014
 */

#define CONSTRAINED_TYPE(TypeName, ValueType)         \
    class TypeName                                    \
    {                                                 \
    public:                                           \
        TypeName() : value(0) {}                      \
                                                      \
        explicit TypeName(ValueType val)              \
            : value(val)                              \
        {}                                            \
                                                      \
        TypeName& operator=(ValueType val)            \
        {                                             \
            value = val;                              \
            return *this;                             \
        }                                             \
                                                      \
        ValueType get() const { return value; }       \
                                                      \
        bool operator==(const TypeName rhs) const     \
        { return rhs.value == value; }                \
                                                      \
        bool operator==(ValueType rhs) const          \
        { return rhs == value; }                      \
                                                      \
        TypeName operator+(TypeName rhs) const        \
        { return TypeName(value + rhs.get()); }       \
                                                      \
        TypeName operator+(ValueType rhs) const       \
        { return TypeName(value + rhs); }             \
                                                      \
        TypeName operator*(TypeName rhs) const        \
        { return TypeName(value * rhs.get()); }       \
                                                      \
        TypeName operator*(ValueType rhs) const       \
        { return TypeName(value * rhs); }             \
                                                      \
        TypeName operator/(TypeName rhs) const        \
        { return TypeName(value / rhs.get()); }       \
                                                      \
        TypeName operator/(ValueType rhs) const       \
        { return TypeName(value / rhs); }             \
                                                      \
    private:                                          \
        ValueType value;                              \
    };                                                \
                                                      \
    inline TypeName operator/(ValueType p1, TypeName p2) \
    { return TypeName(p1 / p2.get()); }                  \
                                                         \
    inline bool operator==(ValueType p1, TypeName p2)    \
    { return p1 == p2.get(); }                           \
                                                         \
    inline TypeName operator+(ValueType p1, TypeName p2) \
    { return TypeName(p1 + p2.get()); }                  \
                                                         \
    inline TypeName operator*(ValueType p1, TypeName p2) \
    { return TypeName(p1 * p2.get()); }                  \
                                                         \
    struct DUMMY_##TypeName {}

namespace ct
{
} // namespace ct
