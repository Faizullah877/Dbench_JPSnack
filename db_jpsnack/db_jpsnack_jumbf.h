#pragma once
#include <list>
#include "db_box.h"
#include "db_jumb_box.h"
#include "db_jpsnk_desc_box.h"
#include "db_jpsnk_inst_set_box.h"
#include "db_jpsnk_obmb.h"

namespace dbench {

class DbJPSnackJumbBox : DbJumbBox
{
public:
	DbJPSnackJumbBox();
	~DbJPSnackJumbBox();
	void set_jpsnk_desc_box(DbJPSnackDescBox* jpsnk_desc_box);
	void set_jpsnk_inst_box(DbInstSetBox* inst_box);
	void insert_object_metadata_box(DbObjMetaDataBox* obj_mdata_box);

	void set_box_size();
	uint64_t get_box_size();
	void serialize(unsigned char** out_buf, uint64_t* out_buf_size);

private:
	DbJPSnackDescBox* jpsnk_desc_box_ptr_;
	DbInstSetBox* jpsnk_inst_box_ptr_;
	std::list<DbObjMetaDataBox*> obj_mdata_boxes_;
};
}

