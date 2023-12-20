#include "db_jpsnk_desc_box.h"

DbJPSnackDescBox::DbJPSnackDescBox()
{
}

DbJPSnackDescBox::~DbJPSnackDescBox()
{
}

void DbJPSnackDescBox::set_start_time(uint64_t s_time)
{
	start_time_ = s_time;
}

uint64_t DbJPSnackDescBox::get_start_time()
{
	return start_time_;
}

void DbJPSnackDescBox::set_num_of_comp(uint8_t no)
{
	if (no == 0) {
		num_comp = 0;
		num_comp_present = false;
	}
	else {
		num_comp = no;
		num_comp_present = true;
	}
}

uint8_t DbJPSnackDescBox::get_num_of_comp()
{
	return num_comp;
}

bool DbJPSnackDescBox::is_num_of_comp_present()
{
	return num_comp_present;
}
