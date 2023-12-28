// db_jpsnack_app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include "db_jpsnk_desc_box.h"
#include "db_jpsnk_instruction.h"
#include "db_jpsnk_inst_set_box.h"
#include "db_jpsnk_obmb.h"


using namespace std;
using namespace dbench;

int main()
{
    //list<uint8_t> obj_ids;
    //obj_ids.push_back(0x5);
    //obj_ids.push_back(10);
    //obj_ids.push_back(15);

    //DbJPSnackDescBox jpsnk_desc_box;
    //jpsnk_desc_box.set_box(2000, 3, obj_ids);
    //unsigned char* buf = nullptr;
    //uint64_t buf_size = 0;
    //jpsnk_desc_box.serialize(&buf, &buf_size);

    //DbJPSnackInstruction* inst = new DbJPSnackInstruction;
    //inst->set_xo_yo(0, 0);
    //inst->set_width_height(512, 256);
    //inst->set_persist_life_nextuse(0, 12, 0);

    //DbInstSetBox inst_set_box;
    //inst_set_box.set_repetition(1);
    //inst_set_box.set_tick(1000);
    //inst_set_box.set_xo_yo_flag(true);
    //inst_set_box.set_width_height_flag(true);
    //inst_set_box.set_persist_life_nextuse_flag(true);
    //inst_set_box.insert_instruction(inst);

    //unsigned char* buf2 = nullptr;
    //uint64_t buf_size2 = 0;
    //inst_set_box.serialize(&buf2, &buf_size2);
    //
    //delete[] buf2;
    //delete inst;

    DbObjMetaDataBox box;

    box.set_object_id(1);
    box.set_media_type("image/jpg");
    box.set_no_of_media(6);
    box.add_location("self#jumbf=Object1");
    box.add_location("self#jumbf=Object2");
    box.add_location("self#jumbf=Object3");
    box.add_location("self#jumbf=Object4");
    box.add_location("self#jumbf=Object5");
    box.add_location("self#jumbf=Object6");


    unsigned char* buf3 = nullptr;
    uint64_t buf_size3 = 0;
    box.serialize(&buf3, &buf_size3);
    
    delete[] buf3;



    std::cout << "Hello World!\n";
    return 0;
}
