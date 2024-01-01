// db_jpsnack_app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include "db_jpsnk_desc_box.h"
#include "db_jpsnk_instruction.h"
#include "db_jpsnk_inst_set_box.h"
#include "db_jpsnk_obmb.h"
#include "db_jpsnack_jumbf.h"


using namespace std;
using namespace dbench;

int main()
{
    list<uint8_t> obj_ids;
    obj_ids.push_back(5);

    DbJPSnackDescBox jpsnk_desc_box;
    jpsnk_desc_box.set_box(2000, 1, obj_ids);

    DbJPSnackInstruction* inst = new DbJPSnackInstruction;
    inst->set_xo_yo(0, 0);
    inst->set_width_height(512, 256);
    inst->set_persist_life_nextuse(0, 12, 0);

    DbInstSetBox inst_set_box;
    inst_set_box.set_repetition(1);
    inst_set_box.set_tick(1000);
    inst_set_box.set_xo_yo_flag(true);
    inst_set_box.set_width_height_flag(true);
    inst_set_box.set_persist_life_nextuse_flag(true);
    inst_set_box.insert_instruction(inst);


    DbObjMetaDataBox box;

    box.set_object_id(5);
    box.set_media_type("image/jpg");
    box.set_no_of_media(6);
    box.add_location("self#jumbf=Object1");
    box.add_location("self#jumbf=Object2");
    box.add_location("self#jumbf=Object3");
    box.add_location("self#jumbf=Object4");
    box.add_location("self#jumbf=Object5");
    box.add_location("self#jumbf=Object6");

    DbJPSnackJumbBox jumbf_box;
    jumbf_box.set_jpsnk_desc_box(&jpsnk_desc_box);
    jumbf_box.set_jpsnk_inst_box(&inst_set_box);
    jumbf_box.insert_object_metadata_box(&box);

    unsigned char* jumbf_buf{ nullptr };
    uint64_t jumbf_buf_size{ 0 };
    jumbf_box.serialize(&jumbf_buf, &jumbf_buf_size);

    delete[] jumbf_buf;


    std::cout << "Hello World!\n";
    return 0;
}
