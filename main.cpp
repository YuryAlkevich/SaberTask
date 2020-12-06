#include <iostream>

#include "Tasks/Task1.h"
#include "Tasks/Task2.h"
#include "Tasks/Task3.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;
    std::cout << SaberTask::ToBinaryString((int16_t)-13) << std::endl;

    char data[] = "AAAAA_BB_CCCCC_LOL_LOOOOLLLLL";
    SaberTask::RemoveDubs(data);
    std::cout << data << std::endl;

    SaberTask::List list;
    auto& i1 = list.pushBack("ONE");
    list.pushBack("TWO");
    i1.rand = &list.pushFront("PREONE");
    i1.rand->rand = &i1;

    list.pushFront("PREPREONE").rand = &i1;

    for(auto& it : list)
    {
        std::cout << it.data << std::endl;
    }

    auto file = std::fopen("file.bin", "wb");
    list.serialize(file);
    std::fclose(file);

    SaberTask::List newList;
    file = std::fopen("file.bin", "rb");
    newList.deserialize(file);
    std::fclose(file);

    for(auto& it : newList)
    {
        std::cout << it.data << std::endl;
    }

    auto& preone = newList.find("PREONE");
    auto& one = newList.find("ONE");
    std::cout << int(&preone == one.rand)  << std::endl;

    return 0;
}
