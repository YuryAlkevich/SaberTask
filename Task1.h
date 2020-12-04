#ifndef SABERTASK_TASK1_H
#define SABERTASK_TASK1_H

#include <string>

namespace SaberTask
{
    template<typename T, class = std::is_integral<T>>
    std::string ToBinaryString(T value)
    {
        std::string buffer(sizeof(T) * 8, '0');

        auto strLength = buffer.length();
        for(size_t i = 0, j = strLength - 1; i < strLength; ++i, --j)
        {
            if(value & (0x1 << i))
                buffer[j] = '1';
        }

        return buffer;
    }
}

#endif //SABERTASK_TASK1_H
