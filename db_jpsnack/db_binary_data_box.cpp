
#include "db_binary_data_box.h"

namespace dbench {

	DbBinaryDataBox::DbBinaryDataBox()
	{
		set_box_type(BoxType::BIDB);
	}

	DbBinaryDataBox::~DbBinaryDataBox()
	{
	}

	DbBinaryDataBox::DbBinaryDataBox(unsigned char* binary_data, uint64_t binary_data_size)
	{
		set_box(binary_data, binary_data_size);
	}

	void DbBinaryDataBox::set_box(unsigned char* binary_data, uint64_t binary_data_size)
	{
		set_box_type(BoxType::BIDB);
		set_box_payload(binary_data, binary_data_size);
	}

}
