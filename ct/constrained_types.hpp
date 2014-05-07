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
    private:                                          \
        ValueType value;                              \
    }

namespace ct
{
} // namespace ct
