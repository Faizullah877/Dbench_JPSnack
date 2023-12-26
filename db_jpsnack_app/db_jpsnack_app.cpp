// db_jpsnack_app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include "db_jpsnk_desc_box.h"


using namespace std;
using namespace dbench;

int main()
{
    list<uint8_t> obj_ids;
    obj_ids.push_back(0x5);

    DbJPSnackDescBox desc_box;
    desc_box.set_box(1, 2000, 1, 1, obj_ids);
    unsigned char* buf = nullptr;
    uint64_t buf_size = 0;
    desc_box.serialize(&buf, &buf_size);

    std::cout << "Hello World!\n";
    return 0;
}
