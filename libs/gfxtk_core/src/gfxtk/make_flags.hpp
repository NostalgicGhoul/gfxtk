#ifndef GFXTK_MAKE_FLAGS_HPP
#define GFXTK_MAKE_FLAGS_HPP

#include <type_traits>

// TODO: Since these are `inline` they shouldn't need `GFXTK_EXPORT` right? If they do need that then that will be
//       annoying to implement
#define GFXTK_MAKE_ENUM_CLASS_FLAG(Flags) \
    inline Flags operator|(Flags lhs, Flags rhs) { \
        return static_cast<Flags>( \
                static_cast<std::underlying_type<Flags>::type>(lhs) | \
                static_cast<std::underlying_type<Flags>::type>(rhs) \
        ); \
    } \
    inline Flags operator&(Flags lhs, Flags rhs) { \
        return static_cast<Flags>( \
                static_cast<std::underlying_type<Flags>::type>(lhs) & \
                static_cast<std::underlying_type<Flags>::type>(rhs) \
        ); \
    } \
    inline Flags operator^(Flags lhs, Flags rhs) { \
        return static_cast<Flags>( \
                static_cast<std::underlying_type<Flags>::type>(lhs) ^ \
                static_cast<std::underlying_type<Flags>::type>(rhs) \
        ); \
    } \
    inline Flags& operator|=(Flags& lhs, Flags rhs) { \
        return reinterpret_cast<Flags&>( \
                reinterpret_cast<std::underlying_type<Flags>::type&>(lhs) |= \
                static_cast<std::underlying_type<Flags>::type>(rhs) \
        ); \
    } \
    inline Flags& operator&=(Flags& lhs, Flags rhs) { \
        return reinterpret_cast<Flags&>( \
                reinterpret_cast<std::underlying_type<Flags>::type&>(lhs) &= \
                static_cast<std::underlying_type<Flags>::type>(rhs) \
        ); \
    } \
    inline Flags& operator^=(Flags& lhs, Flags rhs) { \
        return reinterpret_cast<Flags&>( \
                reinterpret_cast<std::underlying_type<Flags>::type&>(lhs) ^= \
                static_cast<std::underlying_type<Flags>::type>(rhs) \
        ); \
    }

#endif //GFXTK_MAKE_FLAGS_HPP
