#pragma once
#include <string>
#include <fstream>
#include <list>
#include "db_jpsnk_desc_box.h"
#include "db_jpsnk_inst_set_box.h"
#include "db_jpsnk_instruction.h"
#include "db_jpsnk_obmb.h"
#include "jpsnk_object.h"

class Encoder
{
public:
	Encoder();
	~Encoder();

	std::string cfg_file_name{ "" };
	std::ifstream cfg_file;

	void initiate(int argc, const char* argv[]);
	void set_background_image_fname(std::string fname);
	void set_output_jpsnk_file_name(std::string fname);
	void set_bg_img_fname_cfg_file();
	void set_output_fname_cfg_file();
	void set_number_of_objects(uint8_t no);
	void set_no_of_object_value();
	void set_start_time_value();
	void set_objects_data();

	list<JPSnackObject*> objects;



private:
	std::string background_image_fname{ "" };
	std::string output_jpsnk_fname{ "" };
	uint32_t start_time{ 0 };
	unsigned char no_of_objects{ 0 };
	std::list<unsigned char> objects_ids;
	dbench::DbJPSnackDescBox desc_box;
	dbench::DbInstSetBox inst_box;
	std::list<dbench::DbObjMetaDataBox*> obj_mdata_boxes;
	std::string get_str_from_cfg_file_for(std::string search_str);
	std::list<dbench::DbJPSnackInstruction> insts_;





};

