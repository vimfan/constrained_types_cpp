/**
 * @file constrained_types.hpp
 * @author Sebastian Madajczyk, sebastian@madajczyk.net
 * @date 04.05.2014
 */

#define CONSTRAINED_TYPE(TypeName, baseType)          \
    class TypeName                                    \
    {                                                 \
    public:                                           \
        TypeName() {}                                 \
                                                      \
        explicit TypeName(baseType)                   \
        {}                                            \
    }

namespace ct
{
} // namespace ct
