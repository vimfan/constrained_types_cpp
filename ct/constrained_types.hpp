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
        ValueType operator+(TypeName rhs) const        \
        { return value + rhs.get(); }       \
                                                      \
        ValueType operator+(ValueType rhs) const      \
        { return value + rhs; }                       \
                                                      \
        ValueType operator*(TypeName rhs) const        \
        { return value * rhs.get(); }       \
                                                      \
        ValueType operator*(ValueType rhs) const       \
        { return value * rhs; }             \
                                                      \
        ValueType operator/(TypeName rhs) const        \
        { return value / rhs.get(); }       \
                                                      \
        ValueType operator/(ValueType rhs) const       \
        { return value / rhs; }             \
                                                      \
        TypeName& operator++()                     \
        { ++value; return *this; }                    \
                                                      \
        TypeName operator++(int)                      \
        { const ValueType v = value;                  \
          return TypeName(value++); }                 \
                                                      \
    private:                                          \
                                                      \
        ValueType value;                              \
    };                                                \
                                                      \
    inline ValueType operator/(ValueType p1, TypeName p2) \
    { return p1 / p2.get(); }                  \
                                                         \
    inline bool operator==(ValueType p1, TypeName p2)    \
    { return p1 == p2.get(); }                           \
                                                         \
    inline ValueType operator+(ValueType p1, TypeName p2) \
    { return p1 + p2.get(); }                             \
                                                         \
    inline ValueType operator*(ValueType p1, TypeName p2) \
    { return p1 * p2.get(); }                  \
                                                         \
    struct DUMMY_##TypeName {}

namespace ct
{
} // namespace ct
