/**
 * @file constrained_types.hpp
 * @author Sebastian Madajczyk, sebastian@madajczyk.net
 * @date 04.05.2014
 */

// Seems to be risky, using traits should minimize or get rid of risk (e.g.
// IsConstrainedType<U>), on the other hand could have huge impact on compilation times

template <typename T, typename U>
inline U operator+(T p1, U p2)
{
    return p2 + p1;
}

template <typename T, typename U>
inline U operator*(T p1, U p2)
{
    return p2 * p1; 
}

// risky end

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
    struct DUMMY_##TypeName {}

namespace ct
{
} // namespace ct
