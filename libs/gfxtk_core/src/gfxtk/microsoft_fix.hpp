#ifndef GFXTK_MICROSOFT_FIX_HPP
#define GFXTK_MICROSOFT_FIX_HPP

#ifdef GFXTK_TARGET_OS_WINDOWS
#ifdef GFXTK_BUILD_LIBRARY
#define GFXTK_EXPORT __declspec(dllexport)
#else
#define GFXTK_EXPORT __declspec(dllimport)
#endif
#else
#define GFXTK_EXPORT
#endif

#endif //GFXTK_MICROSOFT_FIX_HPP
