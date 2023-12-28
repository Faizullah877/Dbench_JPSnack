#pragma once
#include <list>
#include "db_box.h"
#include "db_jumb_box.h"
#include "db_jpsnk_desc_box.h"
#include "db_jpsnk_inst_set_box.h"
#include "db_jpsnk_obmb.h"

namespace dbench {

class DbJPSnack : DbJumbBox
{
public:
	DbJPSnack();
	~DbJPSnack();

private:
	DbJPSnackDescBox jpsnk_desc_box_;
	DbInstSetBox jpsnk_inst_box_;
	std::list<DbObjMetaDataBox> obj_mdata_boxes_;
};
}

