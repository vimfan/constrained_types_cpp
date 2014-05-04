/**
 * @file utils.hpp
 * @author Sebastian Madajczyk, sebastian@madajczyk.net
 * @date 04.05.2014
 */

namespace ct
{

namespace utils
{

typedef char yes[1];
typedef char no[2];

template <typename T, typename C, C val>
class HasNonExplicitCopyConstructor
{
public:
    static yes& test(T p_id);
    static no& test(...);

    static const bool value = (sizeof(test(val)) == sizeof(yes));
};

} // namespace utils

} // namespace ct
