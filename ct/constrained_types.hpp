/**
 * @file constrained_types.hpp
 * @author Sebastian Madajczyk, sebastian@madajczyk.net
 * @date 04.05.2014
 */

// Seems to be risky, using traits should minimize or get rid of risk (e.g.
// IsConstrainedType<U>)
template <typename T, typename U>
inline bool operator==(T p1, U p2)
{
    return p2 == p1;
}

template <typename T, typename U>
inline U operator+(T p1, U p2)
{
    return p2 + p1;
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
    private:                                          \
        ValueType value;                              \
    }

namespace ct
{
} // namespace ct
