#include <iostream>

#include "Task1.h"
#include "Task2.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;
    std::cout << SaberTask::ToBinaryString((int16_t)-13) << std::endl;

    char data[] = "AAAAA_BB_CCCCC_LOL_LOOOOLLLLL";
    SaberTask::RemoveDubs(data);
    std::cout << data << std::endl;

    return 0;
}
