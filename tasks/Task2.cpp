#include "Task2.h"

void SaberTask::RemoveDubs(char *data)
{
    auto* ptrIn = data;
    auto* ptrOut = data;
    char previousChar = '\0';

    while (*ptrIn != '\0')
    {
        if(*ptrIn == previousChar)
        {
            previousChar = *ptrIn;
            ++ptrIn;
            continue;
        }

        *ptrOut = *ptrIn;
        previousChar = *ptrIn;
        ++ptrOut;
        ++ptrIn;
    }

    *ptrOut = '\0';
}

