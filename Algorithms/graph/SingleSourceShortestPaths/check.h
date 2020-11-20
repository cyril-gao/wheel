#ifndef CHECK_H_76934B8E_E66F_48C7_9FBE_BF62C0186A74
#define CHECK_H_76934B8E_E66F_48C7_9FBE_BF62C0186A74

#include <stdio.h>
#include <stdarg.h>
#include <stdexcept>

inline void examine(bool b, const char* format, ...)
{
    if (!b) {
        char buffer[4096];
        va_list args;
        va_start(args, format);
        //vfprintf(stderr, format, args);
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        throw std::runtime_error(buffer);
    }
}

#endif //CHECK_H_76934B8E_E66F_48C7_9FBE_BF62C0186A74
