#pragma once
#include <string>
#include <list>
#include "db_jpsnk_desc_box.h"
#include "db_jpsnk_inst_set_box.h"

class Encoder
{
public:
	Encoder();
	~Encoder();

	std::string cfg_file_name{ "" };
	fstream cfg_file;

	void initiate(int argc, const char* argv[]);
	void set_background_image_fname(std::string fname);
	void set_bg_img_fname_cfg_file();
	void set_output_fname_cfg_file();


private:
	std::string background_image_fname{ "" };
	std::string output_jpsnk_fname{ "" };
	unsigned char no_of_objects{ 0 };
	std::list<unsigned char> objects_ids;
	dbench::DbJPSnackDescBox desc_box;
	dbench::DbInstSetBox inst_box;




};

